A set is an relatively ordered container supporting logarithm insertion,
lookup, and deletion. This implementation of the set data structure uses a
Red-Black Tree as the internal container to maintain a balanced binary tree to
represent the ordered data.

The implementation assumes that the comparison '<' and equality '==' operators
are defined for a properly functioning operations. 

Public operations:

- All of the below are assumed to take O(LOG(N)) time, where N is the number of
  elements currently in the set, provided that the internal binary tree is
  correctly balanced with a rough height of LOG(N).

INSERT(x): Adds an element to the set.

SEARCH(x): Returns whether the set contains a specified element.

DELETE(x): Returns whether the element was removed from the set, if it existed. 

PREDECESSOR(x): Gets the previous element (in an ascending ordered set).

SUCCESSOR(x): Gets the next element (in an ascending ordered set).

MINIMUM(X): Gets the smallest element in the set.

MAXIMUM(X): Gets the largest element in the set.

Files:
* RBT.h: Implementation of the Red-Black Tree data structure.
* Set.h: Implementation of the Set data structure.
* tSet.cpp: Tests the implementation of the Set data structure.
 
Compilation assumptions:
- Uses C++11 STD: 'auto'/'nullptr'
