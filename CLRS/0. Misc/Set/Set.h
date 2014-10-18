#include "RBT.h"

template <typename T>
class Set{
public:
    T* Find(T key){
        auto res = rbt.Search(key);
        if(res != nullptr && res->Data == key)
            return &res->Data;
        else
            return nullptr;

    } 
    
    bool Search(T key)
    {
        auto res= rbt.Search(key);

        if(res != nullptr && res->Data == key)
            return true;
        else
            return false;
    }

    void Insert(T x){
        rbt.Insert(x);
    }

    T Minimum(){
        return (rbt.Minimum())->Data;
    }
    
    T Maximum(){
        auto res = (rbt.Maximum())->Data;
        return res;
    }

   T Successor(T x){
        auto n = rbt.Search(x);
        if(n){
            auto res = rbt.Successor(n);
            return res->Data;
        }
        else{
            return T();
        }
   }
    
   bool Delete(T x){
        if(Search(x)){
            Remove(x);
            return true;
        }
        else{
        return false;
        }
   }

   void Remove(T x){
        rbt.Delete(x);
   }

   T Predecessor(T x){
         auto n = rbt.Search(x);
        if(n){
            auto res = rbt.Predecessor(n);
            return res->Data;
        }
        else{
            return T();
        }
     }
private:
    RBT<T> rbt;
};
