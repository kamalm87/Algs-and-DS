#include <stddef.h>

template <typename T>
struct Node{
    T Data;
    Node<T> *Next, *Prev;
    Node(T d = T(), Node<T> *n = nullptr, Node<T> *p = nullptr) : Data(d), Next(n), Prev(p){}

    // Defined for swap function
    friend bool operator==(const Node<T> &x, const  Node<T> &y){
        if(x.Data == y.Data && x.Next == y.Next && x.Prev == y.Prev){
            return true;
        }
        else
            return false;
    }

    Node<T>* operator=(const Node<T> &rhs){
        Node<T> *n = new Node<T>();
        n->Data = rhs.Data;
        n->Next = rhs.Next;
        n->Prev = rhs.Prev;
    }
    
    Node<T>* operator=(const Node<T> *rhs){
        Node<T> *n = new Node<T>();
        n->Data = rhs->Data;
        n->Next = rhs->Next;
        n->Prev = rhs->Prev;
    }

};
  
template <typename T>
struct LinkedList{
    Node<T> *Head, *Tail;
    size_t Length;

    LinkedList<T>(): Head(nullptr), Tail(nullptr), Length(0) {}
    LinkedList<T>(T d): Head(new Node<T>(d)), Tail(Head), Length(1) {}
    
    void AddToTail(T d){
        AddToTail(new Node<T>(d));
    }

    void AddToTail(Node<T>* n){
        if(!Head){
            Head = n;
            Tail = n;
            n->Next = nullptr;
            Length++;
        } 
        else{
            Node<T> *temp = Tail;
            temp->Next = n;
            n->Prev = temp;
            Tail = n;
            Length++;
        }
    }

    void AddToHead(T d){
        AddToHead(new Node<T>(d));
    }

    void AddToHead(Node<T>* n){
        if(!Head){
            Head = n;
            Tail = n;
            n->Next = nullptr;
            Length++;
        }
        else{
            Node<T> *temp = Head;
            n->Next = temp;
            temp->Prev = n;
            Head = n;
            Length++;
        }
    }

    bool Delete(T d){
	    Node<T>* n = Find(d);
		if (!n) 
            return false;
		else
			return Delete(n);
	}

    // TODO: Test all edge cases: deleting head/tails
	bool Delete(Node<T>* n){
    	if (!n) 
            return false;
		if (n->Prev)
			n->Prev->Next = n->Next;
		else
		    Head = n;
		if (n->Next)
		    n->Next->Prev = n->Prev;
        if(n == Tail)
        {
            n->Prev->Next = nullptr;
        }
        if(n == Head){
            Head = n->Next;
        }
		Length--;
		delete n;
		return true;
	}


	bool Contains(T d){
    	if (Find(d) == nullptr) 
            return false;
    	else
			return true;
		}

    Node<T>* Find(T d){
		Node<T> *C = Head;
		while (C != nullptr){
		    if (d == C->Data)
				return C;
			else
				C = C->Next;
			}
		    return nullptr;
	}

	void Swap(Node<T> *Left, Node<T>* Right){
		if (!Left || !Right) 
            return;
		if (Left == Right) 
            return;
		else if (Left->Next == Right || Right->Next == Left){
			// if the nodes are adjacent, just swap the data
			T t = Left->Data;
			Left->Data = Right->Data;
			Right->Data = t;
			return;
		}
		else{
			Node<T> *TempNode = new Node<T>();
			// Store the Left parameter's pointers to a TempNode
			TempNode->Next = Left->Next;
			TempNode->Prev = Left->Prev;

			// Assign the pointers 
			Left->Next = Right->Next;
			if (Left->Next)
				Left->Next->Prev = Left;
    		Left->Prev = Right->Prev;
		
            if (Left->Prev)
			    Left->Prev->Next = Left;


        	Right->Next = TempNode->Next;
			if (Right->Next)
				Right->Next->Prev = Right;
			Right->Prev = TempNode->Prev;
			if (Right->Prev)
				Right->Prev->Next = Right;

			if (!Left->Prev) Head = Left;
			if (!Right->Prev) Head = Right;
			if (!Left->Next) Tail = Left;
			if (!Right->Next) Tail = Right;
		}
    }

	void InsertionSort(){
		Node<T> *j = Head->Next;
		while (j){
			Node<T> *key = j, *i = j->Prev;

			while (i && i->Data > key->Data){
				Swap(i, i->Prev);
				i = i->Prev;
			}
			i ? Swap(i->Next, key) : Swap(Head, key);
			j = j->Next;
		}
	}

};
