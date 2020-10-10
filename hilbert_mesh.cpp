#include "hilbert.h"

using namespace hilbert;

// Name: CalcHilbertLevel
// Input: hilbert_mesh (HilbertMesh *const)
// Output: (integer32)
// Function: Calculate the level of the Hilbert mesh
int hilbert::CalcHilbertLevel(HilbertMesh *const hilbert_mesh) {
    if (!hilbert_mesh->get_seperate())
        return 0;

    int depth = 0;
    for (int child_index = 0; child_index < kHilbertChild; child_index++) {
        auto child = hilbert_mesh->get_child(child_index);
        depth = std::max(depth, CalcHilbertLevel(static_cast<HilbertMesh *const>(child)) + 1);
    }

    return depth;
}

// Name: DeleteHilbertMesh
// Input: hilbert_mesh (HilbertMesh *const)
// Output: None
// Function: Delete this mesh and all the children of this hilbert mesh
void hilbert::DeleteHilbertMesh(HilbertMesh *const hilbert_mesh) {
    if (!hilbert_mesh->get_seperate()) {
        delete hilbert_mesh;
        return;
    }

    for (int child_index = 0; child_index < kHilbertChild; child_index++) {
        auto child = hilbert_mesh->get_child(child_index);
        DeleteHilbertMesh(static_cast<HilbertMesh *const>(child));
    }

    delete hilbert_mesh;
}

// Name: HilbertMesh::SplitChild
// Input: id (const integer32)
// Output: None
// Function: Split Hilbert mesh at certain position
void HilbertMesh::SplitChild(const int id) {
    auto child_hilbert = new HilbertMesh;
    child_[id] = child_hilbert;
}

// Name: HilbertMesh:MergeChild
// Input: id (const integer32)
// Output: None
// Function: Merge all the children at a certain level of the Hilbert mesh
void HilbertMesh::MergeChild(const int id) {
    DeleteHilbertMesh(child_[id]);
    auto child_hilbert = new HilbertMesh;
    child_[id] = child_hilbert;
}

int HilbertCount(HilbertMesh *const hilbert_mesh) {
    if (!hilbert_mesh->get_seperate())
        return 1;
    int total_nodes = 0;
    for (int child_index = 0; child_index < kHilbertChild; child_index++) {
        auto child = hilbert_mesh->get_child(child_index);
        total_nodes += HilbertCount(child);
    }
    return total_nodes;
}

// Name: CalcCoordination
// Input: id(const integer32), minc（vector<double>), maxc(vector<double>)
// Output: (vector<double>)
// Function: Give the most left-bottom coordination & right-up coordination, along with the id, this function will
// giveout a range of ths id-th block.
std::pair<std::vector<double>, std::vector<double>> hilbert::CalcCoordination(HilbertMesh *const hilbert_mesh,
                                                                              const int id,
                                                                              const std::vector<double> minc,
                                                                              const std::vector<double> maxc) {
    std::vector<double> st_point;
    std::vector<double> ed_point;
    if (hilbert_mesh == 0) {
    }
}