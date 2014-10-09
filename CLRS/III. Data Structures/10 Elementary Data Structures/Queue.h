#pragma once
#include "DynamicArray.h"

namespace KNM_DS{
	
	
	template <typename T>
	class Queue{
		size_t length, head, tail;
		DynamicArray<T> A;


	public:
		Queue(size_t capacity = 2) : A(DynamicArray<T>(capacity)), length(0), head(0), tail(0){}

		void Enequeue(T x){
			A[tail] = x;
			if (tail == head)
				tail = 1;
			else
				tail++;
			
			length++;
		}

		T Dequeue(){
			T x = A[head];
			if (head == length)
				head = 1;
			else
				head++;

			length--;
			return x;
		}
	};

}
