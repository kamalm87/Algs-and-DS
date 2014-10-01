#include "Heap.h"

// Runs heap methods on Figure 6.1:
// Array elements of the figure: 16, 14, 10, 8, 7, 9, 3, 2, 4, 1
// Uses a Max and a Min Heap
void test_BookExample(){
	// Max-Heap, inserting elements into it increasing order
	Heap<int> h1;

	h1.Insert(1);
	h1.Insert(2);
	h1.Insert(3);
	h1.Insert(4);
	h1.Insert(7);
	h1.Insert(8);
	h1.Insert(9);
	h1.Insert(10);
	h1.Insert(14);
	h1.Insert(16);

	int h1_0 = h1[0];
	int h1_1 = h1[1];
	int h1_2 = h1[2];
	int h1_3 = h1[3];
	int h1_4 = h1[4];
	int h1_5 = h1[5];
	int h1_6 = h1[6];
	int h1_7 = h1[7];
	int h1_8 = h1[8];
	int h1_9 = h1[9];
	
	// Sort elements in ascending order
	h1.Sort();
	int h1_0_ = h1[0];
	int h1_1_ = h1[1];
	int h1_2_ = h1[2];
	int h1_3_ = h1[3];
	int h1_4_ = h1[4];
	int h1_5_ = h1[5];
	int h1_6_ = h1[6];
	int h1_7_ = h1[7];
	int h1_8_ = h1[8];
	int h1_9_ = h1[9];
	int* a = new int[10]{1, 2, 3, 4, 7, 8, 9, 10, 14, 16};
	
	// Creates a max-heap from a sorted array
	Heap<int> h2(a, 10);


	int h2_0 = h2[0];
	int h2_1 = h2[1];
	int h2_2 = h2[2];
	int h2_3 = h2[3];
	int h2_4 = h2[4];
	int h2_5 = h2[5];
	int h2_6 = h2[6];
	int h2_7 = h2[7];
	int h2_8 = h2[8];
	int h2_9 = h2[9];

	// Sort elements in ascending order
	h2.Sort();
	int h2_0_ = h2[0];
	int h2_1_ = h2[1];
	int h2_2_ = h2[2];
	int h2_3_ = h2[3];
	int h2_4_ = h2[4];
	int h2_5_ = h2[5];
	int h2_6_ = h2[6];
	int h2_7_ = h2[7];
	int h2_8_ = h2[8];
	int h2_9_ = h2[9];

	// Creates a min-heap from a arbitrarily order array
	int* b = new int[10]{4, 3, 16, 2, 1, 8, 10, 9, 14, 7};
	Heap<int> h3(b, 10, Min);

	h3.Insert(1);
	h3.Insert(2);
	h3.Insert(3);
	h3.Insert(4);
	h3.Insert(7);
	h3.Insert(8);
	h3.Insert(9);
	h3.Insert(10);
	h3.Insert(14);
	h3.Insert(16);

	int h3_0 = h3[0];
	int h3_1 = h3[1];
	int h3_2 = h3[2];
	int h3_3 = h3[3];
	int h3_4 = h3[4];
	int h3_5 = h3[5];
	int h3_6 = h3[6];
	int h3_7 = h3[7];
	int h3_8 = h3[8];
	int h3_9 = h3[9];

	// Sort elements in ascending order
	h3.Sort();
	int h3_0_ = h3[0];
	int h3_1_ = h3[1];
	int h3_2_ = h3[2];
	int h3_3_ = h3[3];
	int h3_4_ = h3[4];
	int h3_5_ = h3[5];
	int h3_6_ = h3[6];
	int h3_7_ = h3[7];
	int h3_8_ = h3[8];
	int h3_9_ = h3[9];

	// Extract the max element from a max-heap 
	h1.Build(); // Note: need to restore Max-Heap property after sorting
	auto extractFromMax = h1.ExtractMaximum();
	// New max is:
	auto newMax = h1.Maximum();

	// Extract the min element from a min-heap
	h3.Build(); // Note: need to restore Max-Heap property after sorting
	auto extractFromMin = h3.ExtractMinimum();
	// New min is:
	auto newMin = h3.Minimum();


	// Corruption ahead:
	// Extract the min element from a max-heap!!!
	auto extractMinFromMAX = h1.ExtractMinimum();
	auto newMinFromMax = h1.Minimum();

	int BREAK_POINT_GOES_HERE = 1;

}

int main(){
	test_BookExample();
}
