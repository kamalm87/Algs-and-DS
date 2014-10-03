// Note these only make sense with identity sequences, so the generic templated data has little point! 

// For floor function
#include <cmath>

template <typename T>
size_t BruteForceInversions(T* A, size_t n){
	
	size_t inversions = 0;
	for (size_t i = 0; i < n - 1; i++){
		for (size_t j = i + 1; j < n; j++){
			if (A[i] > A[j])
				inversions++;
		}
	}
	return inversions;
}

// Wrapper for CountInversions, where n is the number of elements in the array
template <typename T>
size_t CountInversions(T* A, size_t n){
	return CountInversions(A, 0, n - 1);
}

// Actual recursive function, note it's based on 0-based indexing
template <typename T>
size_t CountInversions(T* A, size_t p, size_t r){
	if (p < r){
		size_t x, y, z;
		size_t q = static_cast<size_t>(std::floor((p + r) / 2.0));
		x = CountInversions(A, p, q);
		y = CountInversions(A, q + 1, r);
		z = MergeInversions(A, p, q, r);
		return x + y + z;
		
	}
	else{
		return 0;
	}
}

template <typename T>
size_t MergeInversions(T* A, size_t p, size_t q, size_t r){
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	T *L = new T[n1], *R = new T[n2];

	for (size_t i = 0; i < n1; i++)
		L[i] = A[p + i];

	for (size_t i = 0; i < n2; i++)
		R[i] = A[q + i + 1];

	size_t i = 0, j = 0, inversions = 0, k = p;

	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			j++;
			inversions = inversions + (n1 - i);
		}
		k++;
	}

	if (i != n1){
		for (i; i < n1; i++)
			A[k++] = L[i];
	}
	else if (j != n2){
		for (j; j < n2; j++)
		{
			A[k++] = R[j];
			inversions = inversions + (n1 - i);
		}
			
	}
	return inversions;
}
