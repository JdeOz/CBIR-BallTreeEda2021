//
//

#ifndef RESTRUCTBALLTREE_BALLTREE_HPP
#define RESTRUCTBALLTREE_BALLTREE_HPP

#include "Funciones.h"
#include <queue>

using namespace std;


template<size_t N, typename ElemType, size_t L>
struct BallNode {
    // Nodo Hoja y Nodo Intermedio
    Point<N> ctr; // Centro
    double r; // Radio
    bool isLeaf;// Booleano que nos dices si es hoja o intermedio

    // Nodo hoja
    int num;// Cantidad de datos
    ElemType data[L];// Array de datos

    // Nodo Intermedio
    int left; // Hijo izquierdo
    int right; //hijo derecho

    BallNode() {

    }
};


template<size_t N, typename ElemType, size_t L>
class BallTree {
public:
    BallTree() {
        DataSetTree = read_mnist_images_points<784, int>("Files/train-images-idx3-ubyte"); // Cargo las imágenes
        queue<vector<BallLeaf<N, ElemType>>> DataSet; // Creo una cola con el conjunto de datos que le entraran a cada Node
        DataSet.push(DataSetTree); // Inicio la cola con todos los datos
        int label = 0; // Indice correspondiente a cada hijo
        while (!DataSet.empty()) {
            auto node = new BallNode<N, ElemType, L>; // Nuevo nodo que crearé

            // Centro del nodo
            Point<N> center = mean<N, ElemType>(DataSet.front()); // Generamos el centro del Nodo
            node->ctr = center; // Asigno el centro al nodo

            // Radio del nodo
            Point<N> farthest = argmax<N, ElemType>(DataSet.front(), center); // Hallamos el punto más lejano al centro
            double r = euclidian<N>(farthest, center); // Generamos el radic del nodo
            node->r = r; // Asigno el radio al nodo

            // Pregunto si es o no hoja
            if (DataSet.front().size() <= L) {
                // En el caso que si sea hoja copio las BallLeaf en la data de mi Node
                node->isLeaf = true;
                node->num = DataSet.front().size(); // Asigno la cantidad de hojas que tendrá el nodo hoja
                for (int i = 0; i < DataSet.front().size(); i++) { // Guardo los índices de los BallLeaf hijos
                    node->data[i] = DataSet.front()[i].value;
                }
                node->left = -1; // Declaro nulos los hijos, ya que es nodo hoja
                node->right = -1; // Declaro nulos los hijos, ya que es nodo hoja
            } else {
                // En el caso que no sea hoja divido mis datos en izquierdo y derecho
                node->isLeaf = false;
                node->num = 0; // Como es intermedio entonces no tiene hojas

                random_device rd; // Iniciamos generador aleatorio
                mt19937 mt(rd()); // Iniciamos generador aleatorio
                uniform_int_distribution<int> randNode(0, DataSet.front().size() - 1); // Iniciamos generador aleatorio

                int x0 = randNode(mt); // Buscamos un nodo random
                Point<N> x1 = argmax<N, ElemType>(DataSet.front(),
                                                  DataSet.front()[x0].coords); // Nodo más lejano del random
                Point<N> x2 = argmax<N, ElemType>(DataSet.front(), x1); // Nodo más lejano del más lejano
                Point<N> W = vectorsRes<N>(x1, x2); // Calculamos el vector entre los puntos x1 y x2
                priority_queue<pair<double, BallLeaf<N, ElemType>>> Z; // Creo una cola de prioridad para separar la data
                int median = DataSet.front().size() / 2; // Guardo el índice de la mediana que sería en la mitad de mi Z
                for (int i = 0; i < DataSet.front().size(); i++) { // Asigno su posición en el vector W
                    Z.push(pair<double, BallLeaf<N, ElemType>>(vectorsMult(W, DataSet.front()[i].coords),
                                                               DataSet.front()[i]));
                }
                vector<BallLeaf<N, ElemType>> SL; // Creamos la nueva DataSet para el hijo izquierdo
                vector<BallLeaf<N, ElemType>> SR; // Creamos la nueva DataSet para el hijo derecho
                for (int i = 0; i < median; i++) { // Llenamos el hijo izquierdo con la mitad de los datos
                    SL.push_back(Z.top().second);
                    Z.pop();
                }
                while (!Z.empty()) { // Llenamos el hijo derecho con lo que queda de los datos
                    SR.push_back(Z.top().second);
                    Z.pop();
                }

                DataSet.push(SL); // Agregamos SL a mi cola de DataSet
                node->left = ++label; // Le asignamos el hijo izquierdo a mi nodo

                DataSet.push(SR);// Agregamos SR a mi cola de DataSet
                node->right = ++label; // Le asignamos el hijo derecho a mi nodo

            }
            Nodes.push_back(node); // Agregamos el nodo que creamos a nuestro vector de nodos
            DataSet.pop(); // descartamos el DataSet correspondiente que ya usamos
        }
    }

