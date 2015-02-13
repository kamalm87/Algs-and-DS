#pragma once
#include "Auxiliary/Matrix.h"
#include <iostream>
#include <limits>

template <typename T>
struct  MatrixChainData{
	MatrixChainData(Matrix<T> m, Matrix<size_t> s): M(m), S(s) {} 
	Matrix<T> M;
	Matrix<size_t> S;
};

template <typename T>
MatrixChainData<T> MemoizedMatrixChain(DynamicArray<T> &p){
	size_t n = p.Length();
	Matrix<T> m(n,n,std::numeric_limits<T>::max());
	Matrix<size_t> s(n,n,0);
	LookupChain(m,p,s,1,n-1);
	return MatrixChainData<T>(m,s);
}

template <typename T>
T LookupChain(Matrix<T> &m, DynamicArray<T> &p, Matrix<size_t> & s, size_t i, size_t j){
	std::cout << "(" << i << "," << j << ")" << std::endl;
	if(m[i][j] < std::numeric_limits<T>::max()){ return m[i][j]; }
	
	if(i==j){ m[i][j] = 0;}
	else{
		for(size_t k = i; k < j; k++){
			T q = LookupChain<T>(m,p,s,i,k) + LookupChain<T>(m,p,s,k+1,j) + p[i-1]*p[k]*p[j];
			if(q < m[i][j]){
				m[i][j] = q;
				s[i][j] = k;
			}
		}		
	}
	return m[i][j];
}	


