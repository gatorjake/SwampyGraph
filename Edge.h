//
// Created by jbsha on 1/29/2021.
//

#ifndef SWAMPYGRAPH_EDGE_H
#define SWAMPYGRAPH_EDGE_H
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Color.h"

class Edge {
    Vertex& origin, destination;
    bool forwardDirected, backwardDirected;
    Color color, highlight;
    int weight;
public:
    Edge(Vertex &origin, Vertex &destination, bool forwardDirected = false,
         bool backwardDirected = false, Color color = Color(), Color highlight = Color(), int weight = 1);
    void toggleHighlight(Color color = Color(255, 255));
    void redirect(bool forward, bool backward);
    void toggleColor(Color& color);
    void setWeight(int newWeight) { weight = newWeight; }
    [[nodiscard]] bool isRelativelyDirected(int originID) const;
    [[nodiscard]] int totalVertexID() const { return origin.id + destination.id; }
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);
    void removeIncidencies(std::vector<Vertex *> candidates) const;
    int distributeInDegrees();
    [[nodiscard]] int getOriginID() const { return origin.id; }
};

#endif //SWAMPYGRAPH_EDGE_H
