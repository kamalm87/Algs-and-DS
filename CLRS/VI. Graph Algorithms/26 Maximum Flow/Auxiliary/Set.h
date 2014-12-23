#pragma once
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

    bool Empty(){
      if(rbt.Count() == 0)
        return true;  
      else
        return false;
    }

    size_t Count(){
      return rbt.Count();
    }

    friend bool operator==(Set<T> &l, Set<T> & r){
      if(l.rbt.Count() != r.rbt.Count()){
        return false;
      }
      else{
        auto s1 = l.Minimum(), s2 = r.Minimum();

        while(s1 && s2){
          if( s1 != s2){
            return false;
          }else{
            s1 = l.Successor(s1);
            s2 = r.Successor(s2);
          }
        }
        if( !s1 && !s2)
          return true;
        else
          return false;
      }
    }

    // Dummy, no logical value
    friend bool operator!=(Set<T> &l, Set<T> &r){
      return !(l == r );
    }

    // Dummy, no logical value
    friend bool operator<(const Set<T> &l, const Set<T> &r){
      return true;        
    }
private:
    RBT<T> rbt;
};
