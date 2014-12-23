#include "Auxiliary/Map.h"
#include "Auxiliary/LinkedList.h"
#include "Auxiliary/Stack.h"
#include "Auxiliary/Queue.h"

#include <limits>

// Implementation of a Graph data structure supporting generic parameters
// Supports: 
//          * Types of graphs:
//                           - Directed
//                           - Undirected
//                           - Weighted (Note: no weighted algorithms,
//                                             currently )
//          * Algorithms: 
//                       - Breadth Firsth Search 
//                       - Depth First Search
//                       - Topological Sort
// Notes:
//       * Vertex and Edge structs are encapulsated, requiring use of the auto
//         keyword for functions returning those types.
//       * Vertex   
// (Assumption: the generic type T supports the << operator for ostream for
//              printing output to the console.) 
template <typename T>
class Graph{
private:
    enum VColor{ WHITE, GRAY, BLACK };

    template <typename U>
    struct Vertex{
        Vertex(){}
        Vertex(U d): Data(d){}
        U Data;
        LinkedList<Vertex<U>*> Adj;
        Vertex<T> *Parent;

        // For Breadth-First Search
        int Distance;
        VColor c; 

        // For Depth-First Search
        int Discovered, Finished; 
   };

    template <typename U>
    struct Edge{
       Edge(Vertex<U> *From = nullptr, Vertex<T> *To = nullptr, int w = 0) : From(From), To(To), Weight(w){} 
       Vertex<U> *From, *To;
       int Weight;
    };    

    Set< Vertex<T>* > V;
    Set< Edge<T>* > E;
    bool Weighted = false;
    Vertex<T> *NIL;
    LinkedList<T> *topologicalSorting = nullptr;
    // For DepthFirstSearch
    int Time;    
   
    Mapping<T, Vertex<T>* > vMap;

    // Subroutine for StronglyConnectedComponents
    // - Performs a DepthFirstSearch on the invoking graph
    // - Returned stack contains vertex data in decreasing finish time order
    //   (i.e. top of stack contains last finished vertex from the DFS)
    Stack<T> DFS_Stack(){
      Stack<T> s;
		  Vertex<T> *b = V.Minimum(), *e = V.Maximum();
  		while (b < e){
  			b->c = WHITE;
  			b->Parent = NIL;
  			b = V.Successor(b);
  		}
  		e->c = WHITE;
  		e->Parent = NIL;

  		Time = 0;
  		b = V.Minimum();
  		while (b < e){
  			if (b->c == WHITE){
  				DFS_Stack_Visit(b, s);
  			}
  			b = V.Successor(b);
  		}
  		return s;
    }
    // Recursive DFS routine for DFS_Stack
    void DFS_Stack_Visit(Vertex<T> *u, Stack<T> &s){
  		Time++;
	  	u->Discovered = this->Time;
  		u->c = GRAY;
  		auto vNode = u->Adj.Head;

  		while (vNode){

  			auto v = vNode->Data;
  			if (v->c == WHITE){
  				v->Parent = u;
  				DFS_Stack_Visit(v, s);
  			}
  			vNode = vNode->Next;
  		}

  		u->c = BLACK;
  		Time++;
  		u->Finished = Time;
  		s.Push(u->Data);
   }
    
