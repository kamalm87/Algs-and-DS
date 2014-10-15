#include <stddef.h>

template <typename T>
class DynamicArray{
public:
        DynamicArray() : capacity(10), size(0), A(new T[capacity]){}
        DynamicArray(int capacity) : capacity(capacity), size(0), A(new T[capacity]){}

        
        void insert(T d){
            if(size + 1 < capacity){
                A[size++] = d; 
            }
            else{
                  T *temp = A;
                capacity *= 2;
                A = new T[capacity];
                
                for(int i = 0; i < capacity / 2; i++)
                    A[i] = temp[i];
                A[size++] = d; 
            }
        }

        T& operator[](size_t i){
            if(i <= capacity)
                return A[i];
            else{
                resize(i);
                return A[i];
            }
                
        }

private:

    // TODO: Make this more efficient!    
    void resize(size_t newSize){
        while(capacity <= newSize){
            capacity *= 2;
        }
        T *temp = A;
        A = new T[capacity];
        for(int i = 0; i < capacity / 2; i++)
            A[i] = temp[i];
    }




    // Variable ordering here is important for intiailizers                     
    size_t capacity, size;
    T *A;
};
