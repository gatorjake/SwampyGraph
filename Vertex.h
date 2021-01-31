//
// Created by jbsha on 1/29/2021.
//

#ifndef SWAMPYGRAPH_VERTEX_H
#define SWAMPYGRAPH_VERTEX_H
#include "Color.h"
#include <vector>

struct Vertex {
    int id;
    int degree = 0;
    Color color;
    Color highlight;
    bool visited = false;
    bool exposure = false;
    bool outcome = false;
    int inDegree = 0;
    std::vector<Vertex*> descendants;

    explicit Vertex(int _id, Color color = Color(), Color _highlight = Color());
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);
};


#endif //SWAMPYGRAPH_VERTEX_H