   // Where s is a stack containing the vertex keys ordered by decreasing finished time
   // (Returned from DFS_Stack) 
   LinkedList< LinkedList<T> > SCC_DFS(Stack<T> &s){
      LinkedList< LinkedList<T> > res;
      Vertex<T> *b = V.Minimum(), *e = V.Maximum();
  		while (b < e){
  			b->c = WHITE;
  			b->Parent = NIL;
  			b = V.Successor(b);
  		}
  		e->c = WHITE;
  		e->Parent = NIL;
				
  		Time = 0;
  		b = V.Minimum();
  		while (!s.Empty()){
  			T data = s.Pop();
  			Vertex<T> *u = vMap[data];
  			LinkedList<T> ll;
  			if (u->c == WHITE){
  				Graph<T> g;
  				SCC_DFS_Visit(u, s, ll);
  				res.AddToHead(ll);
  			}
  		}
  		return res;
   }
  // Recursive DFS subroutine for SCC_DFS
	void SCC_DFS_Visit(Vertex<T> *u, Stack<T> & s, LinkedList<T> & ll){
		Time++;
		u->Discovered = this->Time;
		u->c = GRAY;
		auto vNode = u->Adj.Head;

		while (vNode){
			auto v = vNode->Data;
			if (v->c == WHITE){
				v->Parent = u;
				SCC_DFS_Visit(v, s, ll);
			}
			vNode = vNode->Next;
		}
		u->c = BLACK;
		Time++;
		u->Finished = Time;
		ll.AddToTail(u->Data);
	}
  // Creates a transposed graph, assuming that the invoking Graph contains directed edges 
  Graph<T> Transpose(){
   	Graph<T> gT;

		auto b = V.Minimum(), e = V.Maximum();
		while (b < e){
			gT.AddVertex(b->Data);			
			b = V.Successor(b);
		}
		gT.AddVertex(e->Data);
		b = V.Minimum();
		while (b < e){
			auto vNode = b->Adj.Head;

			while (vNode){
				gT.AddEdge(vNode->Data->Data, b->Data);
				vNode = vNode->Next;
			}
			b = V.Successor(b);
		}
		return gT;
  }


public:

    // Creates a list of strongly connected components
    // Outer list: List of each strongly connected component
    // Inner list: List of vertex data contained within a specific strongly connected component
    // Implementation notes: 
    // -1 Creates last-in, first-out (relative to DFS finish time ) stack of vertex data with a modified 
    //    version of Depth-First Search (which alters the invoking Graph)
    // -2 Creates a temporary transposed graph
    // -3 Performs a Depth-First Search on the transpose taking the stack from (1) as a parameter
    //    to determine vertex visitation order. 
    LinkedList<LinkedList<T>> StronglyConnectedComponentList(){
      Stack<T> dfsFinishOrder = DFS_Stack();
      auto gT = Transpose();
      return gT.SCC_DFS(dfsFinishOrder); 
    }

    // Prints each strongly connected component
    // Assumption: generic data type T has supports the '<<' operator on ostreams for console printing
    void PrintStronglyConnectedComponents(){
      LinkedList<LinkedList<T>> ll = StronglyConnectedComponentList();
      PrintStronglyConnectedComponents_Inner(ll);
    }

    // Prints each strongly connected component
    // Assumption: generic data type T has supports the '<<' operator on ostreams for console printing
    void PrintStronglyConnectedComponents_Inner(LinkedList<LinkedList<T>> &ll){
      auto n = ll.Head;
   		int componentNumber = 0;

	  	while (n){
		  	auto inner = (n->Data).Head;
			  if (inner)
  				std::cout << "SCC #" << ++componentNumber << ": ";
  			while (inner){
  				std::cout << inner->Data << ", ";
  				inner = inner->Next;
  			}
  			std::cout << std::endl;
  			n = n->Next;
  		}
    }


   // Prints a vertex's color
   // USE: For debugging to ensure that an algorithm visits/alters every
   // expected vertex
   std::string GetColor(Vertex<T>* v){
        if(v->c == WHITE)
            return "WHITE";
        else if (v->c == GRAY)
            return "GRAY";
        else
            return "BLACK";
    }
   
    // Creates and returns a topologically sorted linked list
    // , using an augmentation version of Depth-First Search,
    // which appends vertex's data to the linked list's head 
    // upon completion (assignment of the vertex's finished variable)
    LinkedList<T> TopologicalSort(){
        topologicalSorting = new LinkedList<T>();
        DepthFirstSearch(topologicalSorting);
    }
    
