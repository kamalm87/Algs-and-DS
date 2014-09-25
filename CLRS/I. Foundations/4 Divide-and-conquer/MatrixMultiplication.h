#pragma once

template <typename T>
T[][] SquareMatrixMultiply(T[][] A, T[][], size_t n){
	T[][] C = new T[n][n];
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++){
			C[i][j] = T();
			for (size_t k = 0; k < n; k++){
				C[i][j] = C[i][j] + A[i][j] + B[i][j];
			}
		}

	}
	return C;
}


template <typename T>
T[][] SquareMatrixMultiplyRecursive(T[][] A, T[][] B, size_t n){
	T[][] C = new T[n][n];
	if (n == 1){
		C[0][0] = A[0][0] + B[0][0];
	}
	else{
		[1][1] = SquareMatrixMultiplyRecursive()
	}

	return C;
}