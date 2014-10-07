#pragma once

namespace KNM_DS{
	
	template <typename T>
	stuct MinMaxPair{
		MinMaxPair(T min, T max): Min(min), Max(max){}
		T Min, Max;
	}


	template <typename T>
	MinMaxPair<T> MinMax(T* A, size_t n){
		T min, max, tempMin, tempMax;
		size_t i;
		if (n % 2 != 0){
			min = max = A[0];
			i = 1;
		}
		else{
			if (A[0] < A[1]){
				min = A[0];
				max = A[1];
			}
			else{
				max = A[0];
				min = A[1];
			}
			i = 2;
		}
	
		for (i; i < n; i += 2){
			if (A[i] < A[i + 1]){
				tempMin = A[i];
				tempMax = A[i + 1];
			}
			else{
				tempMin = A[i + 1];
				tempMax = A[i];
			}
			if (tempMin < min)
				min = tempMin;
			if (tempMax > max)
				max = tempMax;
		}
	
		return MinMaxPar<T>(min, max);
	}


	template <typename T>
	T Minimum(T* A, size_t n){
		T min = A[0];
		for (int i = 1; i < n; i++){
			if (min > A[i])
				min = A[i];
		}
		return min;
	}	

	template <typename T>
	T Maximum(T* A, size_t n){
		T max = A[0];
		for (int i = 1; i < n; i++){
			if (max < A[i])
				max = A[i];
		}
		return max;
	}


	// A wrapper to offset '- 1' for 0-based index and encapulsate a minor implementation detail ('p' parameter)
	template <typename T>
	T RandomizedSelect(T *A, size_t n, size_t i){
		return RandomizedSelect(A, 0, n - 1, i - 1);
	}


	template <typename T>
	T RandomizedSelect(T* A, size_t p, size_t r, size_t i){
		if (p == r)
			return A[p];
		size_t q = RandomizedPartition(A, p, r);
		size_t k = q - p;	// no '+ 1' offset because 0-based index
		if (i == k){
			return A[q];
		}
		else if (i < k){
			return RandomizedSelect(A, p, q - 1, i);
		}
		else return RandomizedSelect(A, q + 1, r, i - k);
	}

	template <typename T>
	T RandomizedSelect(T* A, size_t p, size_t r, size_t i){
		if (p == r)
			return A[p];
		size_t q = RandomizedPartition(A, p, r);
		size_t k = q - p;	// no '+ 1' offset because 0-based index
		if (i == k){
			return A[q];
		}
		else if (i < k){
			return RandomizedSelect(A, p, q - 1, i);
		}
		else return RandomizedSelect(A, q + 1, r, i - k);
	}


	template <typename T>
	size_t RandomizedPartition(T *A, size_t p, size_t r){
		size_t i = Random(p, r);
		Swap(A, i, r);
		return Partition(A, p, r);
	}

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

}
