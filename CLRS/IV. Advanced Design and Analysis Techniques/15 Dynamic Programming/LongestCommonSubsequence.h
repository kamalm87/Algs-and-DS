#include "Auxiliary/Matrix.h"
#include "Auxiliary/DynamicArray.h"
#include <string>


template <typename T, typename U>
struct Pair{
	Pair(T a, U b): A(a), B(b) {}
	T A;
       	U B;
};

template <typename T>
Pair<Matrix<std::string>,Matrix<size_t>> LCS_Length(DynamicArray<T> &X, DynamicArray<T> &Y){
	size_t m = X.Length(), 
	       n = Y.Length();

	Matrix<std::string> 	b(m+1,n+1,"");
        Matrix<size_t>		c(m+1,n+1,0);	
	
	for(size_t i = 1; i <= m; i++){
		for(size_t j = 1; j <= n; j++){
/* For debugging if necessary. Ensures that the indices are mapped correctly
			std::cout << "(" << i << "," << j << ") " << "X[" << i 
				  << "]: " << X[i] << ", Y[" << j << "]: " << Y[j]	       
				  << std::endl;
*/			// since the computation tabulation is offset by +1
			// must offset the references to sequence values by -1
			if(X[i-1]==Y[j-1]){
				c[i][j] = c[i - 1][ j - 1 ] + 1;
				// b[i,j] "up-left shift"
				b[i][j] = "<^-";		 
			}
			else if(c[i - 1][j] >= c[i][j - 1]){
				c[i][j] = c[i - 1][j];
				// b[i,j] "up shift"
				b[i][j] = "^";		 
			} else{
				c[i][j] = c[i][j-1];
				// b[i,j] "left shift"
				b[i][j] = "<-";		 
			}

		}
	}
	return Pair<Matrix<std::string>,Matrix<size_t>> (b,c);
}

template <typename T>
void PrintLCS(Matrix<std::string>  &b, DynamicArray<T> &X, size_t i, size_t j ){
	if(i == 0 || j == 0 ) return;

	if(b[i][j] == "<^-"){
		PrintLCS<T>(b,X,i-1,j-1);
		// Note: -1 to offset for 0-indexing
		std::cout << X[i-1];
	}
	else if (b[i][j] == "^"){
		PrintLCS<T>(b,X,i-1,j);
	} else{
		PrintLCS<T>(b,X,i,j-1);
	}

}
