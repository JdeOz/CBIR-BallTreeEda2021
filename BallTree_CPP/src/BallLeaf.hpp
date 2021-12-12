

#ifndef RESTRUCTBALLTREE_BALLLEAF_HPP
#define RESTRUCTBALLTREE_BALLLEAF_HPP

#include "Point.hpp"

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
