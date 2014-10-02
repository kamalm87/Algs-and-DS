#include "MaxSubarray.h"

// Creates the array of stock prices from Figure 4.3 in the book. 
int* CreateFigure4_3(){
	int* prices = new int[17];
	prices[0] = 100;
	prices[1] = 113;
	prices[2] = 110;
	prices[3] = 85;
	prices[4] = 105;
	prices[5] = 102;
	prices[6] = 86;
	prices[7] = 63;
	prices[8] = 81;
	prices[9] = 101;
	prices[10] = 94;
	prices[11] = 106;
	prices[12] = 101;
	prices[13] = 79;
	prices[14] = 94;
	prices[15] = 90;
	prices[16] = 97;
	return prices;
}

// Calculates and returns an array of the 'returns' for an array of prices of a generic type
// with a well-defined subtraction operator, where A is the array of prices, and n is the size
// of the array A.
template <typename T>
T* GetReturns(T* A, size_t n){
	T* returns = new int[n - 1];
	for (size_t i = 0; i < n; i++)
		returns[i] = A[i + 1] - A[i];
	return returns;
}

// Tests the FindMaximumSubarray implementation by calculating the returns from Figure 4.3, then 
// inserting the returns into the array to find the optimal holding period
void testMaximumReturnPeriod(){
	auto optimalHoldingPeriod = FindMaximumSubarray(GetReturns(CreateFigure4_3(), 17), 0, 16);

	int DEBUG_BREAK_POINT = 1;
}

int main(){
	testMaximumReturnPeriod();
}
