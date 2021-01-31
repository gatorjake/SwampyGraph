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
    //causal.findConfounders();
    //cout << causal << endl;

    Graph M;
    M.addVertex();
    M.addVertex();
    M.addVertex();
    M.addVertex();
    M.addVertex();
    M.addVertex();

    M.addEdge(M.getVertex(0), M.getVertex(4), true);
    M.addEdge(M.getVertex(1), M.getVertex(2), true);
    M.addEdge(M.getVertex(1), M.getVertex(0), true);
    M.addEdge(M.getVertex(3), M.getVertex(2), true);
    M.addEdge(M.getVertex(3), M.getVertex(4), true);
    M.addEdge(M.getVertex(4), M.getVertex(5), true);
    M.addEdge(M.getVertex(0), M.getVertex(5), true);

    M.getVertex(0)->exposure = true;
    M.getVertex(4)->outcome = true;
    //M.findConfounders();
    //cout << M << endl;

    Graph Example5;
    Example5.addVertex();
    Example5.addVertex();
    Example5.addVertex();
    Example5.addVertex();
    Example5.addVertex();
    Example5.addVertex();
    Example5.addVertex();
    Example5.addVertex();

    Example5.addEdge(Example5.getVertex(0), Example5.getVertex(1), true);
    Example5.addEdge(Example5.getVertex(0), Example5.getVertex(4), true);
    Example5.addEdge(Example5.getVertex(1), Example5.getVertex(2), true);
    Example5.addEdge(Example5.getVertex(1), Example5.getVertex(4), true);
    Example5.addEdge(Example5.getVertex(2), Example5.getVertex(3), true);
    Example5.addEdge(Example5.getVertex(2), Example5.getVertex(5), true);
    Example5.addEdge(Example5.getVertex(3), Example5.getVertex(4), true);
    Example5.addEdge(Example5.getVertex(3), Example5.getVertex(6), true);
    Example5.addEdge(Example5.getVertex(7), Example5.getVertex(4), true);
    Example5.addEdge(Example5.getVertex(7), Example5.getVertex(5), true);

    Example5.getVertex(2)->exposure = true;
    Example5.getVertex(4)->outcome = true;
    //Example5.findConfounders();
    //cout << Example5 << endl;

    /*Graph::findConfounders("[Swamphacks, More Coding, Less Sleep, Turning into a Programmer]",
                           "[[Swamphacks, More Coding, 1]]"); */
    //Graph::findConfounders("[2,3,5,7,11,13]", "[[2,5,6],[3,7,6],[2,3,6],[11,2,6],[13,3,6],[11,13,6]]");
    string result = Graph::findConfounders("[a,b,c]", "[[a,b,1],[c,a,1],[c,b,1]]");
    return 0;
}
