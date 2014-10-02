// For floor function
#include <cmath>
// For random
#include <random>

// Assumes that the indices are contained within the array
// No bounds checking
template <typename T>
void Swap(T *A, size_t i, size_t j){
	T t = A[j];
	A[j] = A[i];
	A[i] = t;
}

template <typename T>
size_t Partition(T *A, size_t p, size_t r){
	T x = A[r];

	size_t i = p, j = p;
	for (j; j < r; j++){
		if (A[j] < x){
			Swap(A, i, j);
			i++;
		}
	}

	Swap(A, i, r);
	return i == 0 ? 1 : i;
}

// Wrapper for Quicksort, where n is the number of elements in the array
template <typename T>
void QuickSort(T *A, size_t n){
	QuickSort(A, 0, n - 1);
}
template <typename T>
void QuickSort(T *A, size_t p, size_t r){
	if (p < r){
		size_t q = Partition<T>(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}

// Wrapper for RandomizedQuicksort, where n is the number of elements in the array
template <typename T>
void RandomizedQuicksort(T *A, size_t n){
	RandomizedQuicksort(A, 0, n - 1);
}

template <typename T>
void RandomizedQuicksort(T *A, size_t p, size_t r){
	if (p < r){
		size_t q = RandomizedPartition(A, p, r);
		RandomizedQuicksort(A, p, q - 1);
		RandomizedQuicksort(A, q+1, r);
	}
}

template <typename T>
size_t RandomizedPartition(T *A, size_t p, size_t r){
	size_t i = Random(p, r);
	Swap(A, i, r);
	return Partition(A, p, r);
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
}:
