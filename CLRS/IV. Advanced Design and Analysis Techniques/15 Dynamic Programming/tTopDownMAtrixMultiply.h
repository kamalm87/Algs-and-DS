#include "TopDownMatrixMultiply.h"

void t(){
	DynamicArray<int> p;
	p.Insert(30);
	p.Insert(35);
	p.Insert(15);
	p.Insert(5);
	p.Insert(10);
	p.Insert(20);
	p.Insert(25);

	for( int i = 0; i < p.Length(); i++)
		std::cout << p[i] << ", ";
	
	auto m = MemoizedMatrixChain(p);
	m.M.PrintEVERYTHINGDOG();
	m.S.PrintEVERYTHINGDOG();
}

int main(){
	t();
}


