template <typename T>
void InsertionSort(T *A, size_t n){
	for (size_t j = 1; j < n; j++){
		T key = A[j];
		size_t i = j - 1;
		while (i >= 0 && A[i] > key){
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}
