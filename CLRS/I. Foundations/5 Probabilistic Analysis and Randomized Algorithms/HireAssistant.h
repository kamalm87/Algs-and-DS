#pragma once

#include <random>
#include <time.h>
#include "MergeSort.h"

#include <iostream>


/*
	PERMUTE-BY-SORTING(A)
	1.	n = A.length
	2.	let P[1..n] be a new array
	3.	for i = 1 to n
	4.		P[i] = RANDOM(1,n^3)
	5.	sort A, using P as sort keys
*/

template <typename T>
T* PermuteBySorting(T* A, size_t n){
	Index<int>* P  = new Index<T>[n];
	std::srand(time(0));
	for (int i = 0; i < n; i++){
		P[i] = Index<int>(i, std::rand() % (n*n*n));
	}

	MergeSort(P, 0, 4);
	T* B = new T[n];
	
	for (int i = 0; i < n; i++)
		B[i] = A[P[i].index.first];
	
	return B;
}


template<typename T>
struct Index{
	Index<T>(){}
	Index<T>(int index, T data) : index(std::make_pair(index, data)){}
	std::pair<int, T> index;

	bool operator<(const Index<T>& rhs) const{ return this->index.second < rhs.index.second; }
	bool operator==(const Index<T>& rhs) const{ return this->index.second == rhs.index.second; }
	bool operator!=(const Index<T>& rhs) const{ return !(this->index.second == rhs.index.second); }
	bool operator>(const Index<T>& rhs) const{ return !(this->index.second < rhs.index.second) && !(this->index.second == rhs.index.second); }
};




template<typename T>
void exchange(T* A, size_t i, size_t j){
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

template <typename T>
void RandomizeInPlace(T* A, size_t n){
	std::srand(time(0));
	for (size_t i = 0; i < n; i++){
		int randumb = std::rand() % n+i;
		
		int stfu = std::rand() % (n - i);
		
		int normalized = randumb < n - 1 ? randumb : n - 1;

		std::cout << normalized << "\t" << stfu <<  std::endl;
		exchange(A, i, normalized);
	}	
}