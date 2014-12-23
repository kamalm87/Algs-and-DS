#pragma once
#include "DynamicArray.h"
    

template <typename T>
class Queue{
	size_t length, head, tail;
	DynamicArray<T> A;


	public:
		Queue(size_t capacity = 2 ) : A(DynamicArray<T>(capacity)), length(0), head(0), tail(0){}

        // TODO: Deal/test "wrap-around" cases, i.e: Head > Tail
		void Enqueue(T x){
			A[tail] = x;
			if (tail == head)
				tail = 1;
			else
				tail++;
			
			length++;
		}

        // TODO: Deal/test "wrap-around" cases, i.e: Head > Tail
		T Dequeue(){
			T x = A[head];
			if (head == length)
				head = 1;
			else
				head++;

			length--;
            
            // Resets positions to the beginning of the array if the Queue
            // becomes empty
            if(length == 0){
                head = tail = 0;
            }
			return x;
        }

        bool Empty(){
            if (length == 0) 
                return true;
            else
                return false;
        }
};
