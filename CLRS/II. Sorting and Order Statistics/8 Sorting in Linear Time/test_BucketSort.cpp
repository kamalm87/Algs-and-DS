#include "BucketSort.h"

// Tests the implementation of the BucketSort algorithm on Figure 8.4
void testBucketSort(){
	double *A = new double[10]{.78, .17, .39, .26, .72, .94, .21, .12, .23, .68};
	double a0 = A[0];
	double a1 = A[1];
	double a2 = A[2];
	double a3 = A[3];
	double a4 = A[4];
	double a5 = A[5];
	double a6 = A[6];
	double a7 = A[7];
	double a8 = A[8];
	double a9 = A[9];
	double a10 = A[10];

	KNM_DS::BucketSort(A, 10);

	double c0 = A[0];
	double c1 = A[1];
	double c2 = A[2];
	double c3 = A[3];
	double c4 = A[4];
	double c5 = A[5];
	double c6 = A[6];
	double c7 = A[7];
	double c8 = A[8];
	double c9 = A[9];

	int DEBUG_BREAK_POINT = 1;
}

int main(){
	testBucketSort();
}
