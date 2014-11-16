#pragma once
#include <cmath>
#include "DynamicArray.h" 

// For a constructor that takes a generic Set<T> that's the same T as the Heap
#include "Set.h"

enum HeapType {Min, Max};

// For non-pointer generic types:
//    - overload the '<' comparison operator for the type, if necessay
// For pointer generic types: 
//    - specialize the template to return a comparison on the underlying data type
//    - ( refer to the specialization in:
//        ../CLRS/VI. Graph Algorithms/24 Single-Source ShortestPaths/Graph_SP.h
//        for the genric type: Vertex<T>* for an example )
template <typename T>
struct T_Less{
  bool operator() (const T &l, const T &r ) const{
    return l < r;
  }
};

// Implements either a min or a max heap, based on the value of the internal HeapType value,
// using T_Less<T> to perform comparisons on the genric type, T.
template <typename T>
class Heap{
public:  

  // Constructor for use with generic sets  
  Heap( Set<T> &S, HeapType type = Min){
    A = DynamicArray<T>( static_cast<size_t>(S.Count()) );
    Type = type;
    T b = S.Minimum(), e = S.Maximum();
    while ( b < e ){
      A.Insert(b);

      b = S.Successor(b);
      if ( b == e ){
        A.Insert(b);
      }
    }
    Size = A.Length();
    HeapSize = Size - 1;
    Build();
  } 

  // Default: Min-Heap using a default-constructed DynamicArray
  //        - Pass in 'Max' to construct a Max-Heap  
  Heap(HeapType type = Min){
   Capacity = 0;
   Size = 0;
   HeapSize = 0;
   Type = type; 
  }

  // Default: Assign an initial capacity for DynamicArray construction
  //         - By default, a Min-Heap is constructed, set the second parameter
  //           to construct a Max-Heap
  Heap (size_t capacity, HeapType type = Min ){
   Capacity = capacity;
   A = DynamicArray<T>(Capacity);
   Size = 0;
   HeapSize = 0;
   Type = type; 
  }

  // Returns the Current HeapType of the Heap
  HeapType GetType(){
    return Type;
  }

  // TODO: Change/optimize, currently this should be ~ LOG(N), which may be undesirable
  //    - Possibility: use Increase/Decrease-Key to reduce amortized performance
  // ****
  // Inserts an element into the Heap, and ensures that underlying array containing the
  // data does not violate the min/max-heap property, depending on the HeapType Type
  // value of the Heap
  void Insert(T data){
    A.Insert(data);
    Size++;
    if( Type == Min)
      BuildHeapMin();
    else if ( Type == Max )
      BuildHeapMax();
  }

  void Build(){
    if( Type == Min )
      BuildHeapMin();
    else if ( Type == Max )
      BuildHeapMax();    
  }

  HeapType ChangeType ( HeapType type ){
    Type = type;
    return Type;
  }

  T Extract(){
    if ( HeapSize == 0 && Size >= 1 ) Build(); 

    if ( Type == Min)
      return ExtractMin();
    else if ( Type == Max )
      return ExtractMax();    
  }

  T Top(){
    return A[0];
  }

  void Sort(){
    if ( Type == Min )
      HeapSortMin();
    else if ( Type == Max )
      HeapSortMax();
  }
  
  bool Empty(){
    return Size == 0; 
  }
  
  // TODO: Why have IncreaseKey and DecreaseKey? Just implemented for completion's sake currently!
  bool IncreaseKey ( size_t i, T k ){
    if( tLess( k, A[i] ) ){
      return false;
    }
    else{
      A[i] = k;
      while ( i >= 0 && tLess( A[ Parent(i) ], A[i] ) ){
        Swap( i, A[Parent(i)] );
        i = Parent(i);
      }
     return true; 
    }
  }
  
  bool DecreaseKey ( size_t i, T k ){
    if ( tLess( A[i], k ) ){
      return false;
    }
    else {
      A[i] = k;
      while ( i >= 0 && tLess( A[i], A[ Parent(i) ] ) ){
        Swap( i, A[ Parent(i) ] );
      }
    }
  }

  // TODO: encapsulate after debugged
  DynamicArray<T> A;
  size_t Capacity;
  size_t Size;

// Internal methods: 
  T ExtractMax(){
    if (Size == 0){
      return T();
    }
    else if (HeapSize == 0){ 
      Size--;
      return A[0];
    }
    else{
      T max = A[0];
      A[0] = A[HeapSize];
      HeapSize--;
      Size--;
      MaxHeapify(0);
      return max;
    }
  }

  T ExtractMin(){
    if (Size == 0){
      return T();
    }
    else if (HeapSize == 0){ 
      Size--;
      return A[0];
    }
    else{
      T min = A[0];
      A[0] = A[HeapSize];
      HeapSize--;
      Size--;
      MinHeapify(0);
      return min;
    }
  }

  size_t Parent ( size_t i ) {
    return static_cast<size_t>( std::floor( i / 2.0 ) ); 
  }

  size_t Left( size_t i ){
   return i == 0 ? 1 : ( i * 2 + 1 ); // special case if i == 0
  }

  size_t Right( size_t i  ){
    return ( ( i + 1 ) * 2 );
  }

  void Swap( size_t i, size_t j ){
    T temp = A[j];
    A[j] = A[i];
    A[i] = temp;
  }
  
  void MinHeapify( size_t i ){
    size_t smallest = i, l = Left(i), r = Right(i);

    if ( l <= HeapSize && tLess( A[l], A[i] ) ){
      smallest = l;
    }

    if ( r <= HeapSize && tLess( A[r], A[smallest] )){
      smallest = r;
    }

    if( smallest != i ){
      Swap(smallest, i);
      MinHeapify(smallest);
    }
  }

   void MaxHeapify( size_t i ){
    size_t largest = i, l = Left(i), r = Right(i);

    if ( l <= HeapSize && tLess( A[i], A[l] ) ){
      largest = l;
    }

    if ( r <= HeapSize && tLess( A[largest], A[r] )){
      largest = r;
    }

    if( largest != i ){
      Swap(largest , i);
      MaxHeapify( largest );
    }
  }
 
  void BuildHeapMin(){
    HeapSize = Size - 1;
    for( int i = static_cast<int>( std::floor( ( Size / 2.0 ) ) - 1 ); i >= 0; i--)
      MinHeapify(i);
  }
 
  void BuildHeapMax(){
     HeapSize = Size - 1;
     for( int i = static_cast<int>( std::floor( ( Size / 2.0 ) ) - 1 ); i >= 0; i--)
      MaxHeapify(i);
  }
 
  void HeapSortMin(){
    BuildHeapMin();
    for( int i = HeapSize; i > 0; i--){
      Swap(0, i);
      HeapSize = HeapSize - 1;
      MinHeapify(0);
    }
  }

  void HeapSortMax(){
    BuildHeapMax();
    for( int i = HeapSize; i > 0; i--){
      Swap(0, i);
      HeapSize = HeapSize - 1;
      MaxHeapify(0);
    }
  }

// Data members:
  size_t HeapSize;
  HeapType Type;
  T_Less<T> tLess;
};
