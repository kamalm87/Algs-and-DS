#include "Map.h"

// Tests the Mapping<Key,Value> implementation with:
// Key = char, Value = int
// - simply maps 'a' to 'z' with 97 to 123
// - tests removal with an associative key belonging to the collection
//   and one that does not
void testMap(){
    Mapping<char, int> m;
    
    bool hasABefore =  m.ContainsKey('a');
    
    for(int i = 97; i < 123; i++)
        m[static_cast<char>(i)] = i;
   
    bool hasANow = m.ContainsKey('a');
    bool hasZ = m.ContainsKey('z');

    bool hasUpperA = m.ContainsKey('A');
    
    bool has97 = m.ContainsValue(97);
    bool has122 = m.ContainsValue(122);
    bool has123 = m.ContainsValue(123);
    
    bool b1 = m.RemoveKey('a');
    bool b2 = m.RemoveKey('E');
    bool has97AfterDeleteOperation = m.ContainsKey('a');
    
    int DB = 1;
}

int main(){
    testMap();
}
