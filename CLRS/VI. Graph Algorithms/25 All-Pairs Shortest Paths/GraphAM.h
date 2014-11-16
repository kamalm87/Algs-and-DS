#pragma once
#include "Auxiliary/Set.h"
#include "Auxiliary/Map.h"
#include "Auxiliary/Matrix.h"
#include <limits>

// Where 
//    - T := the data representing vertex node values
//    - W := the data representing edge weights, with the assumption
//           that is is a numeric type, supporting the 
//           std::numeric_limits<W>::max() operation 
template <typename T, typename W = int>
class GraphAM{
public: 
  GraphAM(){
    infinity = std::numeric_limits<W>::max();
  }
  
  void ChangeNoPathValue( W val ){ NO_PATH_AMOUNT = val; }

  GraphAM( size_t initialCapacity, W def = std::numeric_limits<W>::max() ){ 
    NO_PATH_AMOUNT = def;
    infinity = def;
    edges = Matrix<W>( initialCapacity, initialCapacity, NO_PATH_AMOUNT); 
  }

  bool AddVertex( T u ){

    if (V.ContainsKey(u)){
      return false;
    }
    else{

      V[u] = V.Count() - 1; // ' - 1' to offset the NIL
      int index = V[u];
      if (edges.Rows() < V.Count() ){
        edges.Resize( V.Count() * 2, V.Count() * 2, NO_PATH_AMOUNT); 
      }
      edges[index][index] = 0;
    }
  }

  bool AddEdge( T u, T v, W w ){
    if( !V.ContainsKey(u) || !V.ContainsKey(v) ){
       return false;
    }
    else{
      int uI = V[u], vI = V[v];
      edges[uI][vI] = w;
   } 
  }

  // Assumes that the matrix is a square matrix
  Matrix<W> ExtendShortestPaths( Matrix<W> & L){ 
    size_t n = L.Rows();
    Matrix<W> Lprime = Matrix<W> ( n, n, Infinity() );

    for ( size_t i = 0; i < n; i++ ){
      for ( size_t j = 0; j < n; j++ ){
        Lprime[i][j] = Infinity(); 
        for( size_t k = 0; k < n; k++){
           Lprime[i][j] = Min( Lprime[i][j], Sum( L[i][k] , L[k][j] ) );
        }
      }
    }
    return Lprime;
  }
 
  
  Matrix<W> SlowAllPairsShortestPaths( Matrix<W> &L ){
  
    size_t n = L.Rows();

    Matrix<W> l = L;

    for( size_t m = 1; m < n - 1; m++ ){
      l = ExtendShortestPaths( l );
    }
    return l;
  }
  
  Matrix<W> FasterAllPairsShortestPaths ( Matrix<W> &L ){
    size_t n = L.Rows();

    Matrix<W> l = L * L;
    size_t m = 1;
    while ( m < n){
      
      l = ExtendShortestPaths ( l );
      m *= 2;
    }
    return l;
  }

  Matrix<W> FloydWarshal ( Matrix<W> &L ){

    size_t n = L.Rows();
    Matrix<W> Dj = L, Dk;
    
    for ( size_t k = 0; k < n; k++ ){
      Dk = Matrix<W> ( L.Rows(), L.Rows(), Dk.Infinity() ); 
      for ( size_t i = 0; i < n; i++ ){
        for ( size_t j = 0; j < n; j++ ){
          Dk[i][j] = Min ( Dj[i][j], Sum( Dj[i][k], Dj[k][j] ) );
        }
      }
      Dj = Dk;
    }    
    
    return Dk;
  }

  Matrix<bool> TransitiveClosure(){
    size_t n = V.Count();
    // tJ represents t ^ ( k - 1), where the "exponent" represents the
    // current iteration of the process 
    Matrix<bool> tJ = Matrix<bool>( n, n );

    for ( size_t i = 0; i < n; i++ ){
      for ( size_t j = 0; j < n; j++ ){
        if ( i == j || edges[i][j] != edges.Infinity() ) 
          tJ[i][j] = true;
        else
          tJ[i][j] = false; 
      }
    }
    
    Matrix<bool> tK;
    for ( size_t k = 0; k < n; k++ ){
       tK = Matrix<bool>( n, n); 
       for ( size_t i = 0; i < n; i++ ){
          for ( size_t j = 0; j < n; j++ ){
            tK[i][j] = tJ[i][j] ||  ( tJ[i][k] && tJ[k][j] );       
          }
       }
       tJ = tK;
    }

    return tK;
  }

  W Infinity(){
    return infinity;
  }

  W NO_PATH_AMOUNT = std::numeric_limits<W>::max();
  Mapping< T, int > V;
  Matrix<W> edges;

// ENCAPSULATE AFTER WORKING 
 private:
  
  W infinity;

  
  // Uses the representative value for 'Infinity' as an upper bound
  W Sum ( W x, W y ){

    // This case assumes either x + Infinity ( same for y ) or Infinity + Infinity
    // which is assumed to be defined as equaling Infinity for all possible values of x
    if ( x == Infinity() || y == Infinity() ){
      return Infinity();
    }
    else{

      // This case assumes that there's overflow with either one
      // or both of values being near the representative for infinity
      // , which would result in the sum overflowing for the underlying
      // data type, W
     
     
      if ( x > 0 && y > 0 && ( x + y ) < 0 ){
        return Infinity();
      }
      else{
        // Otherwise: return the sum of the two parameters, with the assumption
        // that the addition operator is well-defined for the type W
        return x + y;
      }
    }
  }

  W Min( W x, W y ){
    if ( x < y )
      return x;
    else
      return y;
  }

  W Max ( W x, W y ){
    if ( x > y)
      return x;
    else
      return y;
  }
};
