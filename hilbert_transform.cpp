#include "hilbert.h"

using namespace std;

namespace hilbert {

// * Algorithm of Gray Code
// * Reference: https://mathworld.wolfram.com/GrayCode.html

// Name: BinaryToGray
// Input: num (integer32)
// Output: (integer32)
// Function: Transform a number into its gray code.
int BinaryToGray(int num) {
    return num ^ (num >> 1);
}

// Name: GrayToBinary
// Input: num (integer32)
// Output: (integer32)
// Function: Transform a gray code into a binary number.
int GrayToBinary(int num) {
    int mask = num;
    while (mask) {
        mask >>= 1;
        num ^= mask;
    }
    return num;
}

// * Algorithm of Gray-Hilbert
// If we go through a 3D space in a Hilbert curve, we can give each node an ID. In another word, we encode each node
// with gray code of its 3D-Hilbert sequence ID. Since gray code promise that there is only one different bit between
// every two adjacent numbers, we can rearrange the gray code into a 3-dim coordinate. We use some tricky way to promise
// each 2 coordinate's distance is always 1. And the methods are implemented by the code below.
// * Reference: https://github.com/galtay/hilbertcurve

// Name: getHilbertIntegerToTranspose
// Input: num (integer32), level (integer32)
// Output: (vector<integer32>[size=3])
// Function: Return the transposed data of an integer number at a certain Hilbert level.
std::vector<int> getHilbertIntegerToTranspose(int num, int level) {
    std::vector<int> cord(3, 0);
    for (int index = 0; index < 3; ++index) {
        for (int bit_index = 3 * level - index - 1; bit_index >= 0; bit_index -= 3) {
            cord[index] = cord[index] << 1 | ((num & (1 << bit_index)) >> bit_index);
        }
    }
    return cord;
}

// Name: getHilbertTransposeToInteger
// Input: num (vector<integer32>[size=3]), level (integer32)
// Output: (integer32)
// Function: Return the Hilbert Transpose of a coordinate.
int getHilbertTransposeToInteger(std::vector<int> num, int level) {
    int hilbert = 0;
    for (int index = 0; index < 3; ++index) {
        int offset = 3 * level - index - 1;
        int count = level - 1;
        while (count >= 0) {
            hilbert |= (num[index] & (1 << count)) >> count << offset;
            offset -= 3;
            count--;
        }
    }
    return hilbert;
}

// Name: getHilbertCord
// Input: h(integer32), level(integer32)
// Output: (vector<integer32>[size=3])
// Function: Return the coordination after giving the Hilbert ID and the level of Hilbert block
std::vector<int> getHilbertCord(int h, int level) {
    auto hilbert_cord = getHilbertIntegerToTranspose(h, level);

    int temp = hilbert_cord[2] >> 1;
    for (int i = 2; i > 0; --i) {
        hilbert_cord[i] ^= hilbert_cord[i - 1];
    }
    hilbert_cord[0] ^= temp;

    int scan = 2;
    while (scan != (1 << level)) {
        int scan_check = scan - 1;
        for (int index = 2; index >= 0; --index) {
            if (hilbert_cord[index] & scan)
                hilbert_cord[0] ^= scan_check;
            else {
                temp = (hilbert_cord[0] ^ hilbert_cord[index]) & scan_check;
                hilbert_cord[0] ^= temp;
                hilbert_cord[index] ^= temp;
            }
        }
        scan <<= 1;
    }
    return hilbert_cord;
}

// Name: getHilbertIndex
// Input: hilbert_cord(vector<integer32>), level (integer32)
// Output: (integer32)
// Function: Return the n-level hilbert index of a point.
int getHilbertIndex(std::vector<int> hilbert_cord, int level) {
    int scan = 1 << (level - 1);
    int temp;
    while (scan > 1) {
        int scan_check = scan - 1;
        for (int i = 0; i < 3; ++i) {
            if (hilbert_cord[i] & scan)
                hilbert_cord[0] ^= scan_check;
            else {
                temp = (hilbert_cord[0] ^ hilbert_cord[i]) & scan_check;
                hilbert_cord[0] ^= temp;
                hilbert_cord[i] ^= temp;
            }
        }
        scan >>= 1;
    }

    for (int i = 1; i < 3; i++)
        hilbert_cord[i] ^= hilbert_cord[i - 1];

    temp = 0;
    scan = 1 << (level - 1);
    while (scan > 1) {
        if (hilbert_cord[2] & scan)
            temp ^= scan - 1;
        scan >>= 1;
    }
    for (int i = 0; i < 3; ++i)
        hilbert_cord[i] ^= temp;

    return getHilbertTransposeToInteger(hilbert_cord, level);
}

// Name: getHilbertZoneIndex
// Input: num(integer32), level (integer32)
// Output: (integer32)
// Function: return the rank of a point
int getHilbertZoneIndex(int num, int level) {
    auto cord = getHilbertCord(num, level);
    return cord[2] * (1 << (level * 2)) + cord[1] * (1 << level) + cord[0];
}
} // namespace hilbert