    BallTree(string name) {
        DataSetTree = read_mnist_images_points<784, int>("Files/train-images-idx3-ubyte"); // Cargo las imágenes
        LoadBallTree(name); // Cargo los nodos a mi árbol
    }

    vector<ElemType> KNN_search(Point<N> t, int k) {
        priority_queue<pair<double, BallLeaf<N, ElemType>>> Q; // Cola en la que se almacenará los resultados del KNN
        vector<ElemType> res; // vector que llenaré con los resultados
        KNN(t, k, Q, Nodes[0]); // Calculo el KNN
        while (!Q.empty()) {
            res.push_back(Q.top().second.value); // Lleno res con los resultados
            Q.pop();
        }
        return res; // Devuelvo res
    }

    void SaveBallTree(string name) {
        ofstream w("Files/" + name + ".bin", ios::binary);
        if (w.is_open()) {
            int total = Nodes.size(); // Declaro la cantidad de nodos que tengo
            w.write((char *) &total, sizeof(int)); // Primero guardo la cantidad de nodos para saber cuantos cargar
            for (auto i: Nodes) {
                w.write((char *) i, sizeof(BallNode<N, ElemType, L>)); // Escribo nodo por nodo en el bin
            }
        } else {
            cout << "Error al abrir el archivo" << endl;
        }
        w.close();
    }

    void LoadBallTree(string name) {
        ifstream r("Files/" + name + ".bin", ios::binary);
        if (r.is_open()) {
            int total; // Variable donde almacenaré la cantidad de nodos que voy a cargar
            r.read((char *) &total, sizeof(int)); // La leo del bin
            for (int i = 0; i < total; i++) { // Cargo nodo por nodo y los almaceno en Nodes
                auto n = new BallNode<N, ElemType, L>;
                r.read((char *) n, sizeof(BallNode<N, ElemType, L>));
                Nodes.push_back(n);
            }
        } else {
            cout << "Error al abrir el archivo" << endl;
        }
        r.close();
    }

private:
    vector<BallNode<N, ElemType, L> *> Nodes;
    vector<BallLeaf<N, ElemType>> DataSetTree;

    void KNN(Point<N> t, int k, priority_queue<pair<double, BallLeaf<N, ElemType>>> &Q, BallNode<N, ElemType, L> *B) {
        // Si el nodo está muy alejado y mi cola ya está completa lo descarto
        if (Q.size() == k and euclidian<N>(t, B->ctr) - B->r >= Q.top().first) {
            return;
        } else if (B->isLeaf) { // Si mi nodo es hoja entonces pregunto BallLeaf por BallLeaf (data)
            for (int i = 0; i < B->num; i++) {
                double distance = euclidian(t, DataSetTree[B->data[i]].coords);
                if (Q.size() < k or distance < Q.top().first) {
                    pair<double, BallLeaf<N, ElemType>> x(distance, DataSetTree[B->data[i]]);
                    Q.push(x); // Si está más cerca que el nodo más lejano del la cola entonces valen como respuesta.
                    if (Q.size() > k) { // Si mi cola se pasa de k entonces le quito el elemento más lejano.
                        Q.pop();
                    }
                }
            }
        } else { // Si mi nodo es intermedio entonces aplico el KNN a cada hijo, pero primero al más cercano
            double d1 = euclidian(t, Nodes[B->left]->ctr);
            double d2 = euclidian(t, Nodes[B->right]->ctr);
            if (d1 < d2) {
                KNN(t, k, Q, Nodes[B->left]);
                KNN(t, k, Q, Nodes[B->right]);
            } else {
                KNN(t, k, Q, Nodes[B->right]);
                KNN(t, k, Q, Nodes[B->left]);
            }
        }
    }
};


#endif //RESTRUCTBALLTREE_BALLTREE_HPP
