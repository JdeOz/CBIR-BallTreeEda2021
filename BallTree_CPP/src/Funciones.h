#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <utility>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "BallLeaf.hpp"

using namespace std;

#define MAX_BUF 3137
const char *CP = "/tmp/CP";// Write, guardo el fifo en la carpeta temp
const char *PC = "/tmp/PC";// Read, guardo el fifo en la carpeta temp


/* ####################################################################################################*/
/* ###################################### 0 Funciones IPC (FIFO) ######################################*/
/* ####################################################################################################*/
// 0.1 Read FIFO
string fifoRead() {
    int fd;
    char n[MAX_BUF];
    fd = open(PC, O_RDONLY);
    read(fd, n, MAX_BUF);
    close(fd);
    string n_(n);
    return n_;
}

// 0.2 Write FIFO
void fifoWrite(const string &n) {
    int fd;
    char n2[n.size()];
    strcpy(n2, n.c_str());
    fd = open(CP, O_WRONLY);
    write(fd, n2, n.size());
    close(fd);
}


/* ####################################################################################################*/
/* ###################################### 1 Cargado del DataSet #######################################*/
/* ####################################################################################################*/
// 1.1 Función necesaria para el cargado de imágenes
int reverseInt(int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    return ((int) c1 << 24) + ((int) c2 << 16) + ((int) c3 << 8) + c4;
}

// 1.2 Cargado de imágenes
vector<vector<int>> read_mnist_images(const string &name) {
    ifstream file(name, std::ios::binary);
    vector<vector<int>> images;
    if (file.is_open()) {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char *) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char *) &number_of_images, sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char *) &n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char *) &n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        for (int i = 0; i < number_of_images; ++i) {
            vector<int> raw;
            for (int r = 0; r < n_rows; ++r) {
                for (int c = 0; c < n_cols; ++c) {
                    unsigned char temp = 0;
                    file.read((char *) &temp, sizeof(temp));
                    raw.push_back((int) temp);
                }
            }
            images.push_back(raw);
        }
    }
    return images;
}

// 1.3 Cargado de las labels
vector<int> read_mnist_labels(const string &name) {
    ifstream file(name, std::ios::binary);
    vector<int> labels;
    if (file.is_open()) {
        int magic_number = 0;
        int number_of_labels = 0;
        file.read((char *) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char *) &number_of_labels, sizeof(number_of_labels));
        number_of_labels = reverseInt(number_of_labels);
        for (int i = 0; i < number_of_labels; ++i) {
            unsigned char temp = 0;
            file.read((char *) &temp, sizeof(temp));
            labels.push_back((int) temp);
        }
    }
    return labels;
}

// 1.2 Cargado de imágenes
template<size_t N, typename ElemType>
vector<BallLeaf<N, ElemType>> read_mnist_images_points(const string &name) {
    ifstream file(name, std::ios::binary);
    vector<BallLeaf<N, ElemType>> images;
    if (file.is_open()) {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char *) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char *) &number_of_images, sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char *) &n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);
        file.read((char *) &n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);
        for (int i = 0; i < number_of_images; i++) {
            Point<N> image;
            for (int j = 0; j < N; j++) {
                unsigned char temp = 0;
                file.read((char *) &temp, sizeof(temp));
                image[j] = (int) temp;
            }
            images.push_back(BallLeaf<N, ElemType>(image, i));
        }
    }
    return images;
}


/* ####################################################################################################*/
/* ####################################### 2 Manejo de vectores #######################################*/
/* ####################################################################################################*/
//// 2.1 Distancia Euclidiana
template<size_t N>
double euclidian(Point<N> a, Point<N> b) {
    double x = 0;
    for (int i = 0; i < N; i++) {
        x += pow(b[i] - a[i], 2);
    }
    return sqrt(x);
}

// 2.2 Función que calcula el punto del conjunto S más lejano a p
template<size_t N, typename ElemType>
Point<N> argmax(vector<BallLeaf<N, ElemType>> S, Point<N> p) {
    int iterMax = 0;
    double distanceMax = 0;
    for (int i = 0; i < S.size(); i++) {
        double distance = euclidian(p, S[i].coords);
        if (distance > distanceMax) {
            iterMax = i;
            distanceMax = distance;
        }
    }
    return S[iterMax].coords;
}

// 2.3 Función que calcula el punto medio (mean) de un conjunto de puntos
template<size_t N, typename ElemType>
Point<N> mean(vector<BallLeaf<N, ElemType>> S) {
    Point<N> meanPoint;
    for (int i = 0; i < N; i++) {
        meanPoint[i] = 0;
    }
    for (auto &point: S) {
        for (int j = 0; j < N; j++) {
            meanPoint[j] += point.coords[j];
        }
    }
    for (int i = 0; i < N; i++) {
        meanPoint[i] = meanPoint[i] / (double) S.size();
    }
    return meanPoint;
}

// 2.4 Resta de vectores(Puntos)
template<size_t N>
Point<N> vectorsRes(Point<N> a, Point<N> b) {
    Point<N> x;
    for (int i = 0; i < N; i++) {
        x[i] = a[i] - b[i];
    }
    return x;
}

// 2.5 Multiplicación de vectores(Puntos)
template<size_t N>
double vectorsMult(Point<N> a, Point<N> b) {
    double x = 0;
    for (int i = 0; i < N; i++) {
        x += a[i] * b[i];
    }
    return x;
}


/* ####################################################################################################*/
/* ##################################### 3 Manejo de string ###########################################*/
/* ####################################################################################################*/
// 3.1 Dividir un string
vector<string> split(const string &sentence, char param) {
    string parte;
    vector<string> splitted;
    stringstream x(sentence);
    while (getline(x, parte, param)) {
        splitted.push_back(parte);
    }
    return splitted;
}

// 3.2 Convertir string a point
template<size_t N>
Point<N> to_point(const string &s) {
    Point<N> newPoint;
    vector<string> splitted = split(s, ',');
    for (int i = 0; i < N; i++) {
        newPoint[i] = stod(splitted[i]);
    }
    return newPoint;
}


/* ####################################################################################################*/
/* ################################### 4 Sobrecarga operadores ########################################*/
/* ####################################################################################################*/
template<size_t N, typename ElemType>
bool operator<(const pair<double, BallLeaf<N, ElemType>> &p1, const pair<double, BallLeaf<N, ElemType>> &p2) {
    return p1.first < p2.first;
}