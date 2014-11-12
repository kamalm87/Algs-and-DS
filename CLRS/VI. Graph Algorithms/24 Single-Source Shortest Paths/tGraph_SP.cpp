#include "Graph_SP.h"

Graph<char> Figure24_1_1(){

  Graph<char> g;
  g.AddVertex('a');
  g.AddVertex('b');
  g.AddVertex('c');
  g.AddVertex('d');
  g.AddVertex('e');
  g.AddVertex('f');
  g.AddVertex('g');
  g.AddVertex('s');

  g.AddEdge( 's', 'a',  3 );
  g.AddEdge( 's', 'c',  5 );
  g.AddEdge( 's', 'e',  2 );
  g.AddEdge( 'a', 'b', -4 );
  g.AddEdge( 'b', 'g',  4 );
  g.AddEdge( 'c', 'd',  6 );
  g.AddEdge( 'd', 'c', -3 );
  g.AddEdge( 'd', 'g',  8 );
  g.AddEdge( 'e', 'f',  3 );
  g.AddEdge( 'f', 'e', -6 );
  g.AddEdge( 'f', 'g',  7 );

  return g;
}

Graph<char> Figure24_1_2(){

  Graph<char> g;
  g.AddVertex( 'h' );
  g.AddVertex( 'i' );
  g.AddVertex( 'j' );

  g.AddEdge( 'h', 'i',  2 );
  g.AddEdge( 'i', 'j',  3 ); 
  g.AddEdge( 'j', 'h', -8 );
  return g;
}

Graph<char> Figure_24_2(){

  Graph<char> g;

  g.AddVertex('s');
  g.AddVertex('t');
  g.AddVertex('x');
  g.AddVertex('y');
  g.AddVertex('z');

  // from edges:
  // s's edges
  g.AddEdge( 's', 't',  3 );
  g.AddEdge( 's', 'y',  5 );
  // t's edges 
  g.AddEdge( 't', 'x',  6 );
  g.AddEdge( 't', 'y',  2 );
  // x's edges
  g.AddEdge( 'x', 'z', 11); 
  // y's edges
  g.AddEdge( 'y', 't', 1 );
  g.AddEdge( 'y', 'x', 4 ); 
  g.AddEdge( 'y', 'z', 6 ); 
  // z's edges
  g.AddEdge( 'z', 'x', 7 );

  return g;
}

Graph<char> Figure_24_4(){
  Graph<char> g;
  g.AddVertex('s');
  g.AddVertex('t');
  g.AddVertex('x');
  g.AddVertex('y');
  g.AddVertex('z');

  // from edges:
  // s's edges
  g.AddEdge( 's', 't',  6 );
  g.AddEdge( 's', 'y',  7 );
  // t's edges 
  g.AddEdge( 't', 'x',  5 );
  g.AddEdge( 't', 'y',  8 );
  g.AddEdge( 't', 'z', -4 );
  // x's edges 
  g.AddEdge( 'x', 't', -2 );
  // y's edges
  g.AddEdge( 'y', 'z',  9 );
  g.AddEdge( 'y', 'x', -3 );
  // z's edges
  g.AddEdge( 'z', 'x',  7 );

  return g;
}

Graph<char> Figure_24_5(){
 
  Graph<char> g;
  g.AddVertex('r');
  g.AddVertex('s');
  g.AddVertex('t');
  g.AddVertex('x');
  g.AddVertex('y');
  g.AddVertex('z');

  g.AddEdge( 'r', 's',  5 );
  g.AddEdge( 'r', 't',  3 );
  g.AddEdge( 's', 't',  2 );
  g.AddEdge( 's', 'x',  6 );
  g.AddEdge( 't', 'x',  7 );
  g.AddEdge( 't', 'y',  4 );
  g.AddEdge( 't', 'z',  2 );
  g.AddEdge( 'x', 'y', -1 );
  g.AddEdge( 'x', 'z',  1 ); 
  g.AddEdge( 'y', 'z', -2 );
  
  return g;
}

Graph<char> Figure_24_6(){
 
  Graph<char> g;
  g.AddVertex('s'); 
  g.AddVertex('t'); 
  g.AddVertex('y'); 
  g.AddVertex('x'); 
  g.AddVertex('z'); 
  
  g.AddEdge( 's', 't', 10 );
  g.AddEdge( 's', 'y',  5 );  
  g.AddEdge( 't', 'y',  2 );  
  g.AddEdge( 'y', 't',  3 );  
  g.AddEdge( 't', 'x',  1 );
  g.AddEdge( 'x', 'z',  4 );
  g.AddEdge( 'z', 'x',  6 ); 
  g.AddEdge( 'y', 'z',  2 );
  g.AddEdge( 'y', 'x',  9 ); 
  g.AddEdge( 'z', 's',  7 );

  return g;
}

template <typename T>
void ApplyAndPrintBellmanFord(Graph<T> &g, T s, std::string msg = ""){
  std::cout << std::endl << std::endl;
  std::cout << msg << std::endl;
  g.PrintVerticesInfo();
    g.PrintEdgesInfo();
  std::cout << "After Bellman-Ford:" << std::endl;
  bool result = g.BellmanFord(s);
  std::cout << "The graph contains no negative cycles: " << result << std::endl; 
  g.PrintVerticesInfo();

}

void TestBellmanFord(){
  Graph<char> f2411 = Figure24_1_1();
  Graph<char> f2412 = Figure24_1_2();
  Graph<char> f242 = Figure_24_2();
  Graph<char> f244 = Figure_24_4();

  ApplyAndPrintBellmanFord( f2411, 's', "Figure 24.1.1:" ); 
  ApplyAndPrintBellmanFord( f2412, 'h', "Figure 24.1.2:" ); 
  ApplyAndPrintBellmanFord( f242,  's', "Figure 24.22:" ); 
  ApplyAndPrintBellmanFord( f244,  's', "Figure 24.4:"   ); 

}

void TestDijkstra(){
  std::cout << std::endl << "Djikstra's Algorithm on Figure 24.6:" << std::endl << "Before:"  << std::endl;
  Graph<char> f246 = Figure_24_6();
  f246.PrintEdgesInfo();
  f246.PrintVerticesInfo(); 
  
  std::cout << "After given starting point: s" << std::endl;
  f246.Dijkstra('s');
  f246.PrintVerticesInfo(); 
}

int main(){
  
  TestBellmanFord();
  TestDijkstra();
  /*
  auto f = Figure_24_6();
  f.PrintEdgesInfo();
  f.PrintVerticesInfo();
  

  f.Dijkstra('s');
  f.PrintVerticesInfo();

  //  TestBellmanFord();
  */
/*  
  auto wut = Figure_24_4();
  wut.PrintVerticesInfo();
  wut.PrintEdgesInfo();
  auto realTrapShit = wut.BellmanFord('s');
  wut.PrintVerticesInfo();
  wut.PrintEdgesInfo();
  */


  int endBP = 1;
}
