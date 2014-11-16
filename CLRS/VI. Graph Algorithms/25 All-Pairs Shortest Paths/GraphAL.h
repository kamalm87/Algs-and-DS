#pragma once
#include "Auxiliary/DynamicArray.h"
#include "Auxiliary/Heap.h"
#include "Auxiliary/LinkedList.h"
#include "Auxiliary/Map.h"
#include "Auxiliary/Matrix.h"
#include "Auxiliary/Set.h"

// For std::numerics<int>::max() to mark pseudo-infinite Distance value for untraversed Vertices
#include <limits>

// Forward declaration to give Graph access to certain Vertex private elements
template <typename T, typename W = int>
class Graph;

// Enums used for internally invoked Depth-First Searches
enum VertexColor{ vWHITE = 1, vGRAY, vBLACK };

template <typename T>
struct Vertex{
  
  // Provides Graph access to Vertex attributes related to Depth-First Search, which are
  // not explicitly used in any algorithms for Section 24. 
  friend class Graph<T>;

  // All explicit construction should use the parametized constructor. 
  // The default-constructor is intended to function as a boundary points for containers 
  // Assumption for the Distance variable:
  //  - all-traversed vertices <= untraversed vertices ( max - 1 ) < default-constructed vertice boundary points ( max ) 
  Vertex() : Data(T()), Predecessor( nullptr ), Distance( std::numeric_limits<int>::max() ){}  
  Vertex(T data) : Data(data), Predecessor( nullptr ), Distance( std::numeric_limits<int>::max() - 1 ), Color( vWHITE ) {}  

  T Data;
  LinkedList< Vertex<T>* > Adj;
  Vertex<T> *Predecessor;
  int Distance;

  // For operator overloading, 
  // - The comparison operators are based on the Distance variable, for use with the ordered
  //   contianers, Min-Heap, Set, and ( by extension of the compound type, VerticePair ) Mapping
  // - The equality operators are based on key access, and they assume that vertices have distinct
  //   Data values for the set of all vertices
  friend bool operator<(Vertex<T> &l, Vertex<T> &r){ return l.Distance < r.Distance; }
  friend bool operator>(const Vertex<T> &l, const Vertex<T> &r){ return l.Distance > r.Distance; }
  friend bool operator==(const Vertex<T> &l, const Vertex<T> &r){ return l.Data == r.Data; }
  friend bool operator!=(const Vertex<T> &l, const Vertex<T> &r){ return !( l == r ); } 
private:
   int Discovered, Finished; 
   VertexColor Color;
};

// Overloaded T_Less functor for use with Min-Heap based comparisons for Dijkstra's Algorithm,
// which takes a Min-Priority Queue of Vertices, which is implemented as a Min-Heap
template <typename T>
struct T_Less< Vertex<T>* >{
  bool operator() ( const Vertex<T> *l, const Vertex<T> *r) const {
     return l->Distance < r->Distance;
  }
};

// Represents an Edge in a weighted, directed graph. 
// - Where u := the starting vertex, v := the destination vertex
// - For all vertices u and v in a graph, it is assumed that can be at most
//   1 edge for each distinct u and v pair
// - Equality is defined by having same starting and destination vertices
// - Ordering is defined by Edge Weight
// ( Note: Currently, all values must explicitly be assigned. And only expected
//         to be constructed and assigned in the AddEdge method. )
template <typename T>
struct Edge{

  Edge(Vertex<T> *u = nullptr, Vertex<T> *v = nullptr, int weight = 0) : U(u), V(v), Weight(weight) {}

  friend bool operator==(const Edge<T> &l, Edge<T> &r){
    if (l.U == r.U && l.V == r.V )
      return true;
    else
      return false;
  }

  friend bool operator<(Edge<T> &l, Edge<T> &r){
    if(l.Weight < r.Weight)
      return true;
    else
      return false;
  }

  Vertex<T> *U, *V;
  int Weight;
};

