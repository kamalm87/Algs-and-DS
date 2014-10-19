#pragma once
#include "Auxiliary/LinkedList.h"
#include "Auxiliary/Set.h"
#include "Auxiliary/Map.h"
#include <iostream>

template <typename T>
class DisjointSet{
public:
    DisjointSet(){}  
    
    void MakeSet(T x){
        auto ll = new LinkedList<T>(x);
        sets.Insert(ll);
        map[x] = ll;
    }
    
    void Union(T x, T y){
        auto sx = map[x];
        auto sy = map[y];

        if(sx->Length >= sy->Length){
            sx->Tail->Next = sy->Head;
            sx->Tail = sy->Head;
            auto c = sy->Head;
            while(c){
                c->Prev = sx->Head;
                c = c->Next;
            }
            sx->Length += sy->Length;
            sets.Remove(sy);
        }
        else{
            sy->Tail->Next = sx->Head;
            sy->Tail = sx->Head;
            auto c = sy->Head;
            while(c){
                c->Prev = sy->Head;
                c = c->Next;
            }
            sy->Length += sx->Length;
            sets.Remove(sx);
        }
    }

    LinkedList<T>* FindSet(T x){
        return map[x];
    } 

    // TODO: revert
// TEMP
// private:    

    Set<LinkedList<T>*> sets;    
    Mapping<T, LinkedList<T>*> map;

};
