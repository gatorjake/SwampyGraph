#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Graph graph;
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();

    graph.addEdge(graph.getVertex(1), graph.getVertex(3));
    graph.addEdge(graph.getVertex(1), graph.getVertex(3));
    graph.addEdge(graph.getVertex(1), graph.getVertex(3));
    graph.addEdge(graph.getVertex(1), graph.getVertex(3));
    graph.addEdge(graph.getVertex(2), graph.getVertex(3));
    graph.addEdge(graph.getVertex(1), graph.getVertex(4));
    graph.addEdge(graph.getVertex(2), graph.getVertex(4));
    graph.addEdge(graph.getVertex(3), graph.getVertex(4));
    graph.addEdge(graph.getVertex(0), graph.getVertex(0));
    graph.addEdge(graph.getVertex(0), graph.getVertex(4));

    graph.getEdge(1, 4)->redirect(true, true);
    Color red(255);
    graph.getEdge(1, 4)->toggleColor(red);
    graph.getEdge(1, 3)->redirect(true, false);
    graph.getEdge(1, 3, 1)->redirect(false, true);
    graph.getEdge(1, 3, 2)->toggleColor(red);
    graph.getEdge(1, 3, 3)->setWeight(17);
    Color yellow(255, 255);
    graph.getVertex(2)->highlight = yellow;
    graph.getEdge(2, 4)->toggleHighlight(yellow);
    cout << graph << endl;
    //todo for tomorrow: the error occurs at the breakpoint because the Vertex ID has become arbitrary (along with
    //its other aspects. We suspect this is a memory leak and therefore should test that with leaker.h.
    return 0;
}
