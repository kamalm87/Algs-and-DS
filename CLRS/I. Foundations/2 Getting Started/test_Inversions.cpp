#include "Inversion.h"

void testInversions(){
	// Reverse sorted array, in general, these should have n(n-1)/2 inversions
	// In this case: (6*5)/2 = 15
	int* A = new int[6]{6, 5, 4, 3, 2, 1};
	// The books example, which should have 5 inversions:
	// (2,1), (3, 1), (8, 6), (8, 1), (6,1)
	int* B = new int[5]{ 2, 3, 8, 6, 1 };

	auto bruteForceA = BruteForceInversions(A, 6);
	auto bruteForceB = BruteForceInversions(B, 5);
	auto mergeInversionA = CountInversions(A, 6);
	auto mergeInversionB = CountInversions(B, 5);

	int DEBUG_BREAKPOINT_HERE = 1;
}

int main(){
	testInversions();
}
