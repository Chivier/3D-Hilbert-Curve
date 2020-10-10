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
    // Describe a HilbertMesh
    private:
    // Hilbert children
    HilbertMesh *child_[kHilbertChild];
    // If the hilbert mesh is seperated
    bool seperate_;
    // // Count how many nodes this mesh contains, dynamically updated
    // int nodes_;

    public:
    HilbertMesh() = default;
    ~HilbertMesh() = default;

    // Set Function
    void set_child(const int id, HilbertMesh *const newchild) { child_[id] = newchild; }
    void set_seperate(const bool seperate) { seperate_ = seperate; }
    // void set_level(const int nodes) { nodes_ = nodes; }

    // Get Function
    HilbertMesh *get_child(const int id) const { return child_[id]; }
    bool get_seperate() const { return seperate_; }
    // int get_nodes() const { return nodes_; }

    // Split Child
    void SplitChild(const int id);

    // Merge Child
    void MergeChild(const int id);

    // Calculate id
    void CalcId(const std::vector<int> hilbert_cord);
};

// Calculate the maximum depth of a hilbert mesh
int CalcHilbertLevel(HilbertMesh *const hilbert_mesh);

// Delete the hilbert mesh
void DeleteHilbertMesh(HilbertMesh *const hilbert_mesh);

// Calc the coordination range of id-th block
std::pair<std::vector<double>, std::vector<double>> CalcCoordination(HilbertMesh *const hilbert_mesh, const int id,
                                                                     const std::vector<double> minc,
                                                                     const std::vector<double> maxc);

// return the block id which contains the block
} // namespace hilbert

using namespace hilbert;
#endif