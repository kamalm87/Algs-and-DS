#include "MatrixMultiply.h"

void t(){
  DynamicArray<int> p;
  p.Insert(30);
  p.Insert(35);
  p.Insert(15);
  p.Insert(5);
  p.Insert(10);
  p.Insert(20);
  p.Insert(25);

  MatrixChainData<int> m = MatrixChainOrder<int>(p); 
  m.M.PrintEVERYTHINGDOG();
  m.S.PrintEVERYTHINGDOG();
  PrintOptimalParens(m,1,6);
}

int main(){
  t();
}
