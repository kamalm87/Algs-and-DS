#include "Auxiliary/DynamicArray.h"
#include "Auxiliary/Matrix.h"
#include <limits>

template <typename T>
struct OptimalBSTPair{
	Matrix<T> Table;
	Matrix<size_t> Root;
	OptimalBSTPair<T> ( Matrix<T> t, Matrix<size_t> r) : Table(t), Root(r) {}
};

// T is assumed to be a numerical type with float-like support for percentages
// p := probabilities of the keys
// q := probabilities of the dummies
// n := number of keys
// Assumptions:
// 		* q ( 0, ..., n - 1) contain the dummy probabilities
// 		* p ( 1, ..., n - 1) contain the key probabilties, with p[0] being inserted as a dummy node to skip over
// 		 - if it is desired to use no dummy indexed value for p, then change line 33's p[j] to p[j-1] and the algorithm
// 		   should function properly, assumming that the current implementation is valid
template <typename T>
OptimalBSTPair<T> OptimalBST( DynamicArray<T> &p, DynamicArray<T> &q, size_t n){
	Matrix<T> e(n+2,n+1,T()), w(n+2,n+1,T());
	Matrix<size_t>	root(n+1,n+1,0);
	for(size_t i = 1; i <= n+1; i++){
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for( size_t l = 1; l <= n + 1; l++){
		for( size_t i = 1; i <= n - l + 1; i++){
			size_t j = i + l - 1;
			e[i][j] = std::numeric_limits<T>::max(); // assignment repesents infinity
			w[i][j] = w[i][j-1] + p[j] + q[j];
			for( size_t r = i; r <= j; r++){
				T t = e[i][r-1] + e[r+1][j] + w[i][j];
				if(t < e[i][j]){
					e[i][j] = t;
					root[i][j] = r;
				}
			}			
		}
	}
	return OptimalBSTPair<T>(e,root);
}

void ConstructOptimalBST1(Matrix<size_t> &root, size_t i, size_t j){
size_t m = root[i][j];
if( i == m){
	std::cout << "left child d[" << m - 1 << "] of k[" << m << "]" << std::endl;
} else {
	std::cout << "left child k[" << root[i][m-1] <<  "] of k[" << m << "]" << std::endl;
	ConstructOptimalBST1(root,i,m-1);
}

if ( j == m){
	std::cout << "right child d[" << m << "] of k[" << m << "]" << std::endl;
} else {

	std::cout << "right child k[" << root[m+1][j] << "] of k[" << m << "]" << std::endl;
	ConstructOptimalBST1(root,m+1,j);
}

}
void ConstructOptimalBST(Matrix<size_t> &root, size_t n){
	std::cout << "root at k[" << root[1][n] << "]" << std::endl;
	ConstructOptimalBST1(root,1,n);

}




