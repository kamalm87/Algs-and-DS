#include "OptimalBST.h"

// From Figure 15.9 (page 397)
// p: 
// - 0: 1: .15 2: .10 3: .05 4: .10 5: .20 
// q: 
// - 0: .05 1: .10 2: .05 3: .05 4: .05 5: .10 
void t(){
	DynamicArray<double> p(5),q(5);
	// first insertion is dummy insertion
	p.Insert(-.1);
	p.Insert(.15);
	p.Insert(.10);
	p.Insert(.05);
	p.Insert(.10);
	p.Insert(.20);
	
	q.Insert(.05);
	q.Insert(.10);
	q.Insert(.05);
	q.Insert(.05);
	q.Insert(.05);
	q.Insert(.10);

	auto wut = OptimalBST<double>(p,q,5);
	wut.Root.PrintEVERYTHINGDOG();
	wut.Table.PrintEVERYTHINGDOG();
	auto r = wut.Root;
	ConstructOptimalBST(r,5);
}

// From Exercise 15.5-2 (page 503)
// p: 
// - 0: 1: .04 2: .06 3: .08 4: .02 5: .10 6: .12 7: .14
// q: 
// - 0: .06 1: .06 2: .06 3: .06 4: .05 5: .05 6: .05 7: .05 
void u(){
	DynamicArray<double> p(7), q(7);
	// first insertion is dummy insertion
	p.Insert(-.1);
	p.Insert(.04);
	p.Insert(.06);
	p.Insert(.08);
	p.Insert(.02);
	p.Insert(.10);
	p.Insert(.12);
	p.Insert(.14);

	q.Insert(.06);
	q.Insert(.06);
	q.Insert(.06);
	q.Insert(.06);
	q.Insert(.05);
	q.Insert(.05);
	q.Insert(.05);
	q.Insert(.05);

	auto wut = OptimalBST<double>(p,q,7);
	wut.Root.PrintEVERYTHINGDOG();
	wut.Table.PrintEVERYTHINGDOG();
	auto r = wut.Root;
	ConstructOptimalBST(r,7);

}


int main(){
	t();
	u();
}
