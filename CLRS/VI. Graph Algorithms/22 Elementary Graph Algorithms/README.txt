FILES:
- Graph.h: Implementation of the Graph data structure and the elementary graph algorithms detailed in pseudocode_22.txt 
- tGRaph.cpp:  Tests the implementation of the elementary graph algorithms.
- pseudocode_22.txt: Details the 

AUXILIARY ( These were created in other sections. Brief description of their purpose for this section. )
- Contains the component data structures used for the graph data structure and the associated elementary algoritms:
- DynamicArray.h: Internal component of Stack and Queue.
- LinkedList.h: To represent adjacency lists and the return type for the strongly connected component implementation.
- Map.h: To map vertex data to internal vertices in the graph implementation.
- Queue.h: For the Breadth-First Search algorithm.
- RBT.h: Internal component of Set and Map.
- Set.h:  Internal component of Map. Used within Graph to store Edges and Vertices.   
- Stack.h: Used to store Last-In First-Out data for a modified version of Depth-First Search for use with the Strongly Connected Component algorithm.

TESTING:
- compiled using the most recent version of the G++ compiler (as of 11/02/2014)
- used: g++ -g -std=++11 tGraph.h -o test
  (On this working directory)
