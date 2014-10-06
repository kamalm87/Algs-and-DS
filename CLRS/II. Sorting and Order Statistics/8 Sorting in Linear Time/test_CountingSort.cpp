#include "CountingSort.h"

// Runs through the book's example: Figure 8.2
void test_CountingSort(){
	int* a = new int[8]{2, 5, 3, 0, 2, 3, 0, 3};
	auto b = CountingSort(a, 7, 5);
	auto b0 = b[0];
	auto b1 = b[1];
	auto b2 = b[2];
	auto b3 = b[3];
	auto b4 = b[4];
	auto b5 = b[5];
	auto b6 = b[6];
	auto b7 = b[7];
	auto b8 = b[8];
}


int main(){
	test_CountingSort();
}
