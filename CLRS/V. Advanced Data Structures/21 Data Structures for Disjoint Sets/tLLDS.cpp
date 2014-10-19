#include "llDS.h"
#include <iostream>

template <typename T>
void printOutLL(LinkedList<T> *LL){
    auto c = LL->Head;
    std::cout << "L: " << LL->Length << "H->D: " << LL->Head->Data << " T->D: " << LL->Tail->Data << std::endl;
    while(c){
        std::cout << c->Data << ", ";
        c = c->Next;
    }
    std::cout << std::endl;
}


// Tests the Disjoint-Set operations on Figure 21.2 from the text
void testDS(){
    DisjointSet<char> ds;

    ds.MakeSet('a');
    ds.MakeSet('b');
    ds.MakeSet('c');
    ds.MakeSet('d');
    ds.MakeSet('e');
    ds.MakeSet('f');
    ds.MakeSet('g');
    ds.MakeSet('h');
    ds.MakeSet('i');
    ds.MakeSet('j');

    


    ds.Union('a', 'b');
    ds.Union('a', 'c');
    ds.Union('a', 'd');
    printOutLL(ds.map['a']);
    
    ds.Union('e', 'f');
    ds.Union('e', 'g');
    printOutLL(ds.map['e']);

    ds.Union('h', 'i');
    printOutLL(ds.map['h']);
    printOutLL(ds.map['j']);
   
    int db = 11;
}

int main(){
    testDS();
}
