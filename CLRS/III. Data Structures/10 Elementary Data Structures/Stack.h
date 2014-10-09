#pragma once
#include "DynamicArray.h"

namespace KNM_DS{


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
		void Push(T x){
			A.Insert(x);
			top++;
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


}

