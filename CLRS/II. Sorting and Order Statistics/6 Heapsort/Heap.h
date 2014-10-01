// for floor functions
#include <cmath>

namespace KNM_DS{
	
	// Contains the possible types of Heaps supported, which determines the type of internal implemented Insertion/Building/Sorting for a given Heap
	// Options: Min, Max
	namespace HeapType{
		enum HeapType{ Min, Max };
	}

	template <typename T>
	class Heap{
	public:
		// Constructs a heap with an initial inner array capacity, which is 10 by default
		Heap(size_t capacity = 10, HeapType::HeapType type = Max ) : Capacity(capacity), Size(0), HeapSize(0), A(new T[capacity]), Type(type){}
		Heap(HeapType::HeapType type) : Capacity(10), Size(0), HeapSize(0), A(new T[Capacity]), Type(type){}
		// Builds a heap from an array 
		Heap(T* a, size_t n, HeapType::HeapType type = Max) : Capacity(n), Size(n), A(a), Type(type){
			Build();
			HeapSize = n;
		}

		
		// Inserts an element into the heap, perserving the min/max-heap heap property of the class's HeapType
		// In addition, maintains and resizes the internal array to represent the heap, if necessary 
		void Insert(T d){
			if (Size < Capacity){
				// insert into heap AND increment the position of the "next" element to be inserted
				if (Type == Max){
					if (MaxHeapInsert(d))
						Size++;
				}
				else if (Type == Min){
					if (MinHeapInsert(d))
						Size++;
				}
			}
			else{ // double the capacity, and copy over existing elements, then insert new element 
				T* t = A;
				Capacity *= 2;
				A = new T[Capacity];
				for (int i = 0; i < (int)Size; i++)
					A[i] = t[i];
			
				if (Type == Max){
					if (MaxHeapInsert(d))
						Size++;
				}
				else if (Type == Min){
					if (MinHeapInsert(d))
						Size++;
				}
				
				delete []t;			// garbage collection
			}
		}

		// Changes the Heap Type, rebuilds the heap, and resets the heapsize
		void ChangeType(HeapType::HeapType t){
			Type = t;
			HeapSize = Size;
			Build();
			HeapSize = Size;
		}

		// Min-Heap: Sorts keys in descending order
		// Max-Heap: Sorts keys in ascending order
		void Sort(){
			if (Type == Max)
				HeapSort();
			else if (Type == Min)
				HeapSortMIN();
		}

		// Builds either a min or a max heap based on its current type
		void Build(){
			if (Type == Max)
				BuildHeap();
			else if (Type == Min)
				BuildHeapMIN();
		}
	
		// Note: performing an 'inverse' operation corrupts the heap property (e.g, a Min operation on a max-heap)
		// * Will need to invoke Build() to restore the heap property for the current state
		T ExtractMaximum(){
			if (HeapSize == 0) return T();

			if (Type == Max){
				T max = A[0];
				A[0] = A[HeapSize];
				HeapSize = HeapSize - 1;
				Size--;
				MaxHeapify(A, 0);
				return max;
			}
			else{ // if (Type == Min){ // INEFFICIENT: O(LOG(N))
				Sort();
				HeapSize = Size;
				T max = A[0];
				A[0] = A[HeapSize];
				HeapSize = HeapSize - 1;
				Size--;
				MinHeapify(A, 0);
				return max;
			}
		}

		// Note: performing an 'inverse' operation corrupts the heap property (e.g, a Min operation on a max-heap)
		// * Will need to invoke Build() to restore the heap property for the current state
		T ExtractMinimum(){
			if (HeapSize == 0) return T();

			if (Type == Min){
				T min = A[0];
				A[0] = A[HeapSize];
				HeapSize = HeapSize - 1;
				Size--;
				MinHeapify(A, 0);
				return min;
			}
			else{ // if (Type == Max){ // INEFFICIENT: O(LOG(N))
				Sort();
				HeapSize = Size;
				T min = A[0];
				A[0] = A[HeapSize];
				HeapSize = HeapSize - 1;
				Size--;
				MaxHeapify(A, 0);
				return min;
			}
		}

		// Note: performing an 'inverse' operation corrupts the heap property (e.g, a Min operation on a max-heap)
		// * Will need to invoke Build() to restore the heap property for the current state
		T Minimum(){
			if (Type == Min){
				return A[0];
			}
			else {	// Type == Min
				Sort();	// INEFFICIENT: O(LOG(N))
				T t =  A[HeapSize];
				Build();
				return t;
			}
		}

