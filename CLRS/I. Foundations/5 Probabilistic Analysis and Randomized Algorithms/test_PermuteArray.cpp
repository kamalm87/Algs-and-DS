#include "PermuteArray.h"

// Permutes an 2 arries:
// - an array in descending order
// - an array in ascending order
void createPermutedArrayTest(){

	int *A = new int[10]{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int a0 = A[0];
	int a1 = A[1];
	int a2 = A[2];
	int a3 = A[3];
	int a4 = A[4];
	int a5 = A[5];
	int a6 = A[6];
	int a7 = A[7];
	int a8 = A[8];
	int a9 = A[9];

	int *B = PermuteBySorting(A, 10);

	int b0 = B[0];
	int b1 = B[1];
	int b2 = B[2];
	int b3 = B[3];
	int b4 = B[4];
	int b5 = B[5];
	int b6 = B[6];
	int b7 = B[7];
	int b8 = B[8];
	int b9 = B[9];


	
	int *C = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int c0 = C[0];
	int c1 = C[1];
	int c2 = C[2];
	int c3 = C[3];
	int c4 = C[4];
	int c5 = C[5];
	int c6 = C[6];
	int c7 = C[7];
	int c8 = C[8];
	int c9 = C[9];

	int *D = PermuteBySorting(C, 10);

	int d0 = D[0];
	int d1 = D[1];
	int d2 = D[2];
	int d3 = D[3];
	int d4 = D[4];
	int d5 = D[5];
	int d6 = D[6];
	int d7 = D[7];
	int d8 = D[8];
	int d9 = D[9];

	int DEBUG_BREAK_POINT = 1;


}

int main(){
	createPermutedArrayTest();
}

