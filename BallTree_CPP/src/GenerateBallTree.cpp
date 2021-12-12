#include "BallTree.hpp"
#include "Timer.hpp"

using namespace std;

// Timer para la generación del Ball Tree
template<size_t N, typename ElemType, size_t L>
BallTree<N, ElemType, L> GenerateBallTree() {
    BallTree<784, int, 10> MyBallTree;
    return MyBallTree;
}

int main() {
    // Declaración funciones Timer
    Timer<BallTree<784, int, 10>()> Ball_Tree_Generate(GenerateBallTree, "Generate");

    // Generación del BallTree
    BallTree<784, int, 10> MyBallTree = Ball_Tree_Generate();

    // Guardo el Ball Tree generado en un archivo .bin para cargarlo posteriormente
    MyBallTree.SaveBallTree("BallTreeFile");
}
