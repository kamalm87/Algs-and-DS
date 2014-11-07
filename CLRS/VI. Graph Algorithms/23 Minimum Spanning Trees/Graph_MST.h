#include "Auxiliary/DisjointSet.h"
#include "Auxiliary/DynamicArray.h"
#include "Auxiliary/Heap.h"
#include "Auxiliary/LinkedList.h"
#include "Auxiliary/Map.h"
#include "Auxiliary/Queue.h"
#include "Auxiliary/RBT.h"
#include "Auxiliary/Set.h"

// For std::numerics<int>::max() to get an extensible dummy value for a min-priority queue
#include <limits> 


// Prim algorithm vertex-specific implementation notes:
// - for dummy key values, std::numeric<int>::max() is used for boundary dummy nodes
//   , while uninitialized nodes with values will be set to 'std::numeric<int>::max() - 1'
// - DeQueued is set to false by default, and will be altered to true in Prim's algorithm for O(1) 
//   Queue search time
// - IMPORTANT: To ensure that default initialized vertices operate as NIL values, 
//              std::numeric<int>::max() will be used for the default constructor,
//              while std::numeric<int>::max() - 1 will be used within Prim's algorithm.
template <typename T>
struct Vertex{
	T Data;
	LinkedList<Vertex<T>*> Adj;

	// For prim's algorithm
	int Key;
	bool DeQueued;
	Vertex<T> *Parent;

	Vertex() : Key(std::numeric_limits<int>::max()), Parent(nullptr), Data(T()), DeQueued(false){}
	Vertex(T d) : Data(d), Key(std::numeric_limits<int>::max() - 1), Parent(nullptr), DeQueued(false) {}

	friend bool operator<(Vertex<T> &l, Vertex<T> &r){
		return l.Key < r.Key;
	}

	friend bool operator>(Vertex<T> &l, Vertex<T> &r){
		return l.Key > r.Key;
	}

	friend bool operator==(Vertex<T> &l, Vertex<T> &r){
		return l.Data == r.Data;
	}

	friend bool operator!=(Vertex<T> &l, Vertex<T> &r){
		return !(l == r);
	}
};

// A wrapper structure representing a pair of ordered vertices, which functions as a key
// for the < VerticePair<T>,  Edge<T>* > mapping, which is used in the implementation of 
// Prim's Algorithm.
// - Logic: has an 'absolute' key value regardless of values of u, v
//   e.g: (1,2) == (2,1) for key accessor logic 
template <typename T>
struct VerticePair{
	VerticePair() : X(nullptr), Y(nullptr), U(nullptr), V(nullptr){}
	VerticePair(Vertex<T> *u, Vertex<T> *v){
		*this = VerticePair();
		AssignU(u);
		AssignV(v);
	}

	void AssignU(Vertex<T> *u){
		U = u;
		if (U != nullptr && V != nullptr ){
			if (U->Data <= V->Data){
				X = U;
				Y = V;
			}
			else{
				X = V;
				Y = U;

			}
		}
	}

	void AssignV(Vertex<T> *v){
		V = v;
		if (U && V){
			if (U->Data <= V->Data){
				X = U;
				Y = V;
			}
			else{
				X = V;
				Y = U;

			}
		}
	}

  // Operators are solely overloaded to aid in the attempt of efficient tree-derived storage
  // And key access/insertion where this structure wrapper is used as a key
  // Assumption: Distinct vertices values, which will be ordered. 
	friend bool operator==(VerticePair<T> &l, VerticePair<T> &r){
		return l.X == r.X && l.Y == r.Y;
	}
	friend bool operator!=(const VerticePair<T> &l, const VerticePair<T> &r){
		return !(l == r);
	}
  friend bool operator<(const VerticePair<T> &l, const VerticePair<T> &r){
		if (l.X->Data < r.X->Data)
			return true;
		else if (l.X->Data == r.X->Data && l.Y->Data < r.Y->Data)
			return true;
		else
			return false;
	}
	friend bool operator>(const VerticePair<T> &l, const VerticePair<T> &r){
		return !(l < r) && !(l == r);
	}
private:
	Vertex<T> *X, *Y, *U, *V;
};

// This Edge implementation is solely intended to represent undirected weighted edges
// The equality operator is intended to function as an identity operator
// , while the comparison operator is used to order collections of edges in ascending order
template <typename T>
struct Edge{
	Edge(Vertex<T> *From = nullptr, Vertex<T> *To = nullptr, int w = 0) : From(From), To(To), Weight(w){}
	Vertex<T> *From, *To;
	int Weight;

