#include "Stack.h"
using namespace KNM_DS;

// Tests the implementation on Figure 10.1 from the book
void testStack(){

	Stack<int> s;

	s.Push(15);
	s.Push(6);
	s.Push(2);
	s.Push(9);
	s.Push(17);
	s.Push(3);

	int topPop = s.Pop();
	int newTop = s.Top();


	int BP = 1;
}

int main(){
	testStack();
}
