// For seeding srand's time
#include <time.h>

void testQuickSort(){
	// Pre-Sorted array, and indexed values:
	int *A = new int[8]{2, 8, 7, 1, 3, 5, 6, 4};
	
	int a0 = A[0];
	int a1 = A[1];
	int a2 = A[2];
	int a3 = A[3];
	int a4 = A[4];
	int a5 = A[5];
	int a6 = A[6];
	int a7 = A[7];
	QuickSort(A, 8);

	// Sorted values:
	int b0 = A[0];
	int b1 = A[1];
	int b2 = A[2];
	int b3 = A[3];
	int b4 = A[4];
	int b5 = A[5];
	int b6 = A[6];
	int b7 = A[7];

	int BREAKPOINT_HERE = 1;
}

void testRandomizedQuickSort(){
	// Seed for pseudo-random number generation
	srand(time(nullptr));
	// Pre-Sorted array, and indexed values:
	int *A = new int[8]{2, 8, 7, 1, 3, 5, 6, 4};
	
	int a0 = A[0];
	int a1 = A[1];
	int a2 = A[2];
	int a3 = A[3];
	int a4 = A[4];
	int a5 = A[5];
	int a6 = A[6];
	int a7 = A[7];
	RandomizedQuicksort(A, 8);

	// Sorted values:
	int b0 = A[0];
	int b1 = A[1];
	int b2 = A[2];
	int b3 = A[3];
	int b4 = A[4];
	int b5 = A[5];
	int b6 = A[6];
	int b7 = A[7];

	int BREAKPOINT_HERE = 1;
}

int main(){
	testQuickSort();
	testRandomizedQuickSort();
}
