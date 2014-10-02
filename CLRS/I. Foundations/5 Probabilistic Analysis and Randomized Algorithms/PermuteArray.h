#pragma once
// Change this to location of MergeSort.h
#include "MergeSort.h"
// Below two headers for pseudo-random number generator and seeding the RNG
#include <random>
#include <time.h>

// Returns a permuted array based on sorting index values by an associated randomly generated variable
template <typename T>
T* PermuteBySorting(T* A, size_t n){
	std::srand(time(nullptr));
	IndexPair<int>* P = new IndexPair<int>[n];
	
	for (size_t i = 0; i < n; i++)
		P[i] = IndexPair<int>(i, Random(0, n*n*n));
	
	MergeSort(P, n);
	T *B = new T[n];
	for (size_t i = 0; i < n; i++)
		B[i] = A[P[i].Index];
	return B;
}

// Permutes an array in place
template <typename T>
void RandomizeInPlace(T *A, size_t n){
	for(size_t i = 0; i < n; i++)
		Swap(A, i, Random(i,n));
}


// Based on methods from:
// http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
size_t Random(size_t low, size_t high){
	int r;
	const unsigned int range = high - low;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	do{
		r = std::rand();
	} while (r >= limit);
	return static_cast<size_t>(low + (r / buckets));
}

template <typename T>
void Swap(T *A, size_t i, size_t j){
	T t = A[i];
	A[i] = A[j];
	A[j] = t;
}

// Represents an Pair with a generic value and an index.
// Defines comparison operator for sorting by the Value, which is assumed to be
// generated randomly through a method
template <typename T>
struct IndexPair{
	IndexPair(size_t i = 0, T d = T()) : Value(d), Index(i){}
	size_t Index;
	T Value;
	bool operator<(const IndexPair<T> &rhs) const { return this->Value < rhs.Value; };
};
