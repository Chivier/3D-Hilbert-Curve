#include "hilbert.h"
#include <iostream>

using namespace std;
using namespace hilbert;

int main() {
    std::cout << hilbert::getHilbertZoneIndex(1, 1) << std::endl;
    HilbertMesh *test_hilebert_mesh1 = new HilbertMesh;
    // std::cout << test_hilebert_mesh1->get_level() << std::endl;
    std::cout << test_hilebert_mesh1->get_child(1) << std::endl;
    delete test_hilebert_mesh1;

    HilbertMesh test_hilebert_mesh2;
    // std::cout << test_hilebert_mesh2.get_level() << std::endl;
}