// Used as a key for a pair of Vertices to query for a Graph's Edge, if one exists.
// - U := A starting vertex, V := A destination vertex
// - Equality is deined by having the same u and v
// - Comparisons are currently arbitrarily ordered by first the U value, then V value
//   - Example comparisons given T = int and (U,V): 
//     -- (1,9) <  (2,2) == true , ( 2,2 ) <  (9,1) == true
template <typename T>
struct VerticePair{
  VerticePair(Vertex<T> *u = nullptr, Vertex<T> *v = nullptr) : U(u), V(v) {}
  
  void AssignU(Vertex<T> *u){
    U = u;
  }

  void AssignV(Vertex<T> *v){
    V = v;
  }

  friend bool operator==(const VerticePair<T> &l, const VerticePair<T> &r){
    return l.U == r.U && l.V == r.V;
  }

  friend bool operator<(const VerticePair<T> &l, const VerticePair<T> &r){
    if( l.U->Data < r.U->Data )
      return true;  
    else if ( l.U->Data == r.U->Data && l.V->Data < r.V->Data )
      return true;
    else
      return false;
  }
private: 
  Vertex<T> *U, *V;  
};

// Represents a directed, weighted graph
// Implements the following algorithms:
// - BellmanFord
// - Directed-Acyclic-Graph Shortest Paths
// - Dijkstra's Algorithm
template <typename T, typename W >
class Graph{
public:
  
  Graph(): vNIL(new Vertex<T>()), eNIL(new Edge<T>()){} 

  bool AddVertex(T u, bool map);
  bool AddEdge(T u, T v, int weight);
  void PrintVerticesInfo();
  void PrintEdgesInfo();
  
  void InitializeSingleSource(Vertex<T> *s);
  void Relax( Edge<T> *e);
  bool BellmanFord( T s );
  void DAG_Shortest_Paths(T s);
  void Dijkstra(T s);
  void Dijkstra(T s, T x);
  Matrix<W> Johnson( T s );

  static W Infinity(){
    return infinity;
  }

  Mapping < T , size_t > indexMap;


private:

  // ::max() is "reserved" for NIL, so ::max() -1 represents infinity
  const static W infinity = std::numeric_limits<W>::max() - 1;
  // Used internally for the internally invoked Depth-First Search
  int Time;

  // Represent NIL values for Vertices/Edges 
  Vertex<T> *vNIL;
  Edge<T> *eNIL;

  // Set of all Vertices/Edges  
  Set< Vertex<T>* > V;
  Set< Edge<T>* > E;

  // Mappings for Vertices/Edges
  Mapping < T, Vertex<T>* > vMap;
  Mapping < VerticePair<T>, Edge<T>* >  eMap;
  // The following two functions are intended for testing/debugging the graph
  // Assumption: the type T is overloaded to support ostream<<
  //            - If not, need to specialize the template for the given type
  void PrintVertexInfo( Vertex<T> *v ){
    std::cout << "\tV: " << v->Data << " D: " << v->Distance << std::endl;
    // Uncomment if you wish to display the information of each Adjacent Edge
    /*
    VerticePair<T> vp;
    auto vNode = v->Adj.Head;
    
    vp.AssignU(v);
    while (vNode){
      vp.AssignV(vNode->Data);
      std::cout << "\t";
      PrintEdgeInfo( eMap[vp] );
      vNode = vNode->Next;
    }
    */
  }
  void PrintEdgeInfo( Edge<T> *e ){
    std::cout << "\tE: (" << e->U->Data << "," << e->V->Data << ") W: " << e-> Weight << std::endl;
  }

  // Returns a LinkedList containing the Graph's Vertices' Data in topologically sorted order
  LinkedList<T> DepthFirstSearch(){
    LinkedList<T> list;
    
    Vertex<T> *b = V.Minimum(), *e = V.Maximum();
    while( b < e ){
      b->Color = vWHITE;
      b->Predecessor = vNIL;
      b = V.Successor(b);
    }
    
    Time = 0;
    b = V.Minimum();
    while ( b < e ){
      std::cout << b->Data << ", ";
      if( b->Color == vWHITE ){
        Visit(b, list);        
      }
      b = V.Successor(b);
    }
    return list;
  }

