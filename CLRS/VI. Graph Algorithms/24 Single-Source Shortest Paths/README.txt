* Built and tested with g++ in Linux 
  - to compile in Linux
    g++ -std=c++11 tGraph_SP.cpp -o test
* FILES:
  - Graph_SP.h: Implementation of a directed weighted graph.
    - Implements following algorithms: 
      (1) BellmanFord
      (2) Directed-Acyclic-Graph Shortest Paths
      (3) Dijkatra's
  - tGraph_SP.cpp: Tests the implementation of Graph_SP.h 
  - pseudocode_24.txt: Outlines algorithms, problems, and sections from this section.
* AUXILIARY:
  - DynamicArray.h: Represents an array capable of being dynamically resized. Used by Heap.h
  - Heap.h: Represents a min or max heap. Used in Dijkstra's represent to implement a Min-Priority queue
            - Graph_SP.h provides a template-specialized comparison functor for generic type T := Vertex<T>* 
  - LinkedList.h: Represents a linked list. Used for topological sort.
  - Map.h: Represents an associative array. Used within Graph.
  - RBT.h: Represents a Red-Black Tree, used for the implementations of Map and Set. 
  - Set.h: Represents an ordered set. Used within Graph.
