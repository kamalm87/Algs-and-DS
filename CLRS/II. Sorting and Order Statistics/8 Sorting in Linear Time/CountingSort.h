#pragma once
namespace KNM_DS{

	// Note: only whole numbers really make sense with this sorting algorithm
	template <typename T>
	T* CountingSort(T* A, size_t n, size_t k){
		T* B = new T[n + 1];
		T* C = new T[k];

		for (size_t i = 0; i <= k; i++)
			C[i] = 0;

		// C[i] now contains the number of elements equal to i
		for (size_t j = 0; j <= n; j++)
			C[A[j]] = C[A[j]] + 1;


		// C[i] now contains the number of elements less than or equal to i
		for (size_t i = 0; i <= k; i++)
			C[i] = i == 0 ? C[i] : C[i] + C[i - 1];

		for (int j = n; j >= 0; j--){
			// Need to offset the output index's position by 1
			// to account for 0-based indexing
			B[C[A[j]] - 1] = A[j];
			C[A[j]] = C[A[j]] - 1;
		}
		return B;
	}	
}


