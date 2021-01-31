//
// Created by jbsha on 1/30/2021.
//

#include "Graph.h"
#include <iostream>
#include <cmath>
#include <unordered_map>

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

void Graph::identifyPaths(int originID, int destinationID) {
    if (originID == destinationID) {
        return;
    }
    for (Vertex*& vertex : vertices) {
        vertex->visited = false;
    }
    paths.emplace_back();
    identifyPaths(originID, destinationID, originID);
}

void Graph::identifyDescendants(int ancestorID, int currentID) {
    vertices.at(ancestorID)->descendants.push_back(vertices.at(currentID));
    vertices.at(currentID)->visited = true;
    for (int i = 0; i < maxVertexID; i++) {
        if (vertices.at(i)->visited) {
            continue;
        }
        if (edges.at(i).at(currentID).size() + edges.at(currentID).at(i).size() == 0) {
            continue;
        }
        for (Edge*& edge : edges.at(i).at(currentID)) {
            if (edge->isRelativelyDirected(currentID))
                identifyDescendants(ancestorID, edge->totalVertexID() - currentID);
        }
        for (Edge*& edge : edges.at(currentID).at(i)) {
            if (edge->isRelativelyDirected(currentID))
                identifyDescendants(ancestorID, edge->totalVertexID() - currentID);
        }
    }
}

void Graph::identifyPaths(int originID, int destinationID, int currentID) {
    vertices.at(currentID)->visited = true;
    if (destinationID == currentID) {
        currentPath++;
        paths.emplace_back();
        for (int i = 0; i < paths.at(currentPath - 1).size(); i++) {
            paths.at(currentPath).push_back(paths.at(currentPath - 1).at(i));
        }
    }
    else { for (int i = 0; i < maxVertexID; i++) {
        if (vertices.at(i)->visited) {
            continue;
        }
        if (edges.at(i).at(currentID).size() + edges.at(currentID).at(i).size() == 0) {
            continue;
        }
        for (Edge*& edge : edges.at(i).at(currentID)) {
            paths.at(currentPath).push_back(edge);
            identifyPaths(originID, destinationID, i);
        }
        for (Edge*& edge : edges.at(currentID).at(i)) {
            paths.at(currentPath).push_back(edge);
            identifyPaths(originID, destinationID, i);
        }
    }}
    vertices.at(currentID)->visited = false;
    if (!paths.at(currentPath).empty()) {
        paths.at(currentPath).pop_back();
    } else {
        paths.at(currentPath).clear();
    }
}

void Graph::identifyPaths() {
    for (int i = 0; i < maxVertexID; i++) {
        for (int j = 0; j < i; j++) {
            identifyPaths(i, j);
        }
    }
}

vector<std::vector<Vertex*>>& Graph::findConfounders(bool quick) {
    vector<Vertex*> candidates = vertices;
    for (auto& exposure : vertices) {
        if (exposure->exposure) {
            for (auto& outcome : vertices) {
                if (outcome->outcome) {
                    identifyPaths(exposure->id, outcome->id);
                    for (auto& path : paths) {
                        if (isDirected(path, exposure->id, outcome->id)) {
                            for (auto& edge : path) {
                                edge->removeIncidencies(candidates);
                                identifyDescendants(edge->getOriginID(), edge->getOriginID());
                            }
                        }
                    }
                    identifyDescendants(outcome->id, outcome->id);
                }
            }
        }
    }
    for (int i = 0; i < maxVertexID; i++) {
        for (Vertex* vertex : vertices) {
            for (Vertex* descendant : vertex->descendants) {
                if (descendant->id == i) {
                    for (int j = 0; j < candidates.size(); j++) {
                        if (candidates.at(j)->id == i) {
                            candidates.erase(candidates.begin() + j);
                            j--;
                        }
                    }
                }
            }
        }
    }

    confounders.emplace_back();
    for (int i = 0; i < pow(2, candidates.size()); i++) {
        if (quick) {
            i = (int)(pow(2, candidates.size()) - 0.99);
        }
        int j = i;
        vector<Vertex*>& subset = confounders.at(sufficientSetsFound);
        for (int k = 0; k < candidates.size(); k++) {
            if (j / (int)(pow(2, k)) % 2 == 1) {
                subset.push_back(candidates.at(k));
            }
        }
        bool sufficient = true;

        for (auto& path : paths) {
            if (path.empty()) {
                continue;
            }

            bool isInSomeSenseDirected = false;
            for (auto &exposure : vertices) {
                if (exposure->exposure) {
                    for (auto &outcome : vertices) {
                        if (outcome->outcome) {
                            if (isDirected(path, exposure->id, outcome->id)) {
                                isInSomeSenseDirected = true;
                            }
                        }
                    }
                }
            }
            if (isInSomeSenseDirected) {
                continue;
            }

            vector<int> inDegreeAssignments;
            inDegreeAssignments.reserve(path.size());
            for (Edge* edge : path) {
                inDegreeAssignments.push_back(edge->distributeInDegrees());
            }
            bool isBlocked = false;
            for (Vertex* vertex : vertices) {
                int relevantInDegreeAssignments = 0;
                for (int assignment : inDegreeAssignments) {
                    if (assignment == vertex->id) {
                        relevantInDegreeAssignments++;
                    }
                }
                if (vertex->inDegree > 1 || relevantInDegreeAssignments > 1) {
                    isBlocked = true;
                }
                vertex->inDegree = 0;
            }
            if (isBlocked) {
                continue;
            }

            bool pathUnderControl = false;
            vector<int> route;
            route.reserve(2 * path.size());
            for (Edge* edge : path) {
                route.push_back(edge->getOriginID());
                route.push_back(edge->totalVertexID() - edge->getOriginID());
            }
            for (Vertex* controlledFor : subset) {
                for (int routed : route) {
                    if (controlledFor->id == routed) {
                        pathUnderControl = true;
                    }
                }
            }
            if (pathUnderControl) {
                continue;
            }

            sufficient = false;
            break;
        }

        if (sufficient) {
            sufficientSetsFound++;
            confounders.emplace_back();
        }
        else {
            subset.clear();
        }
    }
    confounders.pop_back();
    for (auto& SufficientSet : confounders) {
        cout << "To determine the causal effect of the exposure(s) on the outcome(s), it suffices to control for the following vertices:";
        for (auto& confounder : SufficientSet) {
            cout << " " << confounder->id << ".";
        }
        cout << endl;
    }
    return confounders;
}