    void printTopologicalSortedResults(){

        // lazy instantiation of the sorting, if necessary
        if(!topologicalSorting )
            TopologicalSort();
        auto n = topologicalSorting->Head; 
        if(n){
            std::cout << std::endl;
            std::cout << "Toplogical sorting results:" << std::endl;
        }
        else{
            return; // Nothing topologically sorted
        }
        while(n){
            if( n != topologicalSorting->Tail)
                std::cout << n->Data << "->";
            else
                std::cout << n->Data;
            
            n = n->Next;
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }
    
    // Default constructor simply creates a dummy NIL pointer vertex 
    // Other variables are intialized/assigned within methods using them 
    Graph(){    
        NIL = new Vertex<T>();
    }
   
    // Wrapper for the BFS algorithm
    // Selects an arbitrary Node to begin as the start point, which is expected
    // to be one of the first vertices inserted into the graph, based on the
    // set ordering, which is expected to be based on comparisons on pointers
    void BreadthFirstSearch(){
        BreadthFirstSearch(V.Minimum());
    }

    // Implementation of the BFS algorithm
    void BreadthFirstSearch(Vertex<T> * S){
        
        // Use as placeholder to represent an infinite value for untraversed vertices
        int INFINITY = std::numeric_limits<int>::max();

        auto b = V.Minimum(), e = V.Maximum();

        while(b < e){
            b->c = WHITE;
            b->Distance = INFINITY; 
            b->Parent = NIL;
            b = V.Successor(b);

            if(b == e){
              e->c = WHITE;
              e->Parent = NIL;
              e->Distance = INFINITY; 
            }
       }
    
       S->c = GRAY;
       S->Distance = 0;
       S->Parent = NIL; 

       Queue<Vertex<T>* > Q;
       Q.Enqueue(S); 

       while(!Q.Empty()){
            Vertex<T> *u = Q.Dequeue();
            auto vNode = u->Adj.Head;
            while(vNode){
                auto v = vNode->Data;
                std::cout << v->Data << ", ";  
                if(v->c == WHITE){
                    v->c = GRAY;
                    v->Distance = u->Distance + 1;
                    v->Parent = u;
                    Q.Enqueue(v);
                }
                vNode = vNode->Next;
            } 
       }

       // TODO: Add possible edge case?
       // Implementation wart note, unrelated to algorithm:
       // * Since the implementation of set uses the min and the max as
       // * boundaries and the equality operator is not well-defined for
       // * Vertex<T>*, which happen to be the set's generic type, a quick check
       // * of the end, max boundary is performed to ensure that all vertices are
       // * processed
       if(e->c == WHITE) 
       {
            // logic would go here, if necessary
       }
    }

    // Implementation note for the following DFS algorithm functions: 
    // Time refers to private int Time declared within class, allowing it to
    // act as a pseudo global variable scoped to the invoking Graph<T> object
    void DepthFirstSearch(){
         
        Vertex<T> *b = V.Minimum();
        Vertex<T> *e = V.Maximum();
        while( b < e){
            b->c = WHITE;
            b->Parent = NIL;
            b = V.Successor(b);
        }
        
        Time = 0;
        b = V.Minimum();
        while(b < e){
            if(b->c == WHITE){
                 DFS_Visit(b);
            }
            b = V.Successor(b);
        }
        
        // Checks the "end" boundary element to avoid having to define the
        // equality operator
        if(e->c == WHITE)
            DFS_Visit(b);

    }

    void DFS_Visit(Vertex<T> *u){
        Time++;
        u->Discovered = this->Time;
        u->c = GRAY;
    
        auto vNode = u->Adj.Head;

        while(vNode){
        
            auto v = vNode->Data;
            if(v->c == WHITE){
                v->Parent = u;
                DFS_Visit(v);
            }
            vNode = vNode->Next;
        }

        u->c = BLACK;
        Time++;
        u->Finished = Time;
    }

    // These two functions are modified to aid in the creation
    // of a topologically sorted list
    // The algorithms operate identically to the standard 
    // DFS algorithm, with the addition of inserting a node's
    // data into the referenced linked list's head after it's finished
    // processing at the end of the DFS-Visit subroutine 
    void DepthFirstSearch(LinkedList<T> * ll){
         
        Vertex<T> *b = V.Minimum();
        Vertex<T> *e = V.Maximum();
        while( b < e){
            b->c = WHITE;
            b->Parent = NIL;
            b = V.Successor(b);
        }
        
        Time = 0;
        b = V.Minimum();
        while(b < e){
            if(b->c == WHITE){
                 DFS_Visit(b, ll);
            }
            b = V.Successor(b);
        }
        // Checks the "end" boundary element to avoid having to define the
        // equality operator
        if(e->c == WHITE)
            DFS_Visit(b, ll);
    }

    void DFS_Visit(Vertex<T> *u, LinkedList<T> *ll){
        Time++;
        u->Discovered = this->Time;
        u->c = GRAY;
    
        auto vNode = u->Adj.Head;

        while(vNode){
        
            auto v = vNode->Data;
            if(v->c == WHITE){
                v->Parent = u;
                DFS_Visit(v, ll);
            }
            vNode = vNode->Next;
        }

        u->c = BLACK;
        Time++;
        u->Finished = Time;
        // Topological Sort infusion: after a given vertex's recursive stack
        // finishes, the node is added into the list's head 
        ll->AddToHead(u->Data);
    }

    void printVertices(){
      auto b = V.Minimum(), e = V.Maximum();

      while(b<e){
        printVertexInfo(b->Data);
        b = V.Successor(b);
      }
      printVertexInfo(e->Data);
    }

    // TODO: Remove whenever, just for crude debugging
    // USE: To print the data for all the to vertices relating to the Vertex
    // associated with the data, if it exists.
    // (Assumption: generic type 'T' supports the << operator for ostream, for
    //              console output)
    void printVertexInfo(T d){
        bool f = true;
        Vertex<T> *v = vMap[d];
        if(v){
            std::cout << "Vertex: ";
            std::cout << v->Data;
            auto c = v->Adj.Head;
            while(c){
                if(f){
                  std::cout<< "Adj: ";
                  f = false; 
                }
                std::cout << c->Data->Data << "->";
                c = c->Next;
            }
            f = true;
            std::cout << std::endl;
        }
        else{
            std::cout << "No vertex associated with " << d << std::endl;
        }
    }

    // TODO: Add a check for overwriting cases
    bool AddVertex(T d){
        Vertex<T> *t = new Vertex<T>(d);
        V.Insert(t);
        vMap[d] = t;
    }

    // Edge adding functions:
    // - Note: An undirected edge requires use of the explicitly named function
    
    // Adds a directed edge to the graph, provided that the 'to' and 'from'
    // vertices exist within the Graph upon this method's invocation 
    bool AddEdge(T from, T to, int weight = 0 ){
        auto fromVertex  = vMap[from];
        auto toVertex = vMap[to];
        
        if(fromVertex && toVertex){
            auto e = new Edge<T>(fromVertex, toVertex, weight);
            E.Insert(e);
            fromVertex->Adj.AddToHead(toVertex);
            return true;
       } else {
            return false;
       }
   }

   // Adds a directed edge to the graph, provided that both vertices exist
   // within the Graph upon this method's invocation 
   bool AddUndirectedEdge(T v1, T v2, int weight = 0){
        auto vertexOne = vMap[v1];
        auto vertexTwo = vMap[v2];
        
        if(vertexOne && vertexTwo){
            auto e = new Edge<T>(vertexOne, vertexTwo, weight);
            E.Insert(e);
            vertexOne->Adj.AddToHead(vertexTwo);
            vertexTwo->Adj.AddToHead(vertexOne);
            return true;    
        }
        else{
            return false;
        }
  }

  // Prints out the vertices values relative to a Breadth-First Search
  // Note: Assumes the type operator, T, supports the '<<' operator for console
  //       output
  void printDepthFirstSearchResults(){
        auto b = V.Minimum();
        auto e = V.Maximum();
 
        std::cout << std::endl;
        std::cout << "Depth-First Search vertex data:" << std::endl;
  
        while(b < e){
            std::cout << b->Data << " D: " << b->Discovered << " F: " << b->Finished << " C: " <<  GetColor(b) << std::endl;
            b = V.Successor(b);
        }
        std::cout << e->Data << " D: " << e->Discovered << " F: " << e->Finished << " C: " <<  GetColor(e) << std::endl;
        std::cout << std::endl << std::endl;
}  

  // Prints out the vertices values relative to a Depth-First Search
  // Note: Assumes the type operator, T, supports the '<<' operator for console
  //       output
  void printBreadthFirstSearchResults(){
        auto b = V.Minimum();
        auto e = V.Maximum();
        
        std::cout << std::endl;
        std::cout << "Breadth-First Search vertex data:" << std::endl;

        while(b < e){
            std::cout << b->Data << " D: " << b->Distance << " C: " <<  GetColor(b) << std::endl;
            b = V.Successor(b);
        }
        std::cout << e->Data << " D: " << e->Distance << " C: " <<  GetColor(e) << std::endl;
        std::cout << std::endl << std::endl;
  }  
};
