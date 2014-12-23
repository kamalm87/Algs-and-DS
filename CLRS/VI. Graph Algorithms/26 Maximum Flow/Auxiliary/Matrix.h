#pragma once
#include "DynamicArray.h"
#include <iostream>
// for numerical representative value for 'Infinity'
#include <limits>


// TODO: Add in cases to account for handling cases with mathematical operations
//       on the assigned representative value for Infinity  
template <typename T>
class Matrix{
  public:
    
    Matrix() : cols(0), rows(0) {}

    Matrix(size_t r, size_t c, T d = T()){
      rows = r;
      cols = c;

      // Set rows: 
      M = DynamicArray< DynamicArray<T> > (rows);

      // Set columns and intialize defaults:
      // * Either intialize each matrix element to the default type value or a specified default
      // * TODO: Optimize constructor for efficient construction with a specified default 
      if( d == T()) {
        for(int i = 0; i < rows; i++)
          M[i] = DynamicArray<T>(cols);
      }
      else{
        for(int i = 0; i < rows; i++)
          M[i] = DynamicArray<T>(cols, d);
      }
    }

    void Resize( size_t r, size_t c, T d = T() ){
      DynamicArray< DynamicArray<T> > t = M;
      M = DynamicArray< DynamicArray<T> >( r );

      if( d != T() ){
        for( int i = 0; i < r; i++)
          M[i] = DynamicArray<T>(c, d);
      }
      else{
        for( int i = 0; i < r; i++)
          M[i] = DynamicArray<T>(c);
      }

      for( int i = 0; i < rows; i++ ){
        for( int j = 0; j < cols; j++){
          M[i][j] = t[i][j];
        }
        std::cout << std::endl;
      }
     
      rows = r;
      cols = c; 
    }

  void PrintEVERYTHINGDOG(){
    int rowN = 1;

    std::cout << std::endl;
    std::cout << "Displaying the contents of a " << rows << " X " << cols << " Matrix:" << std::endl; 
    for(int i = 0; i < rows; i++){
      std::cout << "\t R" << rowN << ": ";
      for(int j = 0; j < cols; j++){
        if ( M[i][j] != infinity){ 
          if ( M[i][j] >= 0 ) std::cout << " ";
          std::cout << M[i][j] << ( j != cols - 1 ? "," : "\n");
        }
        else{
         std::cout << " *" << ( j != cols - 1 ? "," : "\n");
        }
      }
      rowN++;
    }   
    std::cout << std::endl;
  }
  
  size_t Rows(){
    return rows;
  }

  size_t Columns(){
    return cols;
  }


  void ScalarMultiply( T m){
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++)
        M[i][j] *= m;
    }
  }


  // Returns an empty matrix if the matrix dimensions
  // do not support matrix multiplication
  Matrix<T> Multiply( Matrix<T>& B){
    auto A = *this;
    if ( A.Columns() != B.Rows() ){ 
      return Matrix<T>();
    } 
    else{
      Matrix<T> C = Matrix<T>( this->Rows(), B.Columns() );
      for(int i = 0; i < this->Rows(); i++){
        for(int j = 0; j < B.Columns(); j++){
          
          T sum = T();
          for(int k = 0; k < B.Rows(); k++){
            sum += (*this)[i][k] * B[k][j];
          }
          C[i][j] = sum;
        }
      }
      return C;
    }
  }

  Matrix<T> Tranpose(){
    Matrix<T> M = Matrix<T>(this->Columns(), this->Rows());
    for( int i = 0; i < this->Rows(); i++){
      for( int j = 0; j < this->Columns(); j++){
        M[j][i] = (*this)[i][j];
      }
    }
    return M; 
  } 

  void AddToEach( T a ){
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++)
        M[i][j] += a;
    }
  }

  void SubtractFromEach( T s ){
    AddToEach( -s );
  }

 DynamicArray<T>& operator[](size_t i){
  if( i < rows )
    return M[i];
    // TODO: put case for when invoked row is out of range!
 }

 friend Matrix<T> operator*( Matrix<T> &l, Matrix<T> &r) {
    
  if( l.Columns() != r.Rows()){
    return Matrix<T>();
  }
  else{
    Matrix<T> C = Matrix<T>( l.Rows(), r.Columns() ); 
    for(int i = 0; i < l.Rows(); i++){
      for(int j = 0; j < r.Columns(); j++){
          
        T sum = T();
        for(int k = 0; k < r.Rows(); k++){
          sum = Sum ( sum,   Prod( l[i][k] , r[k][j]) );
        }
          C[i][j] = sum;
        }
      }
      return C;
  } 
 }
  
 static T Infinity(){
    return infinity;
 }

private:
  
  static T Sum( T x, T y ){
    if ( x == Infinity() || y == Infinity() ){
      
    }
    else{
      if ( x > 0 && y > 0 && ( x + y ) < 0 ){
        return Infinity();
      }
      else{  
        return Infinity();
      }
   } 
  } 

  static T Prod( T x, T y ){
    if ( x == Infinity() || y == Infinity() ){
      return Infinity();
    }
    else{
      if ( x > 0 && y > 0 && ( x * y < 0 )){

        return Infinity();
      }
      if ( ( x > 0 && y < 0 && ( x * y > 0 ) ) 
            ||
           ( y > 0 && x < 0 && ( x * y > 0 ) )
           )
      {
        return Infinity();
      }
      else{
        return x * y;
      }
    }
  }
  
 const static T infinity = std::numeric_limits<T>::max();
 size_t rows, cols;
 DynamicArray< DynamicArray<T> > M;
};


template <>
void Matrix<bool>::PrintEVERYTHINGDOG(){
   int rowN = 1;

    std::cout << std::endl;
    std::cout << "Displaying the contents of a " << rows << " X " << cols << " Matrix:" << std::endl; 
    for(int i = 0; i < rows; i++){
      std::cout << "\t R" << rowN << ": ";
      for(int j = 0; j < cols; j++){
        if ( M[i][j] == true ){ 
          std::cout << 1 << ( j != cols - 1 ? "," : "\n");
        }
        else{
         std::cout << "0" << ( j != cols - 1 ? "," : "\n");
        }
      }
      rowN++;
    }   
    std::cout << std::endl;

}
