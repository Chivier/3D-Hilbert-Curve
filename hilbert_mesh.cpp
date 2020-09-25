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

//
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

void HilbertMesh::SplitChild(const int id) {
    auto child_hilbert = new HilbertMesh;
    child_[id] = child_hilbert;
}

void HilbertMesh::MergeChild(const int id) {
    DeleteHilbertMesh(child_[id]);
    auto child_hilbert = new HilbertMesh;
    child_[id] = child_hilbert;
}

void CalcCoordination(const int )