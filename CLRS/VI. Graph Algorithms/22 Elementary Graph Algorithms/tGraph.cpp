#include "Graph.h"
#include <iostream>

// To perform a crude implementation of Figure 22.7 from the text
#include <string>

void Figure_22_3();
void Figure_22_4();
void Figure_22_5();
void Figure_22_6();
void Figure_22_7();

void testBreadthFirstSearch(){
    std::cout << "Figure 22.3's BFS Results:" << std::endl;
    Figure_22_3();
    std::cout << std::endl << std::endl;
   
}

void testDepthFirstSearch(){
  
    std::cout << "Figure 22.4's DFS Results:" << std::endl;
    Figure_22_4();

    std::cout << std::endl << std::endl;

    std::cout << "Figure 22.5's DFS Results:" << std::endl;
    Figure_22_5();

    std::cout << std::endl << std::endl;

    std::cout << "Figure 22.6's DFS Results:" << std::endl;
    Figure_22_6();

}


void testTopologicalSort(){
    Figure_22_7();
}

void Figure_22_3(){
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


}

void Figure_22_4(){
    Graph<char> g;
    g.AddVertex('u');
    g.AddVertex('v');
    g.AddVertex('w');
    g.AddVertex('x');
    g.AddVertex('y');
    g.AddVertex('z');

    g.AddEdge('u', 'v');
    g.AddEdge('u', 'x');
    g.AddEdge('y', 'x');
    g.AddEdge('v', 'y');
    g.AddEdge('x', 'v');
    g.AddEdge('w', 'y');
    g.AddEdge('w', 'z');
    g.AddEdge('z', 'z');
    
    g.printVertexInfo('u');
    g.printVertexInfo('v');
    g.printVertexInfo('w');
    g.printVertexInfo('x');
    g.printVertexInfo('y');
    g.printVertexInfo('z');



    auto u = g.vMap['u'];
    auto v = g.vMap['v'];
    auto w = g.vMap['w'];
    auto x = g.vMap['x'];
    auto y = g.vMap['y'];
    auto z = g.vMap['z'];


    g.DepthFirstSearch();



    std::cout << u->Data << " D: " << u->Discovered << " F: " << u->Finished << " C: " <<  g.GetColor(u) << std::endl;
    std::cout << v->Data << " D: " << v->Discovered << " F: " << v->Finished << " C: " <<  g.GetColor(w) << std::endl;
    std::cout << w->Data << " D: " << w->Discovered << " F: " << w->Finished << " C: " <<  g.GetColor(w) << std::endl;
    std::cout << x->Data << " D: " << x->Discovered << " F: " << x->Finished << " C: " <<  g.GetColor(x) << std::endl;
    std::cout << y->Data << " D: " << y->Discovered << " F: " << y->Finished << " C: " <<  g.GetColor(y) << std::endl;
    std::cout << z->Data << " D: " << z->Discovered << " F: " << z->Finished << " C: " <<  g.GetColor(z) << std::endl;

}

void Figure_22_5(){
  Graph<char> g2;

    g2.AddVertex('y');
    g2.AddVertex('z');
    g2.AddVertex('s');
    g2.AddVertex('t');
    g2.AddVertex('x');
    g2.AddVertex('w');
    g2.AddVertex('v');
    g2.AddVertex('u');

    g2.AddEdge('y', 'x');
    g2.AddEdge('x', 'z');
    g2.AddEdge('z', 'y');
    g2.AddEdge('z', 'w');
    g2.AddEdge('w', 'x');
    g2.AddEdge('s', 'z');
    g2.AddEdge('s', 'w');
    g2.AddEdge('v', 's');
    g2.AddEdge('v', 'w');
    g2.AddEdge('t', 'v');
    g2.AddEdge('t', 'u');
    g2.AddEdge('u', 't');
    g2.AddEdge('u', 'v');


    auto y = g2.vMap['y'];
    auto z = g2.vMap['z'];
    auto s = g2.vMap['s'];
    auto t = g2.vMap['t'];
    auto x = g2.vMap['x'];
    auto w = g2.vMap['w'];
    auto v = g2.vMap['v'];
    auto u = g2.vMap['u'];

    g2.DepthFirstSearch();
    
    std::cout << y->Data << " D: " << y->Discovered << " F: " << y->Finished << " C: " <<  g2.GetColor(y) << std::endl;
    std::cout << z->Data << " D: " << z->Discovered << " F: " << z->Finished << " C: " <<  g2.GetColor(z) << std::endl;
    std::cout << s->Data << " D: " << s->Discovered << " F: " << s->Finished << " C: " <<  g2.GetColor(s) << std::endl;
    std::cout << t->Data << " D: " << t->Discovered << " F: " << t->Finished << " C: " <<  g2.GetColor(t) << std::endl;
    std::cout << x->Data << " D: " << x->Discovered << " F: " << x->Finished << " C: " <<  g2.GetColor(x) << std::endl;
    std::cout << w->Data << " D: " << w->Discovered << " F: " << w->Finished << " C: " <<  g2.GetColor(w) << std::endl;
    std::cout << v->Data << " D: " << v->Discovered << " F: " << v->Finished << " C: " <<  g2.GetColor(w) << std::endl;
    std::cout << u->Data << " D: " << u->Discovered << " F: " << u->Finished << " C: " <<  g2.GetColor(u) << std::endl;

}