  // Recursive subroutine for Depth-First Search 
  void Visit(Vertex<T> *u, LinkedList<T> &list){
    Time++;
    u->Discovered = Time; 
    u->Color = vGRAY;
    
    // TODO: clean this up sometime. 
    // - Substitue for LinkedList<T>::Node<T>, which is internally defined within LinkedList 
    auto vNode = u->Adj.Head;
    while(vNode){
      Vertex<T> *v = vNode->Data; 
      if(v->Color == vWHITE){
        v->Predecessor = u;
        Visit(v, list);
      }
      vNode = vNode->Next;
    }

    u->Color = vBLACK;
    Time++;
    u->Finished = Time;
    list.AddToHead(u->Data);
  }
};

// Creates a Vertex and adds it to the set of vertices, if the vertex does not exist
// Returns whether the vertex was created 
template <typename T, typename W>
bool Graph<T, W>::AddVertex( T u, bool map ) {
  if(vMap.ContainsKey(u)){
    return false;
  }
  else{
    Vertex<T>* vertex = new Vertex<T>(u);
    vMap[u] = vertex;
    V.Insert(vertex);
    if( map){
      indexMap[ u ] = indexMap.Count();
    }

    return true;
  }  
}

// Creates a weighted given two vertex keys and a weight, given that vertices exist for 
// both keys
// U := starting vertex, V:= destination vertex
// Returns whether an edge was created
template <typename T, typename W>
bool Graph<T, W>::AddEdge( T u, T v, int weight) {
  
  if(vMap.ContainsKey(u) && vMap.ContainsKey(v)){
      Vertex<T> *U = vMap[u];
      Vertex<T> *V = vMap[v];
      Edge<T> *e = new Edge<T>(U, V, weight);
      U->Adj.AddToTail(V);
      VerticePair<T> vp;
      vp.AssignU(U);
      vp.AssignV(V);
      eMap[vp] = e;
      E.Insert(e);
      return true;
  }
  else{
    return false;
  }
}

// Initializes the distance for a given starting vertex
// Note: Untraversed vertices by default are assigned the max values
//       in the parametized vertex constructor
template <typename T, typename W>
void Graph<T, W>::InitializeSingleSource( Vertex<T> *s){
  s->Distance = 0;
}

// Checks and updates the distance of a vertex, if applicable
template <typename T, typename W>
void Graph<T, W>::Relax( Edge<T> *e ){
  
  Vertex<T> *u = e->U, *v = e->V;
  if(v->Distance > u->Distance + e->Weight ){
    v->Distance = u->Distance + e->Weight;
    v->Predecessor = u;
  }
}

// Implementation of the Bellman-Ford algorithm
template <typename T, typename W>
bool Graph<T, W>::BellmanFord( T s){ 
  Vertex<T> *vS = vMap[s];
  InitializeSingleSource(vS);
  Edge<T> *b = E.Minimum(), *e = E.Maximum();
  
  for(int i = 0; i < V.Count(); i++){
    b = E.Minimum(), e = E.Maximum();
    while( b < e){
      Relax(b);
      b = E.Successor(b);
      if(b == e){
        Relax(b);
      }
    }
  }
  b = E.Minimum(), e = E.Maximum();
  while( b < e){
    if(b->V->Distance > b->U->Distance + b->Weight)
      return false;
    b = E.Successor(b);
    if(b == e){
      if( b->V->Distance > b->U->Distance + b->Weight)
        return false;
    }
  }
  return true;
}

// Implementation of the Directed-Acyclic-Graph algorithm
template <typename T, typename W>
void Graph<T, W>::DAG_Shortest_Paths( T s ){

  InitializeSingleSource( vMap[s] );
  // ts := topologically sorted list of vertex data  
  LinkedList<T> ts = DepthFirstSearch();
  // u/vNode := LinkedList<T>::Node<T> ( Internally defined and declared within LinkedList<T> )
  auto uNode =  ts.Head;
  VerticePair<T> vp;
  while(uNode){
    
    Vertex<T> *u = vMap[uNode->Data];
    vp.AssignU(u);
    
    auto vNode = u->Adj.Head;
    while(vNode){
      
      Vertex<T> *v = vNode->Data;
      vp.AssignV(v);
      if(eMap.ContainsKey(vp)){
        Relax(eMap[vp]);
      }

      vNode = vNode->Next;
    }
    uNode = uNode->Next;
  }  
}