		// Note: performing an 'inverse' operation corrupts the heap property (e.g, a Min operation on a max-heap)
		// * Will need to invoke Build() to restore the heap property for the current state
		T Maximum(){
			if (Type == Max)
				return A[0];
			else { // Type == Min
				// INEFFICIENT: O(LOG(N))
				Sort();
				return A[HeapSize];
			}
		}

		// (For debugging)
		// Reads the value of an an index on the inner array if exists, otherwise returns the generic type's default value
		// if the index parameter exceeds the size of indices existing in the inner array 
		T operator[](size_t i){
			if (i < Size)
				return A[i];
			else
				return T();
		}

	private:

		// Acceses the parent of an index
		size_t Parent(size_t i){
			return (size_t)std::floor(i / 2.0);
		}

		// Acceses the left-child of an index
		size_t Left(size_t i){
			return i == 0 ? 1 : i * 2 + 1; // special case if i = 0
		}

		// Acceses the right-child of an index
		size_t Right(size_t i){
			return ((i + 1) * 2);
		}

		// Places an element to index i, and swaps it unti it does not violate the Min-Heap property, if necessary
		bool DecreaseKey(size_t i, T k)
		{	
			if (k > A[i]){
				return false;
			}
			A[i] = k;
			while (i >= 0 && (A[Parent(i)] > A[i])){
				Swap(i, Parent(i));
				i = Parent(i);
			}
			return true;
		}

		// Inserts an element into a Min-Heap, preserving the MinHeap-property
		bool MinHeapInsert(T k){
			HeapSize = HeapSize + 1;
			A[HeapSize] = T();
			return DecreaseKey(HeapSize, k);
		}

		// Places an element to index i, and swaps it unti it does not violate the Max-Heap property, if necessary
		bool IncreaseKey(size_t i, T k){
			if (k < A[i]){
				return false;
			}
			A[i] = k;
			while (i >= 0 && (A[Parent(i)] < A[i])){
				Swap(i, Parent(i));
				i = Parent(i);
			}
			return true;
		}

		// Inserts an element into a Max-Heap, preserving the MaxHeap-property
		bool MaxHeapInsert(T k){
			HeapSize++;
			return IncreaseKey(HeapSize - 1, k);
		}

		// A recursive function, which maintains the Max-Heap property
		void MaxHeapify(T *A, size_t i){
			size_t largest = -1, l = Left(i), r = Right(i);

			if (l <= HeapSize && (A[l] > A[i])){
				largest = l;
			}
			else{
				largest = i;
			}

			if (r <= HeapSize && (A[r] > A[largest])){
				largest = r;
			}

			if (largest != i){
				Swap(largest, i);
				MaxHeapify(A, largest);
			}
		}

		// A recursive function, which maintains the Min-Heap property
		void MinHeapify(T *A, size_t i){
			size_t smallest = i, l = Left(i), r = Right(i);

			if (l <= HeapSize && (A[l] < A[i])){
				smallest = l;
			}

			if (r <= HeapSize && (A[r] < A[smallest])){
				smallest = r;
			}

			if (smallest != i){
				Swap(smallest, i);
				MinHeapify(A, smallest);
			}
		}

		// Swaps the values of two indices in the internal array, A.
		// Note: No bounds checking.
		void Swap(size_t i, size_t j){
			T t = A[i];
			A[i] = A[j];
			A[j] = t;
		}

		// Builds a Max-Heap
		void BuildHeapMIN(){
			HeapSize = Size - 1;
			for (int i = (int)std::floor((Size / 2.0)) - 1; i >= 0; i--)
				MinHeapify(A, i);
		}

		// Builds a Max-Heap
		void BuildHeap(){
			HeapSize = Size - 1;
			for (int i = (int)std::floor((Size / 2.0)) - 1; i >= 0; i--)
				MaxHeapify(A, i);
		}

		// Sorts the elements of a Max-Heap in ascending order
		void HeapSort(){
			BuildHeap();
			for (int i = HeapSize; i > 0; i--){
				Swap(0, i);
				HeapSize = HeapSize - 1;
				MaxHeapify(A, 0);
			}
		}

		// Sorts the elements of a Min-Heap in descending order
		void HeapSortMIN(){
			BuildHeapMIN();
			for (int i = HeapSize; i > 0; i--){
				Swap(0, i);
				HeapSize = HeapSize - 1;
				MinHeapify(A, 0);
			}
		}

		HeapType::HeapType Type;
		size_t Capacity;
		size_t Size;
		size_t HeapSize;
		T* A;
	};
}


