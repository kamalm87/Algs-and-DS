#include "Set.h"

// Tests the set<T> implementation with:
// 1.T = int
// - Inserts 1,000,000 elements
// - Finds min/max
// - Successor(min), Predecessor(max) 
// - Deletes even elements
// *
// 2.T = char
// - Inserts 'a' to 'z', 'A' to 'Z'
// - Finds min, max
// - Succesor(min), Predecessor(max)
void testSet(){
    Set<int> s;

    // Create a set of ints, with 1,000,000 elements
    for(int i = 1; i < 1000001; i++)
        s.Insert(i);

    // Should be 1
    int min = s.Minimum();
    
    // Should be 1,000,000
    int max = s.Maximum();

    // Should be 2
    int minPlus1 = s.Successor(min);
    // Should be 999,999
    int maxMinus1 = s.Predecessor(max);

    // Delete all even numbers from the set
    for(int i = 1; i < 1000001; i++){
        if(i%2 == 0)
            s.Delete(i);
    }
    // The set should now contain only 500,000 elements
    int db = 1;

    // Char set with with A-Z, a-z
    Set<char> sChars;

    // Insert 'A' to 'Z'
    for(int i = 65; i < 91; i++)
        sChars.Insert(static_cast<char>(i));

    // Insert 'a' to 'z'
    for(int i = 97; i < 123; i++)
        sChars.Insert(static_cast<char>(i));

    // Should be 'A'
    char cMin = sChars.Minimum();
    // Should be 'z'
    char cMax = sChars.Maximum();
   
    // Should be 'B'
    char cSecondMin = sChars.Successor(cMin);
    // Should be 'y'
    char cSecondMax = sChars.Predecessor(cMax);
    
    db = 2;
}

int main(){
    testSet();
}
