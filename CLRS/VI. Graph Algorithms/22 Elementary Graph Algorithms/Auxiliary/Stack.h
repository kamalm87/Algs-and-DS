#pragma once
#include "DynamicArray.h"

// TODO: Handle cases where the stack is emptied then used again.
template <typename T>
	class Stack{
		size_t top;
		DynamicArray<T> A;


	public:
		Stack(size_t capacity = 2): A(DynamicArray<T>(capacity)), top(0){}

		bool Empty(){
			if (top == 0)
				return true;
			return false;
		}
		
		// CHECK: This should naively fix the empty stack case. NEED TO TEST (11/2/2014)
		void Push(T x){
			A[top++] = x;
		}

		T Pop(){
			if (!Empty()){
				--top;
				return A[top];
			}
		}

		T Top(){
			return A[top-1];
		}
};
