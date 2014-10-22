#include "Auxiliary/Map.h"
#include "Auxiliary/LinkedList.h"
#include "Auxiliary/Queue.h"

#include <string>

template <typename T>
class Graph{
private:
   
    enum VColor{
        WHITE,
        GRAY,
        BLACK
    };

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

public:
    // TODO: Temp debugging area

         std::string GetColor(Vertex<T>* v){
        if(v->c == WHITE)
            return "WHITE";
        else if (v->c == GRAY)
            return "GRAY";
        else
            return "BLACK";
    }
    

    Mapping<T, Vertex<T>* > vMap;

    // TODO: Temp debugging area

    Graph(){
        NIL = new Vertex<T>();
    }
   
    // Selects an arbitrary Node to begin as the start point
    void BreadthFirstSearch(){
        BreadthFirstSearch(V.Minimum());
    }

    void BreadthFirstSearch(Vertex<T> * S){
        auto b = V.Minimum();
        auto e = V.Maximum();

        e->c = WHITE;
        e->Parent = NIL;
        // TODO: numerics<max>
        e->Distance = 10000000;
        while(b < e){
            b->c = WHITE;
            // TODO: numerics<max>
            b->Distance = 10000000;
            b->Parent = NIL;
            b = V.Successor(b);
       }
    
       S->c = GRAY;
       S->Distance = 0;
       S->Parent = NIL; 

       Queue<Vertex<T>* > Q;
       Q.Enqueue(S); 

       while(!Q.Empty())
       {
            Vertex<T> *u = Q.Dequeue();
            auto vNode = u->Adj.Head;
            std::cout << "Adj elements: " << u->Adj.Length;
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
            std::cout << std::endl;
            u->c = BLACK;

       }
    }


    void printVertexInfo(T d){
        Vertex<T> *v = vMap[d];
        std::cout << "********  ";
        std::cout << v->Data << " -> Adjacent: " << v->Adj.Length << std::endl;
        auto c = v->Adj.Head;
        while(c){
            std::cout << c->Data->Data << "->";
            c = c->Next;
        }
        std::cout << std::endl;
    }


    bool AddVertex(T d){
        Vertex<T> *t = new Vertex<T>(d);
        V.Insert(t);
        vMap[d] = t;
    }


    bool AddUndirectedEdge(T v1, T v2, int weight = 0){
        auto vertexOne = vMap[v1];
        auto vertexTwo = vMap[v2];

        auto e = new Edge<T>(vertexOne, vertexTwo, 0);
        E.Insert(e);
        vertexOne->Adj.AddToHead(vertexTwo);
        vertexTwo->Adj.AddToHead(vertexOne);
    }

    bool AddEdge(T from, T to, int weight = 0 ){
        auto fromVertex  = vMap[from];
        auto toVertex = vMap[to];

        auto e = new Edge<T>(fromVertex, toVertex, 0);
        E.Insert(e);
        fromVertex->Adj.AddToHead(toVertex);
   }

};