// Implementation of Dijkatra's algorithm
template <typename T, typename W>
void Graph<T, W>::Dijkstra( T s ){
  
  InitializeSingleSource(vMap[s]);
  Set< Vertex<T>* > S;

  // Q := Min-Heap priority queue of Vertices
  Heap< Vertex<T>* > Q(this->V);
  VerticePair<T> vp;
  
  while( !Q.Empty() ){
    Vertex<T> *u = Q.Extract();
    S.Insert(u);
    vp.AssignU(u);
    // vNode := LinkedList<T>::Node<T> ( Internally defined and declared within LinkedList<T> )
    auto vNode = u->Adj.Head;
    while(vNode){
      Vertex<T> *v = vNode->Data;
      vp.AssignV(v);
      Relax(eMap[vp]);
      vNode = vNode->Next;
    }
    // Updates the Min-Heap based any Relaxation updates 
    Q.Build();
  }
}

// Specialized version of Dijkstra's algorithm, 
// allowing the user to select a Vertex to ignore
// so as to select V - {x} vertices to traverse
// as in Johnson's Algorithm, where x is the 
// data representing the vertex to ignore 
template <typename T, typename W>
void Graph<T, W>::Dijkstra( T s, T x ){
  
  InitializeSingleSource(vMap[s]);
  Set< Vertex<T>* > S;

  // Q := Min-Heap priority queue of Vertices
  Heap< Vertex<T>* > Q(this->V);
  VerticePair<T> vp;
  
  while( !Q.Empty() ){
    Vertex<T> *u = Q.Extract();

    // Only process vertices that aren't the excluded vertex,
    //  otherwise continue extracting Min from the Queue
    if ( u->Data != x ){
    S.Insert(u);
    vp.AssignU(u);
    // vNode := LinkedList<T>::Node<T> ( Internally defined and declared within LinkedList<T> )
    auto vNode = u->Adj.Head;
    while(vNode){
      Vertex<T> *v = vNode->Data;
      vp.AssignV(v);
      Relax(eMap[vp]);
      vNode = vNode->Next;
    }
    // Updates the Min-Heap based any Relaxation updates 
    Q.Build();
    }
  }
}
template <typename T, typename W>
void Graph<T, W>::PrintVerticesInfo(){
  std::cout << "Vertices:" << std::endl;
  Vertex<T> *b = V.Minimum(), *e = V.Maximum();
  while( b < e ){

    PrintVertexInfo(b);
    b = V.Successor(b);
    if(b == e){
      PrintVertexInfo(b);
    }
  }
}

template <typename T, typename W>
void Graph<T, W>::PrintEdgesInfo(){
  std::cout << "Edges:" << std::endl;
  Edge<T> *b = E.Minimum(), *e = E.Maximum();
  while ( b < e ){
    PrintEdgeInfo(b);
    b = E.Successor(b);
    if( b == e){
      PrintEdgeInfo(b);
    }
  }
}

