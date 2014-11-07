#include "Graph_MST.h"

void Figure23_1(){
	Graph<char> g;
	g.AddVertex('a');
	g.AddVertex('b');
	g.AddVertex('c');
	g.AddVertex('d');
	g.AddVertex('e');
	g.AddVertex('f');
	g.AddVertex('g');
	g.AddVertex('h');
	g.AddVertex('i');
	
	g.AddUndirectedEdge('a', 'b', 4);
	g.AddUndirectedEdge('b', 'c', 8);
	g.AddUndirectedEdge('c', 'd', 7);
	g.AddUndirectedEdge('d', 'e', 9);
	g.AddUndirectedEdge('e', 'f', 10);
	g.AddUndirectedEdge('f', 'c', 4);
	g.AddUndirectedEdge('f', 'g', 2);
	g.AddUndirectedEdge('i', 'g', 6);
	g.AddUndirectedEdge('i', 'c', 2);
	g.AddUndirectedEdge('b', 'h', 11);
	g.AddUndirectedEdge('a', 'h', 8);
	g.AddUndirectedEdge('h', 'g', 1);
	g.AddUndirectedEdge('d', 'f', 14);

  auto wut2 = MST_Kruskal(g);
	auto n = wut2.Head;
	int TOTAL = 0;
	while (n){
		auto e = n->Data;
		std::cout << "(" << e.From->Data << "," << e.To->Data << ") w: " << e.Weight << std::endl;
		TOTAL += e.Weight;
		n = n->Next;
	}
	std::cout << "TOTAL: " << TOTAL << std::endl;


}

void Figure23_5(){
	Graph<char> g;
	g.AddVertex('a');
	g.AddVertex('b');
	g.AddVertex('c');
	g.AddVertex('d');
	g.AddVertex('e');
	g.AddVertex('f');
	g.AddVertex('g');
	g.AddVertex('h');
	g.AddVertex('i');
	
	g.AddUndirectedEdge('a', 'b', 4);
	g.AddUndirectedEdge('b', 'c', 8);
	g.AddUndirectedEdge('c', 'd', 7);
	g.AddUndirectedEdge('d', 'e', 9);
	g.AddUndirectedEdge('e', 'f', 10);
	g.AddUndirectedEdge('f', 'c', 4);
	g.AddUndirectedEdge('f', 'g', 2);
	g.AddUndirectedEdge('i', 'g', 6);
	g.AddUndirectedEdge('i', 'c', 2);
	g.AddUndirectedEdge('b', 'h', 11);
	g.AddUndirectedEdge('a', 'h', 8);
	g.AddUndirectedEdge('h', 'g', 1);
	g.AddUndirectedEdge('d', 'f', 14);



 	// auto wut = MST_Prim3(g);
	auto wut2 = MST_PrimW(g);
	auto n = wut2.Head;
	int TOTAL = 0;
	while (n){
		auto e = n->Data;
		std::cout << "(" << e->From->Data << "," << e->To->Data << ") w: " << e->Weight << std::endl;
		TOTAL += e->Weight;
		n = n->Next;
	}
	std::cout << "TOTAL: " << TOTAL << std::endl;
	int db = 1;

}

int main(){

  std::cout << "Kruskal's Algorithm: " << std::endl;
  Figure23_1();

  std::cout << std::endl << "Prim's Algorithm: " << std::endl;
  Figure23_5();
}
