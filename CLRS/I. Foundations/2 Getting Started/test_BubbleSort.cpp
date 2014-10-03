#include "BubbleSort.h"

void testBubbleSort(){
	int* A = new int[6]{1, 2, 3, 4, 5, 6};
	int* B = new int[5]{ 2, 3, 8, 6, 1 };

	auto b0 = B[0];
	auto b1 = B[1];
	auto b2 = B[2];
	auto b3 = B[3];
	auto b4 = B[4];
	BubbleSort(B, 5);

	auto c0 = B[0];
	auto c1 = B[1];
	auto c2 = B[2];
	auto c3 = B[3];
	auto c4 = B[4];


	auto a0 = A[0];
	auto a1 = A[1];
	auto a2 = A[2];
	auto a3 = A[3];
	auto a4 = A[4];
	auto a5 = A[5];

	BubbleSort(A, 6);

	auto d0 = A[0];
	auto d1 = A[1];
	auto d2 = A[2];
	auto d3 = A[3];
	auto d4 = A[4];
}

int main(){
	testBubbleSort();
}
