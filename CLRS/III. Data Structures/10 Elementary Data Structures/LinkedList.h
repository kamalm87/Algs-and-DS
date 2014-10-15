#pragma once

namespace KNM_DS{

	template <typename T>
	struct Node{
		T Data;
		Node<T> *Next, *Prev;
		Node<T>(T d = T(), Node<T>* n = nullptr, Node<T>* p = nullptr) : Data(d), Next(n), Prev(p){}

		friend bool operator==(const Node<T>& x, const Node<T>& y){
			if (x.Data == y.Data && x.Next == y.Next && x.Prev == y.Prev){
				return true;
			}
			else{
				return false;
			}
		}

		Node<T>* operator=(const Node<T>& rhs){
			Node<T>* n = new Node<T>();
			n->Data = rhs.Data;
			n->Prev = rhs.Prev;
			n->Next = rhs.Next;
			return n;
		}

		Node<T>* operator=(const Node<T>* rhs){
			Node<T>* n = new Node<T>();
			n->Data = rhs->Data;
			n->Prev = rhs->Prev;
			n->Next = rhs->Next;
			return n;
		}
	};


	template <typename T>
	struct LinkedList{
		Node<T> *Head, *Tail;
		size_t Length;
		LinkedList<T>() : Head(nullptr), Tail(nullptr), Length(0){}
		LinkedList<T>(Node<T>* head) : Head(head), Tail(head) Length(0){}

		void addToTail(T data){
			addToTail(new Node<T>(data));
		}

		void addToTail(Node<T> *n){
			if (!Head)
			{
				Head = n;
				Tail = n;
				Length++;
			}
			else{
				Node<T> *t = Tail;
				t->Next = n;
				n->Prev = t;
				Tail = n;
				Length++;
			}
		}

		void addToHead(T data){
			addToHead(new Node<T>(data));
		}

		void addToHead(Node<T> *n){
			if (!Head)
			{
				Head = n;
				Tail = n;
				
			}
			else{
				Head->Prev = n;
				n->Next = Head;
				Head = n;
				Length++;
			}
		}

		bool Delete(T d){
			Node<T>* n = Find(d);
			if (!n) return false;
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
			if (Find(d) == nullptr) return false;
			else
				return true;
		}

		Node<T>* Find(T d){
			Node<T> *C = Head;
			while (C){
				if (d == C->Data)
					return C;
				else
					C = C->Next;
			}
			return nullptr;
		}

		void Swap(Node<T> *Left, Node<T>* Right){
			if (!Left || !Right) return;
			if (Left == Right) return;
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

}

