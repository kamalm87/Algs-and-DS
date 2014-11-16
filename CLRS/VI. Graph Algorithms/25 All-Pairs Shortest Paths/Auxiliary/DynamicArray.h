#pragma once
// for size_t
#include <stddef.h>

template <typename T>
class DynamicArray{
public:

  DynamicArray( ) : capacity( 10 ), size( 0 ), A( new T[capacity] ){}
  DynamicArray( size_t c ) : capacity( c ), size( 0 ), A( new T[capacity] ){}
  DynamicArray( size_t c, T d ){
    capacity = c;
    size = 0;
    A = new T[capacity];
    for ( size_t i = 0; i < capacity; i++)
      A[i] = d;
  } 
  void Insert( T data ){
    if( capacity <= size){
      Resize();
    }
    A[size++] = data;
  }
  
  // User beware: assumes that indices, i, are within range of the array's range of allocated
  //              memory! 
  T& operator[]( size_t i ){
    if ( i < capacity ){
      return A[i];
    }
    else{
      // TODO: add logic instead of nothing!
    }
  }

  bool Empty(){
    return size == 0;
  }

  size_t Length(){
    return size;
  }

  size_t Capacity(){
    return capacity;
  }
private:

  // TODO: Could optimize by adding a parametized version to reduce the number
  //       of Resize operations in certain scenarios
  void Resize(){
    T *t = A;
    this->capacity *= 2; 
    for ( size_t i = 0; i < capacity / 2; i++)
      A[i] = t[i];
  }

  size_t capacity;
  size_t size;
  T *A;
};
