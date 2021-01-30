//
// Created by jbsha on 1/29/2021.
//

#include "Vertex.h"

Vertex::Vertex(int _id, Color _color, Color _highlight) {
    id = _id;
    color = _color;
    highlight = _highlight;
}

std::ostream &operator<<(std::ostream &os, const Vertex &vertex) {
    os << "Vertex #" << vertex.id << " has degree " << vertex.degree <<
    ". It is colored " << vertex.color << " with a " << vertex.highlight << " highlight.";
    return os;
}
