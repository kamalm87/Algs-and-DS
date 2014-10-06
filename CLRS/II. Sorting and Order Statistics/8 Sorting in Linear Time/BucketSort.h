#pragma once
#include "LinkedList.h"
// For floor function
#include <cmath>

namespace KNM_DS{
	template <typename T>
	void BucketSort(T *A, size_t n){
		// Note: pointers to non-pointers, automatically allocated with the default constructor
		LinkedList<T>* B = new LinkedList<T>[n];
		for (int i = 0; i < n; i++)
			B[static_cast<int>(std::floor(n*A[i]))].addToTail(A[i]);
		for (int i = 0; i < n; i++)
			B[i].InsertionSort();
		ConcatenateLinkedListsIntoArray(A, B, n);
	}

	template <typename T>
	void ConcatenateLinkedListsIntoArray(T *A, LinkedList<T>* B, size_t n){
		size_t count = 0;
		for (int i = 0; i < n; i++){
			Node<T> *C = B[i].Head;
			while (C){
				A[count++] = C->Data;
				C = C->Next;
			}
		}
	}
}
