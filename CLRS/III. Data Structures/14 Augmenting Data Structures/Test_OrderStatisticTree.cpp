// Assumes that this file is in the same folder--modify if necessary
#include "OrderStatisticTree.h"

// For console result output
#include <iostream>
// For comparison actual tree height to theoeretical bounds/ O() complexity
#include <cmath>
// Use the project's namespace
using namespace KNM_DS

// Creates an OrderStatisticTree (OST) containing 2,000,000 elements from the sequence 0, to 1,999,999
// From that OST:
//  - it queries the rank of an element contained within the OST and one that is not.
//  - it selects 4 indices from the OST, 3 of which are in the OST, and one which isn't. 
// (Note: the indices are 0-based, and -1 is returned for elements that are not contained within an OST. )
void test_OrderStatisticTree(){


	OrderStatisticTree<int> ost;
	// Note that ost.NIL's data is being changed from the integer default, which is the minimum integer
	// value into -1, which will indicate that a selected order-index does not exist in the OrderStaticTree
	ost.NIL->Data = -1;

	// Insert 2 million elements into ost, 0 to 1,999,999 in ascending order
	for (int i = 0; i < 2000000; i++)
		ost.Insert(i);

	std::cout << "0-based Ranking: " << std::endl;
	std::cout << "1 million's rank is: " << ost.OS_Rank(ost.Search(1000000)) << std::endl;
	std::cout << "2 million's rank is: " << ost.OS_Rank(ost.Search(2000000)) << std::endl;
	std::cout << "The selected 1th-indexed element's data is: " << ost.OS_Select(1)->Data << std::endl;
	std::cout << "The selected 500th-indexed element's data is: " << ost.OS_Select(500)->Data << std::endl;
	std::cout << "The selected 10,001th-indexed element's data is: " << (ost.OS_Select(10001)->Data) << std::endl;
	std::cout << "The selected 1,000,000,000th-indexed element's data is: " << ost.OS_Select(1000000000)->Data << std::endl;
	int ostCount = ost.Count();
	int ostMin = ost.Minimum()->Data;
	int ostMax = ost.Maximum()->Data;
	double ostHeight = ost.Height();
	double logOfCount = log2(ostCount + 1);
	double theoereticalUpperBound = 2 * logOfCount;
	int OPTIONAL_DEBUG_BREAKPOINT_POSITION = 1; 
}

// (For use with the test14_1_Examples() function )
// Creates Figure 14.1 (page 340) from the textbook, by inserting 
// the elements contained in the figure in ascending order 
// Elements: { 3, 7, 10, 12, 14, 14, 16, 17, 19, 20, 21, 21, 26, 28, 30, 35, 38, 39, 41, 47 }
// (Note: duplicate entries intentional)
// (Note: The resulting tree is rooted differently from the book than encountered in tests) 
OrderStatisticTree<int>* CreateFigure14_1_ASC(){
	OrderStatisticTree<int> *ret = new OrderStatisticTree<int>();
	ret->Insert(3);
	ret->Insert(7);
	ret->Insert(10);
	ret->Insert(12);
	ret->Insert(14);
	ret->Insert(16);
	ret->Insert(14);
	ret->Insert(17);
	ret->Insert(21);
	ret->Insert(19);
	ret->Insert(20);
	ret->Insert(21);
	ret->Insert(47);
	ret->Insert(41);
	ret->Insert(26);
	ret->Insert(30);
	ret->Insert(28);
	ret->Insert(38);
	ret->Insert(35);
	ret->Insert(39);

	return ret;
}

// Covers the examples from 14.1 in CRLS 
// (Note the the indices are 0-based)
void test14_1_Examples(){
	auto Figure14_1 = CreateFigure14_1_ASC();
	auto select17thIndexedElement = Figure14_1->OS_Select(17);
	// Assumes that the generic type has an ostream << operation, which int does by default
	// (This really returns the node, then Data returns the generic Data type)
	std::cout << "Indexed node value at rank i = 17 is: " << select17thIndexedElement->Data << std::endl;
	// (Note there is a wrapper, so the below call really searches for
	//  and returns a Node containing either the element or NIL,
	//  which represents a dummy empty pointer, then calls OS_Rank
	//  with the returned Node. If the node is not found, then -1 will be returned )
	auto getRankOfNodeContaining38 = Figure14_1->OS_Rank(38);
	// This type returns an int
	std::cout << "The rank index of the node containing " << 38 << " is: i = " << getRankOfNodeContaining38; 


	int OPTIONAL_DEBUG_BREAKPOINT_POSITION = 1;
}

// Optional--for a simple test program
int main(){
	test_OrderStatisticTree();
	test14_1_Examples();	
}
