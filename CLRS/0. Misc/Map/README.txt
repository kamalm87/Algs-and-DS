A mapping represents a collection with associative keys that are relatively
ordered based on key values. This implementation of the associative mapping
(to be coarsely comparable to 'maps' or 'dicts/dictionaries') uses a Set with
an an internal class used to represent key to value pairs. The internal Set is
structured with a Red-Black Tree data structure to maintain a relatively
balanced binary tree with a height ~ LOG(N), where N = the number of elements
in the container.

Generic type assumptions: 
- Key: Operators defined: comparison '<', equality '=='
- Value: Operators defined: equality '=='

Public operations:
- Assuming that the generic types' operators are properly defined and that the
  interal set's internal Red-Black Tree is balanced!
- Logarithm operations: INSERT, CONTAINS-KEY, DELETE, FIND
- Linear operations: CONTAINS-VALUE
- (*) If the set's tree is not balanced with height = O(LOG(N)), then all operations are assumed to be
  linear

// Where k = Key, v = Value
INSERT(k, v): Either inserts a KeyValuePair<Key, Value> into the internal set, or
              updates the Value of the KeyValuePair

DELETE(k): Deletes a KeyValuePair<Key, Value> with the associative Key k from
           the collection, if exists.

CONTAINS-KEY(k): Returns whether any KeyValuePairs contain the key k.

CONTAINS-VALUE(v): Returns whether any KeyValuePairs contain the value v.

( Note: the operator[] encaspulates the INSERT operattion, with the index being
        the key and the rvalue being the value )

Files:
* RBT.h: Implementation of Red-Black Tree data structure.
* Set.h: Implementation of the Set data structure.
* Map.h: Implementation of the Map data structure.
* tMap.cpp: Tests the implementation of the Map data structure.

Compilation assumptions:
- Uses C++11 STD: 'auto'/'nullptr'
