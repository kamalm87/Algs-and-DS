#pragma once

namespace KNM_DS{

	// Represents a data type of type 'T' with digits type 'U'
	// Digits are accessed using the operator[], from right to left 
	// for the provided <int, int> implementation
	// T is the base data type, U is the 'digit' of T
	// For example, T could be defined as string, while U would be a char
	// ** Need to specialize the operator[] implementations if the 
	// ** base type to digit differs from basic decimal numeric representation
	template <typename T, typename U>
	struct RadixBin{
		T data;
		size_t digits;
		RadixBin() : data(T()), digits(0){}

		// Note: need to implement the below for specific implementations other than <int, int>, as the
		// way digits are structured may differ based on the generic type combination
		RadixBin(T d) : data(d) {}
		U operator[](size_t i);
	};

	// Specialized <int, int> constructor
	RadixBin<int, int>::RadixBin(int d){
		data = d;
		digits = 0;
		int t = d;
		while (t != 0){
			t = t / 10;
			digits++;
		}
	}

	// Specialized <int, int> operator[], assumes digits are right from right to left
	// e.g, 729 : digit = 0 => 9, digit = 1 => 2, digit = 2 => 7
	int RadixBin<int, int>::operator[](size_t i){
		int digits = 0, value = data;
		for (size_t j = 0; j < i; j++)
			value = value / 10;
		value = value % 10;
		return value;
	}

	// RadixSort implementation using the RadixBin<T,U> wrapper struct to sort the data type T
	// Where A is input array, n is number of elements in the array, and d is the number of digits
	// for the maximum element in A
	// RadixSort implementation uses the wrapper generic struct RadixBin<T, U> to perform
	// the digit access logic.
	template <typename T, typename U>
	void RadixSort(RadixBin<T, U>* A, size_t n, size_t d){
		auto w = 1;
		for (size_t i = 0; i < d; i++){
			A = CountingSort(A, n, 10, i);
		}
	}

	// Augmented ContingSort implementation for RadixBin arrays
	// Augmentation: 
	// - modified to use the RadixBin<T, U> generic struct as the input arrays elements 
	// - uses RadixBin's operator[] to access the digits for array C index access/writes
	// Where A is input array, n is number of elements in the array, k is the number of
	// distinct digits, and d is the current digit to sort.
	// Note: encapsulated within the RadixSort as the stable linear sort
	template <typename T, typename U>
	RadixBin<T, U>* CountingSort(RadixBin<T, U>* A, size_t n, size_t k, size_t d){
		RadixBin<T, U> *B = new RadixBin<T, U>[n];
		U* C = new U[k];

		// Note: default constructor for 'U' is assumed to be a minimum
		for (size_t i = 0; i < k; i++)
			C[i] = U();

		for (int j = 0; j < n; j++)
			C[A[j][d]] = C[A[j][d]] + 1;
		for (int i = 1; i < k; i++)
			C[i] = C[i] + C[i - 1];

		for (int j = n - 1; j >= 0; j--){
			B[C[A[j][d]] - 1] = A[j];	// Note: offset ' - 1' to account for 0-based indexing
			C[A[j][d]]--;
		}
		return B;
	}
}