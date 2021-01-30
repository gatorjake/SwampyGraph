//
// Created by jbsha on 1/30/2021.
//

#include "Graph.h"
#include <iostream>

using namespace std;

int Graph::addVertex(Color color, Color highlight) {
    //expand the edges vector as needed so that the addEdge method doesn't give an ArrayIndexOutOfBoundsException
    for (auto& edgeVectorVector : edges) {
        vector<Edge*> newEdgeVector;
        edgeVectorVector.push_back(newEdgeVector);
    }
    vector<vector<Edge*>> newEdgeVectorVector;
    for (int i = 0; i <= maxVertexID; i++) {
        vector<Edge*> newEdgeVector;
        newEdgeVectorVector.push_back(newEdgeVector);
    }
    edges.push_back(newEdgeVectorVector);
    vertices.push_back(new Vertex(maxVertexID, color, highlight));
    maxVertexID++;
    return maxVertexID;
}

void Graph::addEdge(Vertex *origin, Vertex *destination, bool arrow, bool biarrow, Color color, Color highlight) {
    Edge* newEdge = new Edge(*origin, *destination, arrow || biarrow, biarrow, color, highlight);
    //debug: cout << edges.size() << edges.at(0).size() << edges.at(0).at(0).size();
    edges.at(origin->id).at(destination->id).push_back(newEdge);
}

ostream &operator<<(ostream &os, const Graph &graph) {
    for (auto& vertex : graph.vertices) {
        graph.vertexInfo(os, vertex);
    }
    return os;
}

ostream& Graph::vertexInfo(ostream &os, Vertex* vertex) const {
    os << *vertex << endl;
    os << "The following edges are incident to it:" << endl;
    for (auto& edgeVector : edges.at(vertex->id)) {
        for (auto& edge : edgeVector) {
            os << "> " << *edge << endl;
        }
    }
    os << "***" << endl;
    for (auto& edgeVectorVector : edges) {
        for (auto& edge : edgeVectorVector.at(vertex->id)) {
            os << "> " << *edge << endl;
        }
    }
    os << endl;
    return os;
}

Graph::~Graph() {
    for (Vertex* vertex : vertices) {
        delete vertex;
    }
    vertices.clear();
    for (auto& edgeVectorVector : edges) {
        for (auto& edgeVector : edgeVectorVector) {
            for (Edge* edge : edgeVector) {
                delete edge;
            }
            edgeVector.clear();
        }
        edgeVectorVector.clear();
    }
    edges.clear();
}

vector<Edge*> Graph::getEdges(int originID, int destinationID) {
    vector<Edge*> edgesHere;
    for (auto& edge : edges.at(originID).at(destinationID)) {
        edgesHere.push_back(edge);
    }
    for (auto& edge : edges.at(destinationID).at(originID)) {
        edgesHere.push_back(edge);
    }
    return edgesHere;
}

