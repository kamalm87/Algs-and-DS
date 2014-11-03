#include "Graph.h"
#include <iostream>

// To perform a crude implementation of Figure 22.7 from the text
#include <string>

void Figure_22_3();
void Figure_22_4();
void Figure_22_5();
void Figure_22_6();
void Figure_22_7();
void Figure_22_8();
void Figure_22_9();

void testBreadthFirstSearch(){
    std::cout << "*********************************************" << std::endl; 
    std::cout << "Figure 22.3's BFS Results:" << std::endl;
    Figure_22_3();
    std::cout << "*********************************************" << std::endl; 
}

void testDepthFirstSearch(){
    
    std::cout << "*********************************************" << std::endl; 
    std::cout << "Figure 22.4's DFS Results:" << std::endl;
    Figure_22_4();
    std::cout << "*********************************************" << std::endl; 
    
    std::cout << "*********************************************" << std::endl; 
    std::cout << "Figure 22.5's DFS Results:" << std::endl;
    Figure_22_5();
    std::cout << "*********************************************" << std::endl; 
    
    std::cout << "*********************************************" << std::endl; 
    std::cout << "Figure 22.6's DFS Results:" << std::endl;
    Figure_22_6();
    std::cout << "*********************************************" << std::endl; 

}

void testStronglyConnectedComponents(){
 std::cout << "*********************************************" << std::endl; 
 std::cout << "Figure 22.9's Strongly Connected Components Results:" << std::endl;
 Figure_22_9();
}

void testTopologicalSort(){
    Figure_22_7();
    Figure_22_8();
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

    g.BreadthFirstSearch();
    g.printBreadthFirstSearchResults();
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
   
    g.DepthFirstSearch();
    g.printDepthFirstSearchResults();
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

    g2.DepthFirstSearch();
    g2.printDepthFirstSearchResults();
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
    
    std::cout << "Vertex info prior to BFS";
    g.printDepthFirstSearchResults();
    g.DepthFirstSearch();
    std::cout << "Preforming Depth-First Search";   
    g.printDepthFirstSearchResults();
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

    g.printTopologicalSortedResults();
    g.printDepthFirstSearchResults();
}

void Figure_22_8(){
    Graph<char> g;
    for(int i = 109; i < 123; i++)
        g.AddVertex(static_cast<char>(i));

    // add m's 3 directed edges
    g.AddUndirectedEdge('m', 'x'); 
    g.AddUndirectedEdge('m', 'q');
    g.AddUndirectedEdge('m', 'r');
    
    // add n's 3 directed edges
    g.AddUndirectedEdge('n', 'q'); 
    g.AddUndirectedEdge('n', 'u');
    g.AddUndirectedEdge('n', 'o');

    // add o's 2 directed edges
    g.AddUndirectedEdge('o', 'r'); 
    g.AddUndirectedEdge('o', 's');

    // add p's 3 directed edges
    g.AddUndirectedEdge('p', 'o'); 
    g.AddUndirectedEdge('p', 's');
    g.AddUndirectedEdge('p', 'z');

    // add q's 1 directed edge
    g.AddUndirectedEdge('q', 't'); 

    // add r's 1 directed edges
    g.AddUndirectedEdge('r', 'u'); 

    // add s's 3 directed edges
    g.AddUndirectedEdge('s', 'r'); 

    // DO NOT direct edges to t
   
    // add u's 1 directed edge
    g.AddUndirectedEdge('u', 't'); 
  
    // add v's 2 directed edges
    g.AddUndirectedEdge('v', 'x'); 
    g.AddUndirectedEdge('v', 'w'); 

    // add w's 1 directed edge
    g.AddUndirectedEdge('w', 'z'); 

    // DO NOT direct edges to x

    // add y's 1 directed edge
    g.AddUndirectedEdge('y', 'v'); 

    // DO NOT direct edges to z

    g.printTopologicalSortedResults();
    g.printDepthFirstSearchResults();
}

void Figure_22_9(){
	Graph<char> g;
	g.AddVertex('a');
	g.AddVertex('b');
	g.AddVertex('c');
	g.AddVertex('d');
	g.AddVertex('e');
	g.AddVertex('f');
	g.AddVertex('g');
	g.AddVertex('h');

	// SCC: abe
	g.AddEdge('a', 'b');
	g.AddEdge('b', 'e');
	g.AddEdge('e', 'a');

	// SCC: cd
	g.AddEdge('c', 'd');
	g.AddEdge('d', 'c');

  // SCC: h
	g.AddEdge('h', 'h');


	// SCC: fg
	g.AddEdge('f', 'g');
	g.AddEdge('g', 'f');

  // cross-edge: h -> cd
  g.AddEdge('h', 'd');

	// cross-edge: abe -> fg
	g.AddEdge('b', 'f');

	// cross-edge: abe -> fg
	g.AddEdge('e', 'f');

	// cross-edge: abe -> cd
	g.AddEdge('b', 'c');

	// cross-edge: cd -> fg
	g.AddEdge('c', 'g');

	// cross-edge: fg -> h 
	g.AddEdge('g', 'h');
  
  std::cout << std::endl << "Graph info" << std::endl << std::endl;
  g.printVertices();

  std::cout << "Strongly connected components: " << std::endl << std::endl;
	g.PrintStronglyConnectedComponents();
}
int main(){

    testBreadthFirstSearch();
    testDepthFirstSearch();
    testTopologicalSort();
    testStronglyConnectedComponents();

    std::cout << std::endl << "We made it" << std::endl;
}
