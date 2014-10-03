// Where n:= number of elements in the array
template<typename T>
void BubbleSort(T* A, size_t n){
	for (size_t i = 0; i < n - 1; i++){
		for (size_t j = n - 1; j > i; j--){
			if (A[j] < A[j - 1]){
				exchange(j, j - 1, A);
			}
		}
	}
}

template <typename T>
void exchange(size_t i, size_t j, T* A){
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}
