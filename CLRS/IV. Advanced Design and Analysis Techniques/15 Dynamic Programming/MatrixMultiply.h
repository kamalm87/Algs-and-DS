#pragma once
#include "Auxiliary/Matrix.h"
// For debugging small input / PrintOptimalParens
#include <iostream>
// For represenating infinity for generic numeric types T with std::numeric_limits<T>::max()
#include <limits>

// Represents the output of the MatrixChainOrder algorithm where:
// * M := the tabulated computation costs for for a parenthesization at indices i and j 
//   (cost represents the number of scalar multiplications)  
// * S := the tabulated index to split the parenthsizations for indices i and j 
template <typename T>
struct MatrixChainData{
  MatrixChainData(Matrix<T> m, Matrix<size_t> s): M(m), S(s){}
  Matrix<T> M;
  Matrix<size_t> S;
};

// Note: the Matrix class has an overloaded binary * operator, so this function
//       utilizes the existing defined method.
template <typename T>
Matrix<T> MatrixMultiply(Matrix<T> &A, Matrix<T> &B){
  if ( A.Columns() != B.Rows() ){
    std::cout << "Cannot multiply " << A.Columns() << " column matrix by a "
              << B.Rows() << " rows matrix\n";
    std::cout << "Returning an empty default matrix\n";
    return Matrix<T>();
  }
  else{
    std::cout << "Multiplying a " << A.Columns() << " column matrix by a "
              << B.Rows() << " rows matrix and returning the resulting product\n";
    std::cout << "A: " << "(" << A.Rows() << "," << A.Columns() << ") * "
              << "B: " << "(" << B.Rows() << "," << B.Columns() << ") "
              << " -> C: " <<  "(" << A.Rows() << "," << B.Columns() << ")\n";


    return ( A * B );
  }
}

// Complexity:
// * Time: O( N^3 )
// * Storage: O( N^2 )
// Input: a sequence of matrix dimensions, p
//      - Example: The chain of matrices A1 * A2 * A3 with (rows,columns)
//                 such that A1: (10,100), A2: (100,5), A3: (5,50)
//                 would have: p = ( 10, 100, 5, 50)
//      - Assumption: The chain of matrices' dimensions obey the standard laws of matrix multiplication
//      - Notes: Infinity is representated by std::numeric_limits<T>::max(), where T is the templatized type.
//               * Use a templatized type whose max value will never be approached through the algorithm's standard
//                 addition procedures, or 'T' overflow may occur, corrupting the algorithm's output.   
// TODO: improve storage efficiency 
//       * issue: matrices are 0-indexed, the current implementation of the algorithm 
//         wastes a potentially significant amount of space:
//          1) dummy row at for i = 0 and dummy column for j = 0
//          2) matrix representation is space inefficient for both s and m 
template <typename T>
MatrixChainData<T> MatrixChainOrder( DynamicArray<int> p ){
  // Note: will need to alter n if the TODO is applied
  size_t n = p.Length();
  
  Matrix<T> m(n,n,0);
  // s just represents indices, so no templatizing is required
  Matrix<size_t> s(n,n,0);
  
  // Note: will need to alter this entire loop process if the TODO is applied
  for(size_t l = 2; l < n; l++ ){
    for( size_t i = 1; i < n -l + 1; i++ ){
      size_t j = i + l - 1;
      m[i][j] = std::numeric_limits<T>::max(); 
      for( size_t k = i; k < j; k++ ){
        // If either of the tabulated computations contains the representation for infinity, then
        // simply assign q to the representation for infinity to avoid overflow errors.
        // Otherwise, proceed with the algorithm's standard summation procedure for calculating q 
        // * NOTE: There are no checks for whether the algorithm's standard summation procedure
        //         would cause overflow in the case that neither computed tabulation equals the 
        //         representation for infinity
        int q;
        if ( m[i][k] == std::numeric_limits<T>::max() || m[k+1][j] == std::numeric_limits<T>::max() )
           q = std::numeric_limits<T>::max();
        else 
          q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];

        // For debugging purposes on an input size with a relatively small n:
        // std::cout << "m[" << i << "," << j << "]: " << m[i][j] << " q: " << q << "\n"; 
        if ( q < m[i][j] ){
          m[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }
  return MatrixChainData<T>(m,s); 
}

// Note: Will need to alter recursive calls TODO for MatrixChainOrder algorithm implementation is implemented
template <typename T>
void PrintOptimalParens(MatrixChainData<T> &mcd, size_t i, size_t j){
  if ( i == j )
    std::cout << "A" << i;
  else{
    std::cout << "(";
    PrintOptimalParens(mcd,i,mcd.S[i][j]);
    PrintOptimalParens(mcd,mcd.S[i][j]+1,j);
    std::cout << ")";
  }
}
