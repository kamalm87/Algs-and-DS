#include "GraphAL.h" 
#include "GraphAM.h"

GraphAM<int> Figure25_1(){
  GraphAM<int> g = GraphAM<int>(5);
  for(int i = 1; i <= 5; i++)
    g.AddVertex(i);

  g.AddEdge( 1, 2,  3);
  g.AddEdge( 1, 3,  8);
  g.AddEdge( 1, 5, -4);
  g.AddEdge( 2, 4,  1 );
  g.AddEdge( 2, 5,  7 );
  g.AddEdge( 3, 2,  4 );
  g.AddEdge( 4, 1,  2 );
  g.AddEdge( 4, 3, -5 );
  g.AddEdge( 5, 4,  6 );

  return g;
}

Graph<int> Figure25_1_AL(){
  Graph<int> g;

  for(int i = 1; i <= 5; i++)
    g.AddVertex(i, true);

  g.AddEdge( 1, 2,  3);
  g.AddEdge( 1, 3,  8);
  g.AddEdge( 1, 5, -4);
  g.AddEdge( 2, 4,  1 );
  g.AddEdge( 2, 5,  7 );
  g.AddEdge( 3, 2,  4 );
  g.AddEdge( 4, 1,  2 );
  g.AddEdge( 4, 3, -5 );
  g.AddEdge( 5, 4,  6 );

  return g;
 
}

GraphAM<int> Figure25_2(){
  GraphAM<int> g = GraphAM<int>(6);
  for( int i = 1; i <= 6; i++ )
    g.AddVertex(i);
  
  g.AddEdge( 1, 5, -1 );
  g.AddEdge( 2, 1,  1 );
  g.AddEdge( 2, 4,  2 );
  g.AddEdge( 3, 2,  2 );
  g.AddEdge( 3, 6, -8 );
  g.AddEdge( 4, 1, -4 );
  g.AddEdge( 4, 5,  3 );
  g.AddEdge( 5, 2,  7 );
  g.AddEdge( 6, 2,  5 );
  g.AddEdge( 6, 3, 10 );
 
  return g;
}

GraphAM<int> Figure25_5(){
  GraphAM<int> g = GraphAM<int>(4);
  for ( int i = 1; i <= 4; i++ )
    g.AddVertex( i );

  g.AddEdge( 2, 3, 2 ); 
  g.AddEdge( 2, 4, 2 );
  g.AddEdge( 3, 2, 2 ); 
  g.AddEdge( 4, 1, 2 ); 
  g.AddEdge( 4, 3, 2 ); 

  return g; 

}

Graph<int> Figure25_6(){
  Graph<int> g;
  g.AddVertex(1, true);
  g.AddVertex(2, true);
  g.AddVertex(3, true);
  g.AddVertex(4, true);
  g.AddVertex(5, true);
  
  g.AddEdge( 1, 2,  3);
  g.AddEdge( 1, 3,  8);
  g.AddEdge( 1, 5, -4);
  g.AddEdge( 2, 4,  1);
  g.AddEdge( 2, 5,  7);
  g.AddEdge( 3, 2,  4);
  g.AddEdge( 4, 3, -5);
  g.AddEdge( 5, 4,  6);
  
  return g;
}


void Johnson(){
  auto g = Figure25_1_AL();

  std::cout << std::endl << "Performing Johnson's Algorithm on Figure 25.1:" << std::endl;
  auto wut = g.Johnson( 9 );
  wut.PrintEVERYTHINGDOG();
}


void q(){
  auto g = Figure25_6();

}

void TransitiveClosure(){
  auto g = Figure25_5();

  std::cout << "Transitive Closure: " << std::endl;
  auto wtf = g.TransitiveClosure();

  wtf.PrintEVERYTHINGDOG();
}

void tF251_2(){
  auto g = Figure25_1();
  std::cout << std::endl; 
  std::cout << "Performing FloydWarshal on Figure 25.1: " << std::endl;
  auto dk = g.FloydWarshal( g.edges );
  dk.PrintEVERYTHINGDOG();

  int fn = 1;
}


void tF251_1(){

  std::cout << std::endl; 
  std::cout << "Performing Basic Shortest Path Algorithm on Figure 25.1: " << std::endl;

  GraphAM<int> g = Figure25_1(); 
 
  
  auto l = g.SlowAllPairsShortestPaths( g.edges );
  l.PrintEVERYTHINGDOG();
}

int main(){
  tF251_1();
  tF251_2();
  TransitiveClosure();
  Johnson();
}