void Figure_22_6(){
    Graph<char> g;
    g.AddVertex('q');
    g.AddVertex('r');
    g.AddVertex('u');
    g.AddVertex('y');
    g.AddVertex('t');
    g.AddVertex('x');
    g.AddVertex('z');
    g.AddVertex('s');
    g.AddVertex('v');
    g.AddVertex('w');

    // With edge := (directed) edge, with the vertex as the 'from' vertex
    // q's 3 edges
    g.AddEdge('q', 's');
    g.AddEdge('q', 'w');
    g.AddEdge('q', 't');
    // w's 1 edge
    g.AddEdge('w', 's');
    // s's 1 edge
    g.AddEdge('s', 'v');
    // v's 1 edge
    g.AddEdge('v', 'w');
    // t's 2 edges
    g.AddEdge('t', 'x');
    g.AddEdge('t', 'y');
    // x's 1 edge
    g.AddEdge('x', 'z');
    // z's 1 edge
    g.AddEdge('z', 'x');
    // y's 1 edge 
    g.AddEdge('y', 'q');
    // r's 2 edges
    g.AddEdge('r', 'u');
    g.AddEdge('r', 'y');
    // u's 1 edge
    g.AddEdge('u', 'y');


    auto q = g.vMap['q'];
    auto r = g.vMap['s'];
    auto s = g.vMap['s'];
    auto t = g.vMap['t'];
    auto u = g.vMap['u'];
    auto v = g.vMap['v'];
    auto w = g.vMap['w'];
    auto x = g.vMap['x'];
    auto y = g.vMap['y'];
    auto z = g.vMap['z'];

    std::cout << q->Data << " D: " << q->Discovered << " F: " << q->Finished << " C: " <<  g.GetColor(q) << std::endl;
    std::cout << r->Data << " D: " << r->Discovered << " F: " << r->Finished << " C: " <<  g.GetColor(r) << std::endl;
    std::cout << s->Data << " D: " << s->Discovered << " F: " << s->Finished << " C: " <<  g.GetColor(s) << std::endl;
    std::cout << t->Data << " D: " << t->Discovered << " F: " << t->Finished << " C: " <<  g.GetColor(t) << std::endl;
    std::cout << u->Data << " D: " << u->Discovered << " F: " << u->Finished << " C: " <<  g.GetColor(u) << std::endl;
    std::cout << v->Data << " D: " << v->Discovered << " F: " << v->Finished << " C: " <<  g.GetColor(v) << std::endl;
    std::cout << w->Data << " D: " << w->Discovered << " F: " << w->Finished << " C: " <<  g.GetColor(w) << std::endl;
    std::cout << x->Data << " D: " << x->Discovered << " F: " << x->Finished << " C: " <<  g.GetColor(x) << std::endl;
    std::cout << y->Data << " D: " << y->Discovered << " F: " << y->Finished << " C: " <<  g.GetColor(y) << std::endl;
    std::cout << z->Data << " D: " << z->Discovered << " F: " << z->Finished << " C: " <<  g.GetColor(z) << std::endl;

    g.DepthFirstSearch();
    std::cout << std::endl << "After DFS:" << std::endl;
    
    std::cout << q->Data << " D: " << q->Discovered << " F: " << q->Finished << " C: " <<  g.GetColor(q) << std::endl;
    std::cout << r->Data << " D: " << r->Discovered << " F: " << r->Finished << " C: " <<  g.GetColor(r) << std::endl;
    std::cout << s->Data << " D: " << s->Discovered << " F: " << s->Finished << " C: " <<  g.GetColor(s) << std::endl;
    std::cout << t->Data << " D: " << t->Discovered << " F: " << t->Finished << " C: " <<  g.GetColor(t) << std::endl;
    std::cout << u->Data << " D: " << u->Discovered << " F: " << u->Finished << " C: " <<  g.GetColor(u) << std::endl;
    std::cout << v->Data << " D: " << v->Discovered << " F: " << v->Finished << " C: " <<  g.GetColor(v) << std::endl;
    std::cout << w->Data << " D: " << w->Discovered << " F: " << w->Finished << " C: " <<  g.GetColor(w) << std::endl;
    std::cout << x->Data << " D: " << x->Discovered << " F: " << x->Finished << " C: " <<  g.GetColor(x) << std::endl;
    std::cout << y->Data << " D: " << y->Discovered << " F: " << y->Finished << " C: " <<  g.GetColor(y) << std::endl;
    std::cout << z->Data << " D: " << z->Discovered << " F: " << z->Finished << " C: " <<  g.GetColor(z) << std::endl;

    
    std::cout << std::endl;
}

