#pragma once
#include "LinkedList.h"
#include "Set.h"
#include "Map.h"
#include <iostream>

template <typename T>
class DisjointSet{

    private:
        template <typename U>
        struct Tree{
            Tree<U> *Parent;
            int Rank;
            U Data;
            Tree(U d): Data(d), Rank(0), Parent(this){}
           };    



    public:

        void MakeSet(T x){
            auto sx = new Tree<T>(x);
            sx->Parent = sx;
            map[x] = sx;
            sets.Insert(sx);
        }

        Tree<T>* FindSet(T x){
           auto s = map[x];
           if(s == s->Parent)
               return s;
           else
               s = FindSet(s->Parent->Data);
            
            /*
            auto s = map[x]; 

            if( s != s->Parent){
                s = FindSet(s->Parent->Data);
            }
            return s->Parent;
            */
        }

        void Union(T x, T y){
            auto sx = FindSet(x);
            auto sy = FindSet(y);

            if(sx == sy) return;

            if(sx->Rank < sy->Rank){
                sx->Parent = sy;
                sets.Delete(sx);

            }
            else if (sx->Rank > sy->Rank)
            {
                sy->Parent = sx;
                sets.Delete(sy);
            }
            else{
                sy->Parent = sx;
                sets.Delete(sy);
                sx->Rank++;
            }
           
        }
        
        Set<Tree<T>* > sets;
        Mapping< T, Tree<T>* > map;
};
