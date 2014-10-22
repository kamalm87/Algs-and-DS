#pragma once
	template <typename T>
	class DynamicArray{
		size_t capacity, size;
		T* A;
	public:

	 DynamicArray(size_t size = 2) : capacity(size), A(new T[capacity]), size(0){}

	 size_t Length()  {
		 return size;
	 }

     // Automatically resizes the array if i exceeds the current capacity
     // Note: With great convenience, comes great responsibility!
	 T& operator[](size_t i){
		 if( i < capacity)
             return A[i];
         else
         {
            T *t = A;
		    while( capacity <= i)
                capacity *= 2;
	
            A = new T[capacity];
            for (int i = 0; i < capacity / 2; i++)
		        A[i] = t[i];
			delete[]t;
            return A[i];
         }
	 }

	 void Insert(T a){
		 if (size < capacity)
			 A[size++] = a;
		 else{
			  T *t = A;
			 capacity *= 2;
			 A = new T[capacity];
			 for (int i = 0; i < capacity / 2; i++)
				 A[i] = t[i];

			 A[size++] = a;
			 delete[]t;
		 }
	 }
	
	};


