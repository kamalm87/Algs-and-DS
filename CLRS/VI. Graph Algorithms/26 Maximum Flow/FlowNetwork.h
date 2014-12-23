#pragma once
#include "Auxiliary/DynamicArray.h"
#include "Auxiliary/Heap.h"
#include "Auxiliary/LinkedList.h"
#include "Auxiliary/Map.h"
#include "Auxiliary/Queue.h"
#include "Auxiliary/Set.h"
// For std::numerics<int>::max() to mark pseudo-infinite Distance value for untraversed Vertices
#include <limits>

template <typename T, typename W = int>
class Network;

enum VertexColor { vWHITE = 1, vGRAY = 2, vBLACK = 3 };

template <typename T, typename W = int>
struct Vertex{
  
  friend class Network<T>;

  // Default constructor only intended for creation of NIL vertex
  Vertex(){}

  Vertex( T data ): Data( data ), Predecessor( nullptr ), Distance ( infinity ){}
                   

  T Data;
  Vertex<T, W> *Predecessor;
  LinkedList< Vertex< T, W>* > Adj;

  static const W Infinity() { return infinity; }

  friend bool operator <(const Vertex<T, W> &l, const Vertex<T, W> &r){ return l.Distance < r.Distance; }
  friend bool operator >(const Vertex<T, W> &l, const Vertex<T, W> &r){ return l.Distance > r.Distance; }
  friend bool operator==(const Vertex<T, W> &l, const Vertex<T, W> &r){ return l.Data == r.Data; }
  friend bool operator!=(const Vertex<T, W> &l, const Vertex<T, W> &r){ return !( l == r ); } 
  
private:

  static const W nilInfinity = std::numeric_limits<W>::max();
  static const W infinity = std::numeric_limits<W>::max() - 1;

  W Discovered, Finished, Distance;
  VertexColor Color;
};

template <typename T, typename W>
struct Edge{
  

  Edge( Vertex<T, W> *u = nullptr, Vertex<T, W> *v = nullptr, W weight = W(), W capacity = W (), W flow = W() ) :
                         U(u), V(v), Weight( weight ), Capacity ( capacity), Flow ( flow ) {}

  friend bool operator==(const Edge<T, W> &l, Edge<T, W> &r){
    if (l.U == r.U && l.V == r.V )
      return true;
    else
      return false;
  }

  friend bool operator<(Edge<T, W> &l, Edge<T, W> &r){
    if(l.Weight < r.Weight)
      return true;
    else
      return false;
  }

  Vertex<T> *U, *V;
  W Weight, Flow, Capacity, Distance;
};


template <typename T, typename W>
struct VerticePair{
  VerticePair(Vertex<T, W> *u = nullptr, Vertex<T, W> *v = nullptr) : U(u), V(v) {}
  
  void AssignU(Vertex<T, W> *u){
    U = u;
  }

  void AssignV(Vertex<T> *v){
    V = v;
  }

  friend bool operator==(const VerticePair<T, W> &l, const VerticePair<T, W> &r){
    return l.U == r.U && l.V == r.V;
  }

  friend bool operator<(const VerticePair<T, W> &l, const VerticePair<T, W> &r){
    if( l.U->Data < r.U->Data )
      return true;  
    else if ( l.U->Data == r.U->Data && l.V->Data < r.V->Data )
      return true;
    else
      return false;
  }
private: 
  Vertex<T, W> *U, *V;  
};




template < typename T, typename W>
class Network{
public:


  Network() : vNil ( new Vertex< T, W>() ), eNIL ( new Edge< T, W >() ) {}

  bool AddVertex ( T u, bool map );
  bool AddEdge ( T u, T v, W c );
  bool AddEdge ( T u, T v, W c, W f);


  void FordFulkerson ( T s, T t );
  
  void EdmondsKarp ( T s, T t );

  Network<T,W> ResidualNetwork(){
    Network<T,W> g;
    Vertex<T,W> *b = V.Minimum(), *e = V.Maximum();
    std::cout << "Source: " << source << " Sink: " << sink << std::endl; 
    while ( b < e ){
      g.AddVertex(b->Data,true);
      b = V.Successor(b);
      if ( b == e)
        g.AddVertex(b->Data, true);
    }
    
    Edge<T,W> *eB = E.Minimum(), *eE = E.Maximum();
    Edge<T,W> *uv, *vu;

    while(eB<eE){
    
      if(eB->U->Data != sink)    
        g.AddEdge(eB->U->Data, eB->V->Data, eB->Capacity); 
      if(eB->V->Data != sink && eB->U->Data != source)    
        g.AddEdge(eB->V->Data, eB->U->Data, eB->Capacity); 
  
      eB = E.Successor(eB); 

      if( eB == eE ){
        if(eB->U->Data != sink)    
          g.AddEdge(eB->U->Data, eB->V->Data, eB->Capacity); 
        if(eB->V->Data != sink && eB->U->Data != source)    
          g.AddEdge(eB->V->Data, eB->U->Data, eB->Capacity); 
      }
    }
    std::cout<<"\n\nResidual network:\n";
    g.PrintEdges();
    std::cout<<"\n\n";
    return g;
  } 