  // Somewhat arbitray/superficial comparison operator overloading to facilate efficient
  // storage in tree-derived structures and key access/retrieval
  // Assumption: Undirected edges with distinct vertice data values.
	friend bool operator==(Edge<T> &l, Edge<T> &r){
		if (l.From == r.From && l.To == r.To)
			return true;
		else
			return false;
	}

	friend bool operator<(Edge<T> &l, Edge<T> &r){
		if (l.Weight < r.Weight)
			return true;
		else
			return false;
	}
};

// TODO: Add encapulsation for member variables
// A graph implementation supporting Weighted Undirected Edges
// Note: For edge-related methods, the implementations maintain ordered 
//       vertice pair logic that u < v for all pairs (u,v) 
template <typename T>
class Graph{
public:

	// * Returns an edge given two vertice values, if it exists, or a NIL value. 
	// * Assumptions:
	// - 1) u, v both exist as vertices in the graph 
	// - 2) u.Data < v.Data
	Edge<T>& GetEdge(T u, T v){

		if (!vMap.ContainsKey(u) || !vMap.ContainsKey(v)){
			return *eNIL;
		}
		else{

			if (u > v){ // Ensures that u < v for proper key set comparison
				T t = v;
				v = u;
				u = t;
			}
			VerticePair<T> vp(vMap[u], vMap[v]);
			if (eMap.ContainsKey(vp))
				return *eMap[vp];
			else
				return *eNIL;
		}
	}

  // Returns an array of all the Vertice pointers.
	DynamicArray<Vertex<T>*> GetAllVertices(){
		Vertex<T> *vB = V.Minimum(), *vE = V.Maximum();
		DynamicArray<Vertex<T>*> A(V.Count());
		while (vB < vE){
			A.Insert(vB);
			vB = V.Successor(vB);
			if (vB == vE)
				A.Insert(vB);
		}
		return A;
	}

  // Creates an empty graph, and intializes the values of the NIL values for 
  // Vertex and Edge pointers
	Graph(){
		vNIL = nullptr;
		eNIL = new Edge<T>(vNIL, vNIL, -1);
	}

  // Creates an undirected edge, which will be mapped to a single ordered VerticePair.
  // Returns whether an edge was created, which is dependent on the pre-existence 
  // of vertices containing data mapped to 'v1' and 'v2'
	bool AddUndirectedEdge(T v1, T v2, int weight = 0){
		if (v1 > v2){
			T t = v1;
			v1 = v2;
			v2 = t;
		}

		auto vertexOne = vMap[v1];
		auto vertexTwo = vMap[v2];

		if (vertexOne && vertexTwo){
			auto e = new Edge<T>(vertexOne, vertexTwo, weight);
			E.Insert(e);
			vertexOne->Adj.AddToHead(vertexTwo);
			vertexTwo->Adj.AddToHead(vertexOne);
			VerticePair<T> vp;
			vp.AssignU( vertexOne );
			vp.AssignV( vertexTwo );
			eMap[vp] = e;
			return true;
		}
		else{
			return false;
		}
	}

  // Creates or overwriters a Vertice and a mapping.
  // Possible TODO: Prevent overwriting?
	bool AddVertex(T d){
		Vertex<T> *t = new Vertex<T>(d);
		V.Insert(t);
		vMap[d] = t;
		return true;
	}

  // Represent NIL pointers to Vertex/Edges
  Vertex<T> *vNIL;
	Edge<T> *eNIL;
	
  // Contain the collection of all Vertices/Edges
  Set< Vertex<T>* > V;
	Set< Edge<T>* > E;
  
  // Contain the mappings of Vertices and Edges
  // Where: 
  //      - Vertice { Data, Vertice }
  //      - Edge    { (u,v), Edge } 
  //       ( with u,v being the data mapped to a pair of vertices belonging to an edge )
  Mapping<T, Vertex<T>* > vMap;
	Mapping<VerticePair<T>, Edge<T>*> eMap;

};

// Kruskal's Algorithm Implementation 
// Note: (POTENTIAL DANGER ZONE)
//  possible TODO: potential bugs if the Graph<T> g gets deleted--may need to implement explicit deep copying
//                 for Set<Edge<T>> res insertions

