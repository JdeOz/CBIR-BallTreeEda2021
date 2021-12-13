

#ifndef RESTRUCTBALLTREE_BALLLEAF_HPP
#define RESTRUCTBALLTREE_BALLLEAF_HPP

#include "Point.hpp"

// Uso esta estructura para almacenar en un solo objeto el Point de la imagen y su valor que en este caso es su índice.
template<size_t N, typename ElemType>
struct BallLeaf {
    Point<N> coords;
    ElemType value;

    BallLeaf() {

    }

    BallLeaf(Point<N> coords, ElemType value) {
        this->coords = coords;
        this->value = value;
    }
};


#endif //RESTRUCTBALLTREE_BALLLEAF_HPP