  void PrintEdges(){
    Edge<T,W> *b = E.Minimum(), *e = E.Maximum();
    while ( b < e ){
      PrintEdge(b);
      b = E.Successor(b);
      if ( b == e)
        PrintEdge(b);
    } 
  }

  void PrintEdge(Edge<T,W> *e){
    std::cout << "(" << e->U->Data << ", " << e->V->Data << "): " << "F: " <<  e->Flow << " C: " << e->Capacity << std::endl;  
  }
private:
  const static W infinity = std::numeric_limits<W>::max() - 1;

  T source, sink;
  W Time;

  Vertex<T, W> *vNil;
  Edge<T, W> *eNIL;

  Set < Vertex< T, W >* > V;
  Set < Edge< T, W >* >   E;

  Mapping < T, size_t >                       indexMap;
  Mapping < T, Vertex<T, W> * >                   vMap;
  Mapping < VerticePair< T, W >, Edge< T, W >* >  eMap;

// Internal methods, which are not indepedently relevant to this section

  // TODO: Implement
  W FlowConstraint ( LinkedList< Edge< T, W> * > &l ){
  
    // TODO: CHANGE WHEN ACTUAL LOGIC IS IMPLEMENTED
    return W();
  }
  
  LinkedList< Edge<T, W>* > GetPath ( Network<T , W> & n){

    LinkedList< Edge<T, W>* > ll;
    if ( n.E.Count() == 0 ){
      return ll;
    }
    else{

    }

    // TODO: Remove after implemented
    return ll;

  }

  void BreadthFirstSearch ( Vertex<T, W> * S ){
    Vertex<T, W> *b = V.Minimum(), *e = V.Maximum();
    
    while ( b < e ){
      b->Color = vWHITE;
      b->Distance = infinity;
      b->Predecessor = vNil;
      b = V.Successor(b);
      // clean-up
      if( b == e ){
        b->Color = vWHITE;
        b->Distance = infinity;
        b->Predecessor = vNil;
      }
    }
    S->Color = vGRAY;
    S->Distance = W();
    S->Predecessor = vNil;

    Queue< Vertex< T, W >* > Q;
    Q.Enqueue( S );

    while ( !Q.Empty() ) {
      Vertex< T, W > *u = Q.Dequeue();
      auto vNode = u->Adj.Head;
      while ( vNode ){
        Vertex< T, W > *v = vNode->Data;
        if ( v->Color == vWHITE ) {
          v->Color = vGRAY;
          v->Distance = u->Distance + 1;
          v->Predecessor = u;
          Q.Enqueue( v );  
        }
        vNode = vNode->Next;
      }
      u->Color = vBLACK;
    }

    // Edge-cases?
    if ( e->Color == vWHITE ){

    }
  }
};


template < typename T, typename W>
bool Network< T, W >::AddVertex( T u, bool map ){
  
  if ( vMap.ContainsKey( u ) ){
    return false;
  }
  else{

    if( map ) indexMap[ u ] = indexMap.Count();
    Vertex< T, W> *U = new Vertex<T, W> (u);
    vMap[u] = U;
    V.Insert( U );
    return false;
  }
}

template < typename T, typename W>
bool Network< T, W >::AddEdge( T u, T v, W c ){

  if( vMap.ContainsKey ( u ) && vMap.ContainsKey( v ) ){
    Vertex< T, W> *U = vMap[u]; 
    Vertex< T, W> *V = vMap[v]; 
    Edge< T, W> *e = new Edge< T, W > ( U, V, 1, c, W() );
    VerticePair< T, W> vp;
    vp.AssignU( U );
    vp.AssignV( V );
    eMap[vp] = e;
    E.Insert( e );    
    return true;
  } 
  else{
    return false;
  }
}




template <typename T, typename W>
void Network< T, W>::FordFulkerson( T s, T t ){
  Vertex< T, W> *u, *v;    

  Edge<T, W> *b = E.Minimum(), *e  = E.Maximum();

  while( b < e){
    b->Flow = 0;
    b = E.Successor(b);
    if ( b == e)
      b->Flow = 0;
  }
  
}



/* 
  EDMONDS-KARP(G,s,t)
  1. for each each (u,v) in G.E  
  2.    (u,v).f = 0
  3.  while there exists a path from s to in the residual network G_f, perform a BFS   
  4.      c_f(p) = min{c_f(u,v) : (u,v) in p }
  5.      for each edge (u,v) in p
  6.          if (u,v) in E 
  7.              (u,v).f = (u,v).f + c_f(p)
  8.          else (v,u).f = (v,u).f - c_f(p)
  */
template <typename T, typename W>
void Network<T,W>::EdmondsKarp( T s, T t ){
    source = s, sink = t;
    Vertex<T,W> *u, *v;
    Edge<T,W> *eB = E.Minimum(), *eE = E.Maximum();
    while( eB < eE ){
      eB->Flow = 0;
      eB = E.Successor(eB);
      if ( eB == eE)
        eB->Flow = 0;
    }


    Network<T,W> Gf = ResidualNetwork();
}
