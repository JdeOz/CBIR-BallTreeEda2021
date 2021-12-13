#include <iostream>
#include "BallTree.hpp"
#include "Timer.hpp"

using namespace std;

// Timer para el indexado del Ball Tree
template<size_t N, typename ElemType, size_t L>
BallTree<N, ElemType, L> IndexBallTree(string name) {
    BallTree<784, int, 10> MyBallTree(name);
    return MyBallTree;
}

// Timer para el KNN
template<size_t N, typename ElemType, size_t L>
vector<ElemType> KnnBallTree(BallTree<N, ElemType, L> &BT, Point<N> t, int k) {
    return BT.KNN_search(t, k);
}


int main() {
    // FIFO
    mkfifo(CP, 0666); // Creo el fifo CP por si no existe (PC = C++-Python)
    mkfifo(PC, 0666); // Creo el fifo PC por si no existe (CP = Python-C++)

    // Declaración funciones Timer
    Timer<BallTree<784, int, 10>(string)> Ball_Tree_Index(IndexBallTree, "Index");
    Timer<vector<int>(BallTree<784, int, 10> &, Point<784>, int)> Ball_Tree_Knn(KnnBallTree, "KNN");

    // Cargo mi Ball Tree del archivo  .bin
    BallTree<784, int, 10> MyBallTree = Ball_Tree_Index("BallTreeFile");

    // Envío un mensaje que diga que ya se indexó el Ball Tree, En este caso el "PID" por si necesitamos enviar algún "signal"
    string PID = (to_string(getpid()));
    fifoWrite(PID);

    // Loop principal
    while (true) {
        string receive = fifoRead(); // Espero el mensaje de python, puede ser "exit" o el k y la imagen para nuestro knn
        if (receive == "exit") break; // Si el mensaje es "exit" termino el programa
        vector<string> params = split(receive, ';'); // Separo el k del vector de la imagen
        int k = stoi(params[0]); // Convierto mi k en entero
        string bitMap = params[1]; // Guardo el vector que representa mi imagen en bitMap
        Point<784> image = to_point<784>(bitMap); // Convierto en Point el string que representaba mi imagen
        vector<int> knn = Ball_Tree_Knn(MyBallTree, image, k); // Calculo el knn
        string results; // String que devolveré con mi resultado
        for (auto i: knn) {
            results += to_string(i) + ","; // Convierto mi resultado en un string para enviarlo por el fifo
        }
        results.pop_back(); // Le quito la última coma que se pone por error
        fifoWrite(results); // Envío mi resultado
    }
}
