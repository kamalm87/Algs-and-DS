#include "IntervalTree.h"
using namespace KNM_DS;

// The following 3 functions create interval trees using
// the intervals in Figure 14.4 from CLRS (pg 350)
// CreateFigure14_4__NO_ROTATIONS: This trees structure closely replicates the books
// CreateFigure14_4__ASC: Inserts Intervals of sequentially increasing low endpoints
// CreateFigure14_4__DESC: Inserts Intervals of sequentially decreasing low endpoints
IntervalTree<int> CreateFigure14_4__NO_ROTATIONS(){
	IntervalTree<int> it;
	// h:0-
	it.Insert(16, 21);
	// h:1-
	it.Insert(8, 9);
	it.Insert(25, 30);
	// h:2-
	it.Insert(5, 8);
	it.Insert(15, 23);
	it.Insert(17, 19);
	it.Insert(26, 26);
	// h:3-
	it.Insert(0, 3);
	it.Insert(6, 10);
	it.Insert(19, 20);
	return it;
}
IntervalTree<int> CreateFigure14_4__ASC(){
	IntervalTree<int> it;
	it.Insert(0, 3);
	it.Insert(5, 8);
	it.Insert(6, 10);
	it.Insert(8, 9);
	it.Insert(15, 23);
	it.Insert(16, 21);
	it.Insert(17, 19);
	it.Insert(19, 20);
	it.Insert(25, 30);
	it.Insert(26, 26);

	return it;
}
IntervalTree<int> CreateFigure14_4__DESC(){
	IntervalTree<int> it;
	it.Insert(26, 26);
	it.Insert(25, 30);
	it.Insert(19, 20);
	it.Insert(17, 19);
	it.Insert(16, 21);
	it.Insert(15, 23);
	it.Insert(8, 9);
	it.Insert(6, 10);
	it.Insert(5, 8);
	it.Insert(0, 3);
	return it;
}

// Tests various interval operations on Figure 14.4 from the book
// (TODO: Implementation maintenance for Max with deletions)
void Test_Figure14_4_Operations(){
	// Creates Figure 14.4 using in order, ascedencing, and descending insetions
	auto inOrder = CreateFigure14_4__NO_ROTATIONS();
	auto asc = CreateFigure14_4__ASC();
	auto desc = CreateFigure14_4__DESC();

	Node<int>* i1 = inOrder.Search(22, 25);
	Node<int>* a1 = asc.Search(22, 25);
	Node<int>* d1 = desc.Search(22, 25);
	bool foundIni1 = i1 != inOrder.NIL;
	bool foundIna1 = a1 != asc.NIL;
	bool foundInd1 = d1 != desc.NIL;

	Node<int>* i2 = inOrder.Search(11, 14);
	Node<int>* a2 = asc.Search(11, 14);
	Node<int>* d2 = desc.Search(11, 14);
	bool foundIni2 = i2 != inOrder.NIL;
	bool foundIna2 = a2 != asc.NIL;
	bool foundInd2 = d2 != desc.NIL;


	Node<int>* i3 = inOrder.Search(18, 18);
	Node<int>* a3 = asc.Search(18, 18);
	Node<int>* d3 = desc.Search(18, 18);
	bool foundIni3 = i3 != inOrder.NIL;
	bool foundIna3 = a3 != asc.NIL;
	bool foundInd3 = d3 != desc.NIL;

	int DEBUG_BREAK_POINT_COULD_GO_HERE = 1;
}
}

int main(){
	Test_Figure14_4_Operations();
}
