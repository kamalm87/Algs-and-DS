#include "InsertionSort.h"

void testInsertionSort(){
	int* A = new int[6]{5, 2, 4, 6, 1, 3};

	auto a0 = A[0];
	auto a1 = A[1];
	auto a2 = A[2];
	auto a3 = A[3];
	auto a4 = A[4];
	auto a5 = A[5];

	InsertionSort(A, 6);

	auto d0 = A[0];
	auto d1 = A[1];
	auto d2 = A[2];
	auto d3 = A[3];
	auto d4 = A[4];
	auto d5 = A[5];


	int* B = new int[10]{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	auto b0 = B[0];
	auto b1 = B[1];
	auto b2 = B[2];
	auto b3 = B[3];
	auto b4 = B[4];
	auto b5 = B[5];
	auto b6 = B[6];
	auto b7 = B[7];
	auto b8 = B[8];
	auto b9 = B[9];
	InsertionSort(B, 10);
	auto c0 = B[0];
	auto c1 = B[1];
	auto c2 = B[2];
	auto c3 = B[3];
	auto c4 = B[4];
	auto c5 = B[5];
	auto c6 = B[6];
	auto c7 = B[7];
	auto c8 = B[8];
	auto c9 = B[9];
	int BP = 0;
}


int main(){
	testInsertionSort();	
}