// Implementation details:
//  - A are DisjointSets testing that the MST is completely connected 
//  - res returns the set of edges comprising a MST, with associated vertex data for all vertices
//    that belong to g, and weight information
//  - the temporary Set<Edge<T>> 'edges' automatically sorts the edges in ascending order based on weight
//    due to operator overloading on the '<' operator for Edge and the the definition of the set data structure
// Implementation dependencies:
// - Edge<T> operator<  := returns true if the lhs' weight is less than the rhs', otherwise true
// - Edge<T> operator== := returns true if the lhs and rhs have the same respective From and To vertices     
//    - Graph.AddEdge: Adds an adjacent vertex for each vertice, but only adds one edge (u,v) into g.E, 
//      where g.E := Set<Edge<T>*> with an arbitrarily defined u and v based on the parameter assignment 
//     (Note this is undirected)  
template <typename T>
LinkedList<Edge<T>> MST_Kruskal(Graph<T> & g){
	DisjointSet<T> A;
	auto v = g.V.Minimum(), e = g.V.Maximum();
	while (v < e){
		A.MakeSet(v->Data);
		v = g.V.Successor(v);
	}
	A.MakeSet(e->Data);

	Set<Edge<T>> edges;
	auto ed = g.E.Minimum(), ee = g.E.Maximum();

	while (ed < ee){
		edges.Insert(*ed);
		ed = g.E.Successor(ed);
	}
	edges.Insert(*ee);

	LinkedList<Edge<T>> res;
	auto fd = edges.Minimum(), ff = edges.Maximum();
	while (fd < ff){
		if (A.FindSet(fd.From->Data) != A.FindSet(fd.To->Data)){
			A.Union(fd.From->Data, fd.To->Data);
			res.AddToTail(fd);
		}
		fd = edges.Successor(fd);
	}
	return res;
}

// Prim's Algorithm Implementation
// Parameters: Graph g, Vertex r := representing an arbitrary starting point
// Returns: A list containing the Edges which comprise a Minimum-Spanning Tree

// Implementation details:
// - Stores all the vertice pointers in a min-heap priority queue,
//   extracting each min, and greedily choosing optimal local paths,
//   while updating the heap based on greedy choices.
// - Vertices contain DeQueued flag, which is set as vertices are extracted
//   from the priority queue for O(1) queue search 
// - TODO: Test whether the min-heap priority functions properly with arbitrarily
//         created vertices and edges (i.e. in random/malicious order) 
// - TODO: Fix Heap implementation -- currently needs to invoke the Minimum 
//         method when the Queue is empty to access every element. 
template <typename T>
LinkedList<Edge<T>*>  MST_Prim(Graph<T> &g, Vertex<T> *r){
	LinkedList<Edge<T>*> res;
	r->Key = 0;
	auto vs = g.GetAllVertices();
	Heap<Vertex<T>*> Q(vs, HeapType::Min);
	
  VerticePair<T> vp;
	while (!Q.Empty()){
		Vertex<T> *u = Q.ExtractMinimum();
		u->DeQueued = true;
		vp.AssignU(u);
    
    // This entire block goes through each Vertex x in v.Adj
		auto adjVertices = u->Adj.Head;
		while (adjVertices){
			Vertex<T> *v = adjVertices->Data;
			vp.AssignV(v);
			Edge<T> *e = g.eMap[vp];
			if (!v->DeQueued && e->Weight < v->Key){
				v->Parent = u;
				v->Key = e->Weight;
				Q.Build();
			}
			adjVertices = adjVertices->Next;
		}

    // TODO: Fix heap to eliminate this clean up end-case
		if (Q.Empty()){
			u = Q.Minimum();
			vp.AssignU(u);

			auto adjVertices = u->Adj.Head;
			while (adjVertices){
				Vertex<T> *v = adjVertices->Data;
				vp.AssignV(v);
				Edge<T> *e = g.eMap[vp];
				if (!v->DeQueued && e->Weight < v->Key){
					v->Parent = u;
					v->Key = e->Weight;
				}
				adjVertices = adjVertices->Next;
			}
		}
	}

  // Queries the list of all the vertices, inserting edges for all vertices with assigned
  // Parent pointers, i.e., edges for (v, v.Parent), where v has a Parent pointer, into
  // a linked list, which will be returned by the method.
  auto vertices = g.GetAllVertices();
	for (int i = 0; i < vertices.size; i++)
	{
		if (vertices[i]->Parent){
			vp.AssignU(g.vMap[vertices[i]->Data]);
			vp.AssignV(g.vMap[vertices[i]->Parent->Data]);
			res.AddToTail(g.eMap[vp]);
		}
	}
	return res;
}

// A wrapper method for MST_Prim, which merely selects what is considered as the minimum vertice
// value in the collection of vertices as the arbirary starting pointer for the implementation
// of Prim's Algorithm in MST_Prim. 
template <typename T>
LinkedList<Edge<T>*> MST_PrimW(Graph<T> &g){
	Vertex<T> *r = g.V.Minimum();
	return MST_Prim<T>(g, r);
}
