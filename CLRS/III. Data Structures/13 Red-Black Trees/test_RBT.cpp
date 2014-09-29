// assumes that this file is in the same folder--modify if necessary
#include "RedBlackTree.h"
// Below 3 for displaying/comparing results
#include <cmath>
#include <iostream>
#include <string>

// use this projects associated namespace 
using namespace KNM_DS;


// prints the general state of a RBT at given point of time, comparing it to the simplified
// and theoretical bounds: (count, height, log(N+1), 2*log(N+1), where N is the count of the 
// RBT at a given point of time, and log is base-2
template <typename T>
void print_out_tree_height_info(RBT<T> &rbt, const std::string & msg = ""){
	int count = rbt.Count();
	int height = rbt.Height();
	double logTree = std::log2(count + 1);
	double limit = logTree * 2;

	if (msg != "")
		std::cout << msg << std::endl;
	std::cout << "RBT elements: " << count << " RBT height: " << height << " Log2(N+1): " << logTree << " Upper Bound: 2*LOG2(N+1): " << limit << std::endl;
}

// * Creates a Red-Black tree, 
// * Inserts 1,000,000 elements, testing if the tree's height is at or below the theoretical upper bound
// * Deletes 700,000 elements, testing if the tree's height is at or below the theoretical upper bound
// * Inserts 2,000,000 elements, testing if the tree's height is at or below the theoretical upper bound
// * Deletes 1,290,000 elements, testing if the tree's height is at or below the theoretical upper bound
void testBlackTreeHeights(){

	RBT<double> rbt;

	double inputSize = 1000000;
	for (double i = 0; i < inputSize; i++)
		rbt.Insert(i);

	print_out_tree_height_info(rbt);

	for (double i = 0; i < 700000; i++)
		rbt.Delete(i);

	print_out_tree_height_info(rbt);

	for (double d = 1000000; d < 3000000; d++)
		rbt.Insert(d);

	print_out_tree_height_info(rbt);


	for (double d = 700000; d < 2999000; d++)
		rbt.Delete(d);

	print_out_tree_height_info(rbt);


	for (double d = 7000000; d < 14000000; d++)
		rbt.Insert(d);
	print_out_tree_height_info(rbt);


	int END_DEBUG = 1;
}


// to independently run the test in a simple program
int main(){
	testBlackTreeHeights();
	int DEBUG_BREAKPOINT_HERE = 1;
	return 0;
}