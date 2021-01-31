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
    //cout << graph << endl;
    
    Graph causal;
    causal.addVertex();
    causal.addVertex();
    causal.addVertex();
    causal.addVertex();
    
    causal.addEdge(causal.getVertex(0), causal.getVertex(1), true);
    causal.addEdge(causal.getVertex(2), causal.getVertex(0), true);
    causal.addEdge(causal.getVertex(2), causal.getVertex(1), true);
    causal.addEdge(causal.getVertex(0), causal.getVertex(3), true);
    causal.addEdge(causal.getVertex(1), causal.getVertex(3), true);

    causal.getVertex(0)->exposure = true;
    causal.getVertex(1)->outcome = true;
    causal.findConfounders();
    cout << causal << endl;
    
    return 0;
}
