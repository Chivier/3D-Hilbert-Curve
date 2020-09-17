#ifndef HILBERT_H
#define HILBERT_H
#include <iostream>
#include <vector>

namespace hilbert {
int BinaryToGray(int num);
int GrayToBinary(int num);

std::vector<int> getHilbertIntegerToTranspose(int num, int level);
int getHilbertTransposeToInteger(std::vector<int> num, int level);

std::vector<int> getHilbertCord(int h, int level);
int getHilbertIndex(std::vector<int> hilbert_cord, int level);
int getHilbertZoneIndex(int num, int level);
} // namespace hilbert

using namespace hilbert;
#endif