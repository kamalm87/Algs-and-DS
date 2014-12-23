#include "FlowNetwork.h"
#include <string>

void t(){

  Network<std::string, int> n;
  n.AddVertex ( "s", true );
  n.AddVertex ( "v1", true );
  n.AddVertex ( "v2", true );
  n.AddVertex ( "v3", true );
  n.AddVertex ( "v4", true );
  n.AddVertex ( "t", true );

  n.AddEdge ( "s",  "v1", 16 );
  n.AddEdge ( "s",  "v2", 13 );
  n.AddEdge ( "v2", "v1",  4 );
  n.AddEdge ( "v1", "v3", 12 );
  n.AddEdge ( "v3", "v2",  9 );
  n.AddEdge ( "v3", "t",  20 );
  n.AddEdge ( "v2", "v4", 14 );
  n.AddEdge ( "v4", "t",   4 );
  n.AddEdge ( "v3", "v4",  7 );

  n.PrintEdges();
  std::cout << "Before to try and fail\n";

  n.EdmondsKarp("s","t");
 
 
  std::cout << "Before to try and fail\n";
  
  n.PrintEdges();
  
  
  int db = 1;
}

int main(){
  t();
}