bool Graph::isDirected(const std::vector<Edge*>& path, int exposureID, int outcomeID, int progress) {
    if (path.size() - progress == 0) {
        return true;
    }
    for (Edge* edge : path) {
        if (edge->isRelativelyDirected(exposureID)) {
            return isDirected(path, edge->totalVertexID() - exposureID, outcomeID, progress + 1);
        }
    }
    return false;
    /* int auditID = exposureID;
    int pathDex = 0;
    while (auditID != outcomeID) {
        if (path.at(pathDex)->isRelativelyDirected(auditID)) {
            auditID = path.at(pathDex)->totalVertexID() - auditID;
        } else {
            return false;
        }
    }
    return true; */
}

std::string
Graph::findConfounders(std::string inVertices, std::string inEdges, int inExposure, int inOutcome, bool quick) {
    Graph me;
    unordered_map<string, int> vertexNames;
    int toParse = inVertices.length();
    string split;
    int i = 0;
    while (toParse > 0) {
        string nextChar = inVertices.substr(0, 1);
        if (nextChar == "[" || nextChar == "," || nextChar == "]") {
            toParse--;
            inVertices.erase(0, 1);
        } else {
            split = inVertices.substr(0, min(inVertices.find(','), min(inVertices.find('['), inVertices.find(']'))));
            me.addVertex();
            vertexNames[split] = i;
            toParse -= split.length();
            inVertices.erase(0, split.length());
            i++;
        }
    }
    toParse = inEdges.length();
    int edgeCycle = 0;
    int originID, destinationID, weight;
    while (toParse > 0) {
        string nextChar = inEdges.substr(0, 1);
        if (nextChar == "[" || nextChar == "," || nextChar == "]") {
            toParse--;
            inEdges.erase(0, 1);
        } else {
            split = inEdges.substr(0, min(inEdges.find(','), min(inEdges.find('['), inEdges.find(']'))));
            switch (edgeCycle) {
                case 0:
                    originID = vertexNames[split];
                    break;
                case 1:
                    destinationID = vertexNames[split];
                    break;
                case 2:
                    weight = stoi(split);
                    break;
                default:
                    cout << "HELP!" << endl;
            }
            edgeCycle += 1;
            if (edgeCycle == 3) {
                me.addEdge(me.getVertex(originID), me.getVertex(destinationID), true);
                me.getEdge(originID, destinationID)->setWeight(weight); //todo: handle case of multiple weighted edges between the same vertices
                edgeCycle = 0;
            }
            toParse -= split.length();
            inEdges.erase(0, split.length());
        }
    }

    me.vertices.at(inExposure)->exposure = true;
    me.vertices.at(inOutcome)->outcome = true;
    vector<vector<Vertex*>>& solutions = me.findConfounders(quick);
    vector<Vertex*>& principleSolution = solutions.at(0);
    cout << me << endl;

    string s = "[";
    for (int p = 0; p < principleSolution.size() - 1; p++) {
        int confounderID = principleSolution.at(p)->id;
        for (const auto& possibleName : vertexNames) {
            if (possibleName.second == confounderID) {
                s += possibleName.first;
            }
        }
    }
    s += "]";
    return s;
}

