#pragma once
#include <iostream>

// Represent colors in the Red-Black implementation
		enum Color{
			RED = 0,
			BLACK = 1
		};

		// Class representing a node in a Red-Black Tree.
		// * Each Node in a RBT has a parent, data, a color, and two children: left, right
		// * Since the following implemention of the RBT has an instnance variable
		// containing its 'NIL' value, the pointers values here are defaulted to nullptr
		// , which has no logical significance on any of the RBT methods. 
		// (Node pointer assignments will happen within the RBT methods. )
		template <typename T>
		class Node{
		public:

			Node() : Left(nullptr), Right(nullptr), Parent(nullptr), C(BLACK){}
			Node(T d) : Data(d), Left(nullptr), Right(nullptr), Parent(nullptr), C(BLACK){}
			Node(T d, Color c) : Data(d), C(c), Left(nullptr), Right(nullptr), Parent(nullptr){}

			Node<T> *Left, *Right, *Parent;
			T Data;
			Color C;
		};

		// Class representing a Red-Black Tree
		// * The template argument determines the templatized Node (defined above), which will 
		//   represent Red-Black Tree nodes.
		// * public methods: Insert, Delete, Search, Predecessor, Successor, Minimum, Maximum
		template <typename T>
		class RBT{
		public:

			// Order of these is important for the constructor's initializer
			Node<T> *NIL, *Root;

			// Creates an "empty" tree, setting the root as the dummy node NIL,
			// which is supposed to be the parent of the root and the value that
			// all leaves' children will point at
			RBT() : Root(NIL), NIL(new Node < T >()), count(0) {}

			// This method wraps the full insertion method 
			// In addition: assigns the parent and children points point to the tree's
			// NIL value
		public: void Insert(T d){
			// Create a new Node to insert, setting the default pointers to the NIL dummy node
			auto n = new Node<T>(d);
			n->Parent = NIL;
			n->Left = NIL;
			n->Right = NIL;
			Insert(n);
		}

				// Implemention of the RBT.Insert algorithm
		public: void Insert(Node<T>* z){
			Node<T> *y = NIL;
			Node<T> *x = Root;

			while (x != NIL){
				y = x;
				if (z->Data < x->Data){
					x = x->Left;
				}
				else
					x = x->Right;
			}
			z->Parent = y;

			if (y == NIL){
				Root = z;
			}
			else if (z->Data < y->Data){
				y->Left = z;
			}
			else {
				y->Right = z;
			}

			z->Left = NIL;
			z->Right = NIL;
			z->C = RED;
			count++;
			RB_InsertFixup(z);
		}

				// Implementation of the Tree.Succesor algorithm (which is unchanged)
		public: Node<T>* Successor(Node<T>* x){
			if (x->Right != NIL){
				return Minimum(x->Right);
			}
			Node<T>* y = x->Parent;
			while (y != NIL && x == y->Right){
				x = y;
				y = y->Parent;
			}
			return y;
		}
				// Implementation of the Tree.Predecessor algorithm (which is unchanged)
		public: Node<T>* Predecessor(Node<T>* x){
			if (x->Left != NIL){
				return Maximum(x->Left);
			}
			Node<T>* y = x->Parent;
			while (y != NIL && x == y->Left){
				x = y;
				y = y->Parent;
			}
			return y;
		}

				// Wrapper for the Tree.Minimum function, operating on the Tree's Root
		public: Node<T>* Minimum(){
			return Minimum(Root);
		}

				// Implementation of the Tree.Minimum algorithm (which is unchanged)
		public: Node<T>* Minimum(Node<T>* x){
			while (x->Left != NIL){
				x = x->Left;
			}
			return x;
		}

				// Wrapper for the Tree.Maximum function, operating on the Tree's Root
		public: Node<T>* Maximum(){
			return Maximum(this->Root);
		}

				// Implementation of the Tree.Minimum algorithm (which is unchanged)
		public: Node<T>* Maximum(Node<T>* x){
			while (x->Right != NIL){
				x = x->Right;
			}
			return x;
		}

				// Wrapper for the Tree.Search algorithm, operating on the Tree's Root
		public: Node<T>* Search(T d){
			return Search(this->Root, d);
		}

				// Implementation of the Tree.Search algorihtm (which is unchanged)
		public: Node<T>* Search(Node<T>* x, T d){
			if (x == NIL || d == x->Data)
			{
				return x;
			}
			if (d < x->Data){
				return Search(x->Left, d);
			}
			else
				return Search(x->Right, d);
		}

				// Wrapper for the Tree.InorderTreeWalk algorihtm, operating on the Tree's root
		public: void InorderTreeWalk(){
			InorderTreeWalk(Root);
		}

				// Implementation of the Tree.InorderTreeWalk algorithm
		public: void InorderTreeWalk(Node<T>* x){
			if (x != NIL){
				InorderTreeWalk(x->Left);
				std::cout << x->Data << " -> ";
				InorderTreeWalk(x->Right);
			}
		}

				// Wrapper for the Tree.Delete algorithm
		public: void Delete(T d){
			Node<T> *n = this->Search(this->Root, d);
			if (n != NIL)
				Delete(n);
		}

				// Implementation of the RB-Tree.Delete algorithm
		public: void Delete(Node<T>* z){
			Node<T> *x = nullptr, *y = z;
			Color yOriginalColor = y->C;

			if (z->Left == NIL){
				x = z->Right;
				RB_Transplant(z, z->Right);
			}
			else if (z->Right == NIL){
				x = z->Left;
				RB_Transplant(z, z->Left);
			}
			else{
				y = Minimum(z->Right);
				yOriginalColor = y->C;
				x = y->Right;
				if (y->Parent == z){
					x->Parent = y;
				}
				else{
					RB_Transplant(y, y->Right);
					y->Right = z->Right;
					y->Right->Parent = y;
				}
				RB_Transplant(z, y);
				y->Left = z->Left;
				z->Left->Parent = y;
				z->C= z->C;
			}

			count--;
			if (yOriginalColor == BLACK){
				RB_DeleteFixup(x);
			}
		}

				// Implementation of the RB-Transplant algorithm
		private: void RB_Transplant(Node<T> *u, Node<T> *v){
			if (u->Parent == NIL){
				Root = v;
			}
			else if (u == u->Parent->Left)
			{
				u->Parent->Left = v;
			}
			else{
				u->Parent->Right = v;
			}
			v->Parent = u->Parent;
		}

				 // Implementation of the RB-T.Delete-Fixup algorithm
		private: void RB_DeleteFixup(Node<T> *x){
			while (x != this->Root && x->C== BLACK){
				if (x == x->Parent->Left){
					Node<T> *w = x->Parent->Right;
					if (w->C == RED){
						w->C = BLACK;
						x->Parent->C= RED;
						LeftRotate(x->Parent);
						w = x->Parent->Right;
					}

					if (w->Left->C == BLACK && w->Right->C == BLACK){
						w->C = RED;
						x = x->Parent;
					}
					else
					{
						if (w->Right->C== BLACK){
							w->Left->C= BLACK;
							w->C = RED;
							RightRotate(w);
							w = x->Parent->Right;
						}
						w->C= x->Parent->C;
						x->Parent->C = BLACK;
						w->Right->C = BLACK;
						LeftRotate(x->Parent);
						x = this->Root;
					}
				}
				else{
					Node<T> *w = x->Parent->Left;
					if (w->C== RED){
						w->C= BLACK;
						x->Parent->C = RED;
						RightRotate(x->Parent);
						w = x->Parent->Left;
					}

					if (w->Left->C == BLACK && w->Right->C == BLACK){
						w->C = RED;
						x = x->Parent;
					}
					else
					{
						if (w->Left->C == BLACK){
							w->Right->C = BLACK;
							w->C = RED;
							LeftRotate(w);
							w = x->Parent->Left;
						}
						w->C= x->Parent->C;
						x->Parent->C = BLACK;
						w->Left->C = BLACK;
						RightRotate(x->Parent);
						x = this->Root;
					}
				}
			}

			x->C = BLACK;

		}

				 // Implementation of the RB-T.Delete-Fixup algorithm
		private: void RB_InsertFixup(Node<T>* z){
			while (z->Parent->C == RED){

				if (z->Parent == z->Parent->Parent->Left) // Parent is left child of grandparent
				{
					Node<T> *y = z->Parent->Parent->Right;
					if (y->C == RED){
						z->Parent->C = BLACK;
						y->C = BLACK;
						z->Parent->Parent->C = RED;
						z = z->Parent->Parent;
					}
					else{
						if (z == z->Parent->Right){
							z = z->Parent;
							LeftRotate(z);
						}
						z->Parent->C = BLACK;
						z->Parent->Parent->C = RED;
						RightRotate(z->Parent->Parent);
					}
				}
				else  // Parent is left child of grandparent
				{
					Node<T> *y = z->Parent->Parent->Left;
					if (y->C == RED){
						z->Parent->C = BLACK;
						y->C = BLACK;
						z->Parent->Parent->C = RED;
						z = z->Parent->Parent;
					}
					else{
						if (z == z->Parent->Left){
							z = z->Parent;
							RightRotate(z);
						}
						z->Parent->C = BLACK;
						z->Parent->Parent->C = RED;
						LeftRotate(z->Parent->Parent);
					}
				}
			}
			this->Root->C = BLACK;
		}

				 // Implementation of the RB-T.Delete-Fixup algorithm
		private: void RightRotate(Node<T>* x){
			Node<T> *y = x->Left;
			x->Left = y->Right;
			y->Right->Parent = x;
			y->Parent = x->Parent;

			if (x->Parent == NIL){
				Root = y;
			}
			else
			{
				if (x == x->Parent->Left){
					x->Parent->Left = y;
				}
				else{
					x->Parent->Right = y;
				}
			}
			y->Right = x;
			x->Parent = y;
		}

				 // Implementation of the RB-T.Delete-Fixup algorithm
		private: void LeftRotate(Node<T>* x){
			Node<T> *y = x->Right;
			x->Right = y->Left;
			y->Left->Parent = x;
			y->Parent = x->Parent;

			if (x->Parent == NIL){
				Root = y;
			}
			else{
				if (x == x->Parent->Left){
					x->Parent->Left = y;
				}
				else {
					x->Parent->Right = y;
				}
			}

			y->Left = x;
			x->Parent = y;
		}

				 // Method to get the 
		public: size_t Height(){
			return Height(this->Root);
		}

				// Method to get the Height of the Tree
		public: size_t Height(Node<T>* n){
			if (n == NIL) return 0;

			size_t hl = Height(n->Left);
			size_t hr = Height(n->Left);
			return (1 + (hl < hr ? hr : hl));
		}

				// Method to get the number of elements within the Tree
		public: size_t Count(){
			return count;
		}

				// Variable tracking the number of elments within the Tree
		private: size_t count;
		};
