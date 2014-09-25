#pragma once
#include <cmath>
#include <limits>
#include <tuple>

std::tuple<size_t, size_t, int> FindMaxCrossingSubarray(int* A, size_t low, size_t mid, size_t high);
std::tuple<size_t, size_t, int> FindMaximumSubarray(int* A, size_t low, size_t high);


// Psuedo-Code for FindMaxCrossingSubarray
/*
FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
1 left-sum = - infinity
2 sum = 0
3 for i = mid downto low
4	sum = sum + A[i]
5	if sum > left-sum
6		left-sum = sum
7		max-left = i
8 right-sum = -infinity
9 sum = 0
10 for j = mid + 1 to high
11	 sum = sum + A[j]
12	 if sum > right-sum
13		right-sum = sum
14		max-right = j
15 return .max-left;max-right;left-sum C right-sum
*/



std::tuple<size_t, size_t, int> FindMaxCrossingSubarray(int* A, size_t low, size_t mid, size_t high){
	if (high - low == 0){
		return std::tuple<size_t, size_t, int>(0, 0, 0);
	}
	int sum = 0;
	int leftSum = 0;
	int maxLeft = 0;

	for (int i = mid; i > low; i--){
		sum = sum + A[i];
		if (sum > leftSum){
			leftSum = sum;
			maxLeft = i;
		}
	}
	sum = 0;
	int rightSum = 0;
	int maxRight = 0;

	for (int j = mid + 1; j <= high; j++){
		sum = sum + A[j];
		if (sum > rightSum){
			rightSum = sum;
			maxRight = j;
		}
	}
return std::tuple<size_t, size_t, int>(maxLeft, maxRight, (leftSum + rightSum));
}

// Psuedo-Code for FindMaximumSubarray
/*
	FIND-MAXIMUM-SUBARRAY(A,low,high)
	1 if high == low
	2		return (low, high, A[low])  // base case: only one element
	3 else mid = floor( (low+high)/2) )
	4  (left-low, left-high, left-sum) =
	FIND-MAXIMUM-SUBARRAY(A,low,mid)
	5  (right-low, right-high, right-sum) =
	FIND-MAXIMUM-SUBARRAY(A,mid+1,high)
	6  (cross-low, cross-high, cross-sum) =
	FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
	7 if left-sum >= right-sum and left-sum >= cross-sum
	8		return (left-low, left-high, left-sum)
	9 elseif right-sum >= left-sum and right-sum >= cross-sum
	10		return (right-low, right-high, right-sum)
	11 else return (cross-low, cross-high, cross-sum)
*/
std::tuple<size_t, size_t, int> FindMaximumSubarray(int* A, size_t low, size_t high){
	if (high - low <= 1){
		return std::tuple<size_t, size_t, int>(low, high, A[low]);
	}
	else{
		size_t mid = std::ceil((low + high) / 2.0);

		std::tuple<size_t, size_t, int> left = FindMaximumSubarray(A, low, mid);
		std::tuple<size_t, size_t, int> right = FindMaximumSubarray(A, mid + 1, high);
		std::tuple<size_t, size_t, int> cross = FindMaxCrossingSubarray(A, low, mid, high);

		int leftSum = std::get<2>(left);
		int rightSum = std::get<2>(right);
		int crossSum = std::get<2>(cross);

		if (leftSum >= rightSum && leftSum >= crossSum){
			return std::tuple<size_t, size_t, int>(std::get<0>(left), std::get<1>(left), std::get<2>(left));
		}
		else if (rightSum >= leftSum && rightSum >= crossSum){
			return std::tuple<size_t, size_t, int>(std::get<0>(right), std::get<1>(right), std::get<2>(right));
		}
		else{
			return std::tuple<size_t, size_t, int>(std::get<0>(cross), std::get<1>(cross), std::get<2>(cross));
		}
	}
}

void test_SubArray(){
	int* crossingSubarray = new int[17];
	crossingSubarray[0] = 100;
	crossingSubarray[1] = 113;
	crossingSubarray[2] = 110;
	crossingSubarray[3] = 85;
	crossingSubarray[4] = 105;
	crossingSubarray[5] = 102;
	crossingSubarray[6] = 86;
	crossingSubarray[7] = 63;
	crossingSubarray[8] = 81;
	crossingSubarray[9] = 101;
	crossingSubarray[10] = 94;
	crossingSubarray[11] = 106;
	crossingSubarray[12] = 101;
	crossingSubarray[13] = 79;
	crossingSubarray[14] = 94;
	crossingSubarray[15] = 90;
	crossingSubarray[16] = 97;




	int* rA = new int[16];
	for (int i = 0; i < 16; i++){
		rA[i] = crossingSubarray[i + 1] - crossingSubarray[i];
	}

	/*
	for (int i = 0; i < 16; i++){
	std::cout << rA[i] << std::endl;
	}
	*/

	std::tuple<size_t, size_t, int> tup = FindMaximumSubarray(rA, 0, 15);
}