// Implementation of the Johnson Algorithm
// Returns an empty Matrix if the Graph contains negative weight cycles
// Otherwise, returns a Matrix containing the shortest path to each vertex
template <typename T, typename W>
Matrix<W> Graph<T, W>::Johnson( T s ){
  
  Graph<T, W> G = *this;
  Graph<T, W> primeG = *this;
  primeG.AddVertex( s, false );

  bool noNegativeCycle = primeG.BellmanFord( primeG.V.Minimum()->Data );

  Vertex<T> *b = primeG.V.Minimum(), *e = primeG.V.Maximum();
  while ( b < e ){
    if ( b->Data != s ){
      primeG.AddEdge ( s, b->Data, W() ); 
      if ( b == e ){
       primeG.AddEdge ( s, b->Data, W() );
       primeG.BellmanFord( b->Data );
      }
    }
    primeG.BellmanFord( b->Data );
    b = primeG.V.Successor(b);
  }

  Matrix<W> D;
 
  if( !noNegativeCycle ){
   return D;   
  }
  else
  {
    // To ' - 1' offset for 's', which won't be processed
    size_t n = primeG.V.Count() - 1;
    D = Matrix<W>( n, n, D.Infinity() ); 

    Vertex<T> *vS = primeG.vMap[s];
    vS->Distance = W();

    VerticePair<T> vp;
    vp.AssignU(vS);
    auto vNode = vS->Adj.Head;

    while ( vNode ){
      vp.AssignV(vNode->Data);
      auto edge = primeG.eMap[vp];
      edge->Weight = 0 - vNode->Data->Distance;
      vNode = vNode->Next;
    }

    Edge<T> *eb = G.E.Minimum(), *ee = G.E.Maximum();
    while ( eb < ee ){
      // Calculation already done for 's'
      if ( eb->U->Data != s ){
        // w-hat( u,v ) = w( u, v) + h(u) - h(v)
        // where h(u) := distance of vertex u
        eb->Weight = eb->Weight - eb->V->Distance + eb->U->Distance;
      }
     
      eb = primeG.E.Successor( eb );
      if ( eb == ee ){
        if ( eb->U->Data != s ){ 
          eb->Weight = eb->Weight - eb->V->Distance + eb->U->Distance;
        }
      }
    }
    
    b = primeG.V.Minimum(), e = primeG.V.Maximum();
    Vertex<T> *prev = b; 

    // Performs Dijkstra's Algoirthm on each vertex using the adjusted weights
    while ( b < e ){
      // Note: existing implementation of Dijkstra's Algorithm does 
      //       not set distnace to infinity for v in V - {s}
      Vertex<T> *innerB = primeG.V.Minimum(), *innerE = primeG.V.Maximum();
      // Reset the vertices distance to the un-traversed amount, the representative value
      // for infinity 
      while( innerB < innerE ){
        innerB->Distance = primeG.Infinity();
        innerB = primeG.V.Successor( innerB );
        if ( innerB == innerE )
          innerB->Distance = primeG.Infinity();
      }

      primeG.Dijkstra( b->Data, s);
      b = primeG.V.Successor ( b );
      
      // Update Matrix based on the previous  
      if ( indexMap.ContainsKey(prev->Data)){
        // account for 0-based indexing
        size_t i = indexMap[prev->Data] - 1, j;
        innerB = primeG.V.Minimum(), innerE = primeG.V.Maximum();
        while ( innerB < innerE ){
          if ( indexMap.ContainsKey( innerB->Data) ){
              j =   indexMap[innerB->Data] - 1;
              D[i][j] = innerB->Distance;
          }
          innerB = primeG.V.Successor( innerB );
          if ( innerB == innerE ){
            if ( indexMap.ContainsKey( innerB->Data) ){
              j =   indexMap[innerB->Data] - 1;
              D[i][j] = innerB->Distance;
            }
          }
        }
      }

      // Check the final element of the set V, and process into
      // the matrix if it's a mapped vertex 
      if ( b == e ){
        primeG.Dijkstra( b->Data, s);
        if ( indexMap.ContainsKey(b->Data) ){
          // account for 0-based indexing
          size_t i = indexMap[prev->Data] - 1, j;
          innerB = primeG.V.Minimum(), innerE = primeG.V.Maximum();
          while ( innerB < innerE ){
            if ( indexMap.ContainsKey( innerB->Data) ){
                j =   indexMap[innerB->Data] - 1;
                D[i][j] = innerB->Distance;
            }
            innerB = primeG.V.Successor( innerB );
            if ( innerB == innerE ){
              if ( indexMap.ContainsKey( innerB->Data) ){
                j =   indexMap[innerB->Data] - 1;
                D[i][j] = innerB->Distance;
              }
            }
          }
        }
      }
      prev = b;
    }
    return D;
  } 
}
