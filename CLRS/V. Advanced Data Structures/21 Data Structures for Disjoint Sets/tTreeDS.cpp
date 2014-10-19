#include "treeDS.h"
#include <iostream> 

// Tests the Disjoint-Set operations on Figures 21.4 and 21.5 from the text
void t(){
    DisjointSet<char> ds;

    ds.MakeSet('c');
    ds.MakeSet('h');
    ds.MakeSet('e');
    ds.MakeSet('b');
    
    ds.MakeSet('f');
    ds.MakeSet('d');
    ds.MakeSet('g');

    ds.Union('c','e');
    ds.Union('c','h');
    ds.Union('c','b');
    ds.Union('f','d');
    ds.Union('f','g');

    ds.Union('e', 'g');


     /*
   ds.FindSet('c');
   ds.FindSet('h');
   ds.FindSet('e');
   ds.FindSet('b');
   ds.FindSet('f');
   ds.FindSet('d');
   ds.FindSet('g');
   */

   std::cout << ds.FindSet('d')->Data << ", " << ds.FindSet('g')->Data << std::endl;

   auto rc = ds.map['c']->Rank;
   auto pc = ds.FindSet('c')->Data; 
 
   auto rh = ds.map['h']->Rank;
   auto ph = ds.FindSet('h')->Data; 

   
   auto re = ds.map['e']->Rank;
   auto pe = ds.FindSet('e')->Data; 


   auto rb = ds.map['b']->Rank;
   auto pb = ds.FindSet('b')->Data; 


   auto rf = ds.map['f']->Rank;
   auto pf = ds.FindSet('f')->Data; 


   auto rd = ds.map['d']->Rank;
   auto pd = ds.FindSet('d')->Data; 

   
   auto rg = ds.map['g']->Rank;
   auto pg = ds.FindSet('g')->Data; 


  std::cout << "c -> " << rc << " " << "P: " << pc << std::endl;     

  std::cout << "h -> " << rh << " " << "P: " << ph << std::endl;     
  
  std::cout << "e -> " << re << " " << "P: " << pe << std::endl;    
  
  std::cout << "b -> " << rb << " " << "P: " << pb << std::endl;    
  
  std::cout << "f -> " << rf << " " << "P: " << pf << std::endl;    
  
  std::cout << "d -> " << rd << " " << "P: " << pd << std::endl;    
  
  std::cout << "g -> " << rg << " " << "P: " << pg << std::endl;    
   
    int db = 1;
}

int main(){
    t();
}
