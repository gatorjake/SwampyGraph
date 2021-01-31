//
// Created by jbsha on 1/29/2021.
//

#include "Edge.h"

Edge::Edge(Vertex &origin, Vertex &destination, bool forwardDirected, bool backwardDirected, Color color,
           Color highlight, int weight) : origin(origin), destination(destination), color(color), highlight(highlight) {
        origin.degree++;
        destination.degree++;
        this->forwardDirected = forwardDirected;
        this->backwardDirected = backwardDirected;
        this->weight = weight;
}

void Edge::toggleHighlight(Color color) {
    if (highlight == color) {
        highlight = Color();
    }
    else {
        highlight = color;
    }
}

void Edge::redirect(bool forward, bool backward) {
    forwardDirected = forward;
    backwardDirected = backward;
}

void Edge::toggleColor(Color &color) {
    if (this->color == color) {
        this->color = Color();
    }
    else {
        this->color = color;
    }
}

std::ostream &operator<<(std::ostream &os, const Edge& edge) {
    if (edge.forwardDirected) {
        if (edge.backwardDirected) {
            os << "I am an arrow between vertices " << edge.origin.id << " and " << edge.destination.id;
        }
        else {
            os << "I am an arrow pointing from " << edge.origin.id << " to " << edge.destination.id;
        }
    } else {
        if (edge.backwardDirected) {
            os << "I am an arrow point to " << edge.origin.id << " from " << edge.destination.id;
        } else {
            os << "I am an edge between vertices " << edge.origin.id << " and " << edge.destination.id;
        }
    }
    os << " colored " << edge.color << " and highlighted " << edge.highlight << ".";
    if (edge.weight != 1) {
        os << " I weigh " << edge.weight << ".";
    }
    return os;
}

bool Edge::isRelativelyDirected(int originID) const {
    return ((origin.id == originID) && forwardDirected) || ((destination.id == originID) && backwardDirected);
}

void Edge::removeIncidencies(std::vector<Vertex*>& candidates) const {
    for (int i = 0; i < candidates.size(); i++) {
        if (candidates.at(i)->id == origin.id || candidates.at(i)->id == destination.id) {
            candidates.erase(candidates.begin() + i);
            i--;
        }
    }
}

int Edge::distributeInDegrees() {
    if (forwardDirected) {
        destination.inDegree++;
        return destination.id;
    }
    if (backwardDirected) {
        origin.inDegree++;
        return origin.id;
    }
    return -1;
}

