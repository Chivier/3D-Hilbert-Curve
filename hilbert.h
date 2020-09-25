#ifndef HILBERT_H
#define HILBERT_H
#include <algorithm>
#include <iostream>
#include <vector>

namespace hilbert {
// Basic Hilbert Transform
int BinaryToGray(int num);
int GrayToBinary(int num);

std::vector<int> getHilbertIntegerToTranspose(int num, int level);
int getHilbertTransposeToInteger(std::vector<int> num, int level);

std::vector<int> getHilbertCord(int h, int level);
int getHilbertIndex(std::vector<int> hilbert_cord, int level);
int getHilbertZoneIndex(int num, int level);

// Hilbert Mesh
const int kHilbertChild = 8;

class HilbertMesh {
    private:
    HilbertMesh *child_[kHilbertChild];
    bool seperate_;
    // int level_;

    public:
    HilbertMesh() = default;
    ~HilbertMesh() = default;

    // Set Function
    void set_child(const int id, HilbertMesh *const newchild) { child_[id] = newchild; }
    void set_seperate(const bool seperate) { seperate_ = seperate; }
    // void set_level(const int level) { level_ = level; }

    // Get Function
    HilbertMesh *get_child(const int id) const { return child_[id]; }
    bool get_seperate() const { return seperate_; }
    // int get_level() { return level_; }

    // Split Child
    void SplitChild(const int id);

    // Merge Child
    void MergeChild(const int id);

    // Calculate id
    void CalcId(const std::vector<int> hilbert_cord);

    // Calculate coordination
    void CalcCoordination(const int id);
};

// Calculate the maximum depth of a hilbert mesh
int CalcHilbertLevel(HilbertMesh *const hilbert_mesh);

// Delete the hilbert mesh
void DeleteHilbertMesh(HilbertMesh *const hilbert_mesh);

} // namespace hilbert

using namespace hilbert;
#endif