#include "Graph.h"
#include <iostream>

void testBreadthFirstSearch(){
    Graph<char> g;

    g.AddVertex('s');
    g.AddVertex('r');
    g.AddVertex('v');
    g.AddVertex('w');
    g.AddVertex('x');
    g.AddVertex('t');
    g.AddVertex('u');
    g.AddVertex('y');

    
    g.AddUndirectedEdge('v', 'r');
    g.AddUndirectedEdge('r', 's');
    g.AddUndirectedEdge('s', 'w');
    g.AddUndirectedEdge('w', 't');
    g.AddUndirectedEdge('w', 'x');
    g.AddUndirectedEdge('t', 'x');
    g.AddUndirectedEdge('t', 'u');
    g.AddUndirectedEdge('x', 'u');
    g.AddUndirectedEdge('x', 'y');
    g.AddUndirectedEdge('u', 'y');
  
    g.printVertexInfo('s');
    g.printVertexInfo('r');
    g.printVertexInfo('v');
    g.printVertexInfo('w');
    g.printVertexInfo('x');
    g.printVertexInfo('t');
    g.printVertexInfo('u');
    g.printVertexInfo('y');

    g.BreadthFirstSearch();

    auto s = g.vMap['s'];
    auto r = g.vMap['r'];
    auto v = g.vMap['v'];
    auto w = g.vMap['w'];
    auto x = g.vMap['x'];
    auto t = g.vMap['t'];
    auto u = g.vMap['u'];
    auto y = g.vMap['y'];

    std::cout << s->Data << ", D: " << s->Distance  << ", C: "  << g.GetColor(s) << std::endl;
    std::cout << r->Data << ", D: " << r->Distance  << ", C: "  << g.GetColor(r) << std::endl;
    std::cout << v->Data << ", D: " << v->Distance  << ", C: "  << g.GetColor(v) << std::endl;
    std::cout << w->Data << ", D: " << w->Distance  << ", C: "  << g.GetColor(w) << std::endl;
    std::cout << x->Data << ", D: " << x->Distance  << ", C: "  << g.GetColor(x) << std::endl;
    std::cout << t->Data << ", D: " << t->Distance  << ", C: "  << g.GetColor(t) << std::endl;
    std::cout << u->Data << ", D: " << u->Distance  << ", C: "  << g.GetColor(u) << std::endl;
    std::cout << y->Data << ", D: " << y->Distance  << ", C: "  << g.GetColor(y) << std::endl;

    int ThePointBreakPointPatrickSwayzee = 1;
}

int main(){
    testBreadthFirstSearch();
    std::cout << "We made it" << std::endl;
}