void Figure_22_7(){

    Graph<std::string> g;
    g.AddVertex("undershorts");
    g.AddVertex("pants");
    g.AddVertex("belt");
    g.AddVertex("socks");
    g.AddVertex("shoes");
    g.AddVertex("watch"); 
    g.AddVertex("shirt");
    g.AddVertex("tie");
    g.AddVertex("jacket");
   

    g.AddEdge("undershorts", "pants");
    g.AddEdge("undershorts", "shoes");

    g.AddEdge("socks", "shoes");

    g.AddEdge("pants", "belt");    
    
    g.AddEdge("belt", "jacket");
    
    g.AddEdge("shirt", "belt");
    g.AddEdge("shirt", "tie");

    g.AddEdge("tie", "jacket");


    g.printVertexInfo("undershorts");
    g.printVertexInfo("pants");
    g.printVertexInfo("belt");
    g.printVertexInfo("shirt");
    g.printVertexInfo("tie");
    g.printVertexInfo("jacket");
    g.printVertexInfo("socks");
    g.printVertexInfo("shoes");
    g.printVertexInfo("watch");
   

    auto undershorts = g.vMap["undershorts"];
    auto pants = g.vMap["pants"];
    auto belt = g.vMap["belt"];
    auto shirt = g.vMap["shirt"];
    auto tie = g.vMap["tie"];
    auto jacket = g.vMap["jacket"];
    auto socks = g.vMap["socks"];
    auto shoes = g.vMap["shoes"];
    auto watch = g.vMap["watch"];

    std::cout << undershorts->Data << " D: " << undershorts->Discovered << " F: " << undershorts->Finished << " C: " <<  g.GetColor(undershorts) << std::endl;
    std::cout << belt->Data << " D: " << belt->Discovered << " F: " << belt->Finished << " C: " <<  g.GetColor(belt) << std::endl;
    std::cout << pants->Data << " D: " << pants->Discovered << " F: " << pants->Finished << " C: " <<  g.GetColor(pants) << std::endl;
    std::cout << shirt->Data << " D: " << shirt->Discovered << " F: " << shirt->Finished << " C: " <<  g.GetColor(shirt) << std::endl;
    std::cout << tie->Data << " D: " << tie->Discovered << " F: " << tie->Finished << " C: " <<  g.GetColor(tie) << std::endl;
    std::cout << jacket->Data << " D: " << jacket->Discovered << " F: " << jacket->Finished << " C: " <<  g.GetColor(jacket) << std::endl;
    std::cout << socks->Data << " D: " << socks->Discovered << " F: " << socks->Finished << " C: " <<  g.GetColor(socks) << std::endl;
    std::cout << shoes->Data << " D: " << shoes->Discovered << " F: " << shoes->Finished << " C: " <<  g.GetColor(shoes) << std::endl;
    std::cout << watch->Data << " D: " << watch->Discovered << " F: " << watch->Finished << " C: " <<  g.GetColor(watch) << std::endl;


    std::cout << std::endl << std::endl; 
    LinkedList<std::string> ll =  g.TopologicalSort();
    auto n = ll.Head;

    std::cout << std::endl << std::endl;
        
    std::cout << undershorts->Data << " D: " << undershorts->Discovered << " F: " << undershorts->Finished << " C: " <<  g.GetColor(undershorts) << std::endl;
    std::cout << belt->Data << " D: " << belt->Discovered << " F: " << belt->Finished << " C: " <<  g.GetColor(belt) << std::endl;
    std::cout << pants->Data << " D: " << pants->Discovered << " F: " << pants->Finished << " C: " <<  g.GetColor(pants) << std::endl;
    std::cout << shirt->Data << " D: " << shirt->Discovered << " F: " << shirt->Finished << " C: " <<  g.GetColor(shirt) << std::endl;
    std::cout << tie->Data << " D: " << tie->Discovered << " F: " << tie->Finished << " C: " <<  g.GetColor(tie) << std::endl;
    std::cout << jacket->Data << " D: " << jacket->Discovered << " F: " << jacket->Finished << " C: " <<  g.GetColor(jacket) << std::endl;
    std::cout << socks->Data << " D: " << socks->Discovered << " F: " << socks->Finished << " C: " <<  g.GetColor(socks) << std::endl;
    std::cout << shoes->Data << " D: " << shoes->Discovered << " F: " << shoes->Finished << " C: " <<  g.GetColor(shoes) << std::endl;
    std::cout << watch->Data << " D: " << watch->Discovered << " F: " << watch->Finished << " C: " <<  g.GetColor(watch) << std::endl;



    std::cout << std::endl << std::endl;
    std::cout << "Optimal order:" << std::endl;
    while(n){
        std::cout << ( n != ll.Tail ? n->Data + "->" : n->Data );
        n = n->Next;
    }
    std::cout << std::endl;
    int A = 1;
}

int main(){
     testBreadthFirstSearch();
     testDepthFirstSearch();
     testTopologicalSort();   
    
    std::cout << std::endl << "We made it" << std::endl;
}
