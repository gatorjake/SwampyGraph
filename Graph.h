//
// Created by jbsha on 1/30/2021.
//

#ifndef SWAMPYGRAPH_GRAPH_H
#define SWAMPYGRAPH_GRAPH_H
#include <vector>
#include <string>
#include "Vertex.h"
#include "Edge.h"

/*
 * Plan: A vector of vertices and a 3-tensor of edges:
 * a 2D "array" to contain edge vectors, which contain all edges between two vertices.
 * Most of these vectors are empty, and that's OK.
 */
class Graph {
    std::vector<Vertex*> vertices;
    std::vector<std::vector<Vertex*>> confounders;
    int sufficientSetsFound = 0;
    std::vector<std::vector<Edge*>> paths;
    int currentPath = 0;
    std::vector<std::vector<std::vector<Edge*>>> edges;
    int maxVertexID = 0;
public:
    int addVertex(Color color = Color(), Color highlight = Color());
    void addEdge(Vertex *origin, Vertex *destination, bool arrow = false, bool biarrow = false, Color color = Color(), Color highlight = Color());
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    std::ostream& vertexInfo(std::ostream& os, Vertex* vertex) const;
    Vertex* getVertex(int id) { return vertices.at(id); }
    std::vector<Edge*> getEdges(int originID, int destinationID);
    Edge* getEdge(int originID, int destinationID, int which = 0) { return getEdges(originID, destinationID).at(which); }
    void identifyPaths();
    void identifyPaths(int originID, int destinationID);
    void identifyPaths(int originID, int destinationID, int currentID);
    std::vector<std::vector<Vertex*>>& findConfounders(bool quick = false);
    static std::string findConfounders(std::string inVertices, std::string inEdges, int inExposure = 0, int inOutcome = 1, bool quick = true);
    static bool isDirected(std::vector<Edge*> path, int exposureID, int outcomeID);
    ~Graph();
    void identifyDescendants(int ancestorID, int currentID);
};


#endif //SWAMPYGRAPH_GRAPH_H
