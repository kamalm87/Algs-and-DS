namespace KNM_DS{

	// Class to represent an Interval  of a generic type
	// Start: the beginning/low endpoint, Finish: ending/high endpoint
	// Methods: Overlap, LeftOf, RightOf: compare the invoking Interval to another Interval
	//			returning a boolean value indicating whether the the invoking interval is 
	//			respectively overlapped, to the left of, or to the right of the parametized Interval
	// ( Assumption: The generic type has well-defined comparison operators: <, <=, ==. )
	template <typename T>
	class Interval{
	public:

		// ( Assumption: intervals are closed by default/in book's examples. )
		Interval(T s = T(), T f = T(), bool closed = true) : Start(s), Finish(f), Closed(closed){}
		T Start, Finish;
		bool Closed;
		
		bool Overlap(Interval<T> &r){
			if (this->Start <= r.Finish && r.Start <= this->Finish)
				return true;
			else
				return false;
		}

		bool LeftOf(Interval<T> &r){
			if (this->Finish < r.Start)
				return true;
			else
				return false;
		}

		bool RightOf(Interval<T> &r){
			if (r.Finish < this->Start)
				return true;
			else
				return false;
		}

	};

	// Represent colors in the Red-Black implementation
	enum Color{
		RED = 0,
		BLACK = 1
	};

	// [Augmented for Interval Trees: ]
	// * Given an Interval, as defined in the above class.
	// * The Data member is defined as the Interval's low endpoint
	// * The Max member is defined as the maximum relative to the a tree rooted as the node
	//   - defined as Max(x.Max, x.Left.Max, x.Right.Max), where x is the Node
	// Class representing a node in a Red-Black Tree.
	// * Each Node in a RBT has a parent, data, a color, and two children: left, right
	// * Since the following implemention of the RBT has a member
	// containing its 'NIL' value, the pointers values here are defaulted to nullptr
	// , which has no logical significance on any of the RBT methods. 
	// (Node pointer assignments will happen within the RBT methods. )
	template <typename T>
	class Node{
	public:

		// Interval Tree Augmentation:
		// * The node's key become's the Interval's Start value
		Node() : Left(nullptr), Right(nullptr), Parent(nullptr), Color(BLACK){}
		Node(Interval<T> & i) : Data(i.Start), Left(nullptr), Right(nullptr), Parent(nullptr), Interval(i), Max(FindMax(Left, Right)), Color(BLACK) {}
		Node(Interval<T> & i, Color c) : Data(i.Start), Color(c), Left(nullptr), Right(nullptr), Interval(i), Max(Interval.Finish), Parent(nullptr){}
		Interval<T> Interval;
		Node<T> *Left, *Right, *Parent;
		T Data, Max;
		Color Color;

		// ( Assumption: the generic constructor T() creates a logical minimum  dummy value. )
		T FindMax( Node<T> *l, Node<T> *r){
			// Puts dummy logical minimum value if empty children nodes
			if (l&&r)
				return FindMax(this->Interval.Finish, l->Max, r->Max);
			else if (l)
				return FindMax(this->Interval.Finish, l->Max, T());
			else if (r)
				return FindMax(this->Interval.Finish, T(), r->Max);
			else
				return this->Interval.Finish;
		}

		T FindMax(T Max, T LeftMax, T RightMax){
			return Max > LeftMax && Max > RightMax ? Max :						// Return the element's max, if it's max
							LeftMax > Max && LeftMax > RightMax ? LeftMax :		// Return the element's LeftMax, if it's max
								RightMax;										// Return the element's RightMax otherwise, == values returned here
		}
	};

	// Class representing a Red-Black Tree
	// * The template argument determines the templatized Node (defined above), which will 
	//   represent Red-Black Tree nodes.
	// * public methods: Insert, Delete, Search, Predecessor, Successor, Minimum, Maximum
	template <typename T>
	class IntervalTree{
	public:

		// Order of these is important for the constructor's initializer
		Node<T> *NIL, *Root;

		// Creates an "empty" tree, setting the root as the dummy node NIL,
		// which is supposed to be the parent of the root and the value that
		// all leaves' children will point at
		IntervalTree() : Root(NIL), NIL(new Node < T >()), count(0) {}



		size_t Height(){
			return Height(this->Root);
		}

		// Method to get the Height of the Tree
		size_t Height(Node<T>* n){
			if (n == NIL) return 0;

			size_t hl = Height(n->Left);
			size_t hr = Height(n->Left);
			return (1 + (hl < hr ? hr : hl));
		}
	
		// Method to get the number of elements within the Tree
		size_t Count(){
			return count;
		}

		// Function wrappers for delete, creating either a single value or ranged
		// interval to search for and subsequently delete if an overlapping Node is found.
		// If an overlapping Node is found, then it will be deleted and true will be returned
		// , indicating successful deletion.
		bool Delete(T d){
			Node<T>* x = Search(d, d);
			if (x != NIL){
				Delete(x);
				return true;
			}
			else
				return false;
		}
		bool Delete(T l, T h){
			Node<T>* x = Search(l, h);
			if (x != NIL){
				Delete(x);
				return true;
			}
			else
				return false;
		}


		// Augmented method for interval tree:
		// Searches for a Node containing an interval overlapping the search parameter
		Node<T>* IntervalSearch(Interval<T> i){
			Node<T>* x = this->Root;
			while (x != this->NIL && !x->Interval.Overlap(i)){
				if (x->Left != this->NIL && x->Left->Max < i.Closed)
					x = x->Left;
				else
					x = x->Right;
			}
			return x;
		}
		
		// Augmented function wrapper for IntervalSearch: creates an Interval with a local maximum to use as
		// as a parameter for IntervalSearch
		Node<T>* Search(T low, T high){
			return IntervalSearch(Interval<T>(low, high));
		}


		void Insert(Interval<T> i){
			auto n = new Node<T>(i);
			n->Parent = NIL;
			n->Left = NIL;
			n->Right = NIL;
			Insert(n);
		}


		// This method wraps the full insertion method 
		// In addition: assigns the parent and children points point to the tree's
		// NIL value
		void Insert(T low, T high){
			// Create a new Node to insert, setting the default pointers to the NIL dummy node
			auto n = new Node<T>(Interval<T>(low, high));
			n->Parent = NIL;
			n->Left = NIL;
			n->Right = NIL;
			Insert(n);
		}

		// Implemention of the RBT.Insert algorithm
		void Insert(Node<T>* z){
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
			z->Color = RED;
			count++;
			RB_InsertFixup(z);
			while (z != NIL){
				z = z->Parent;
				z->Max = z->FindMax(z->Left != this->NIL ? z->Left : nullptr, z->Right != this->NIL ? z->Right : nullptr);
			}

		}

		// Implementation of the Tree.Succesor algorithm (which is unchanged)
		Node<T>* Successor(Node<T>* x){
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
		Node<T>* Predecessor(Node<T>* x){
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
		Node<T>* Minimum(){
			return Minimum(Root);
		}

		// Implementation of the Tree.Minimum algorithm (which is unchanged)
		Node<T>* Minimum(Node<T>* x){
			while (x->Left != NIL){
				x = x->Left;
			}
			return x;
		}

		// Wrapper for the Tree.Maximum function, operating on the Tree's Root
		Node<T>* Maximum(){
			return Maximum(this->Root);
		}

		// Implementation of the Tree.Minimum algorithm (which is unchanged)
		Node<T>* Maximum(Node<T>* x){
			while (x->Right != NIL){
				x = x->Right;
			}
			return x;
		}

		// Wrapper for the Tree.Search algorithm, operating on the Tree's Root
		Node<T>* Search(T d){
			return Search(this->Root, d);
	
		}	

		// Implementation of the Tree.Search algorihtm (which is unchanged)
		Node<T>* Search(Node<T>* x, T d){
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
		void InorderTreeWalk(){
			InorderTreeWalk(Root);
		}

		// Implementation of the Tree.InorderTreeWalk algorithm
		void InorderTreeWalk(Node<T>* x){
			if (x != NIL){
				InorderTreeWalk(x->Left);
				std::cout << x->Data << " -> ";
				InorderTreeWalk(x->Right);
			}
		}

		// Implementation of the RB-Tree.Delete algorithm
		void Delete(Node<T>* z){
			Node<T> *x = nullptr, *y = z;
			Color yOriginalColor = y->Color;

			if (z->Left == NIL){
				x = z->Right;
				RB_Transplant(z, z->Right);
			}
			else if (z->Right == NIL){
				x = z->Left;
				RB_Transplant(z, z->Left);
			} else{
				y = Minimum(z->Right);
				yOriginalColor = y->Color;
				x = y->Right;
				if (y->Parent == z){
					x->Parent = y;
				} else{
					RB_Transplant(y, y->Right);
					y->Right = z->Right;
					y->Right->Parent = y;
				}
				RB_Transplant(z, y);
				y->Left = z->Left;
				z->Left->Parent = y;
				z->Color = z->Color;
			}

			count--;
			if (yOriginalColor == BLACK){
				RB_DeleteFixup(x);
			}
		}
	private:
		// Implementation of the RB-Transplant algorithm
		void RB_Transplant(Node<T> *u, Node<T> *v){
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
		void RB_DeleteFixup(Node<T> *x){
			while (x != this->Root && x->Color == BLACK){
				if (x == x->Parent->Left){
					Node<T> *w = x->Parent->Right;
					if (w->Color == RED){
						w->Color = BLACK;
						x->Parent->Color = RED;
						LeftRotate(x->Parent);
						w = x->Parent->Right;
					}

					if (w->Left->Color == BLACK && w->Right->Color == BLACK){
						w->Color = RED;
						x = x->Parent;
					}
					else
					{
						if (w->Right->Color == BLACK){
							w->Left->Color = BLACK;
							w->Color = RED;
							RightRotate(w);
							w = x->Parent->Right;
						}
						w->Color = x->Parent->Color;
						x->Parent->Color = BLACK;
						w->Right->Color = BLACK;
						LeftRotate(x->Parent);
						x = this->Root;
					}
				}
				else{
					Node<T> *w = x->Parent->Left;
					if (w->Color == RED){
						w->Color = BLACK;
						x->Parent->Color = RED;
						RightRotate(x->Parent);
						w = x->Parent->Left;
					}

					if (w->Left->Color == BLACK && w->Right->Color == BLACK){
						w->Color = RED;
						x = x->Parent;
					}
					else
					{
						if (w->Left->Color == BLACK){
							w->Right->Color = BLACK;
							w->Color = RED;
							LeftRotate(w);
							w = x->Parent->Left;
						}
						w->Color = x->Parent->Color;
					x->Parent->Color = BLACK;
					w->Left->Color = BLACK;
					RightRotate(x->Parent);
					x = this->Root;
					}
				}
			}	
			x->Color = BLACK;
		}

		// Implementation of the RB-T.Delete-Fixup algorithm
		void RB_InsertFixup(Node<T>* z){
			while (z->Parent->Color == RED){

			if (z->Parent == z->Parent->Parent->Left) // Parent is left child of grandparent
			{
				Node<T> *y = z->Parent->Parent->Right;
				if (y->Color == RED){
					z->Parent->Color = BLACK;
					y->Color = BLACK;
					z->Parent->Parent->Color = RED;
					z = z->Parent->Parent;
				}
				else{
					if (z == z->Parent->Right){
						z = z->Parent;
						LeftRotate(z);
					}
					z->Parent->Color = BLACK;
					z->Parent->Parent->Color = RED;
					RightRotate(z->Parent->Parent);
				}
			}
			else  // Parent is left child of grandparent
			{
				Node<T> *y = z->Parent->Parent->Left;
				if (y->Color == RED){
					z->Parent->Color = BLACK;
					y->Color = BLACK;
					z->Parent->Parent->Color = RED;
					z = z->Parent->Parent;
				}
				else{
					if (z == z->Parent->Left){
						z = z->Parent;
						RightRotate(z);
					}
					z->Parent->Color = BLACK;
					z->Parent->Parent->Color = RED;
					LeftRotate(z->Parent->Parent);
				}
			}
		}
		this->Root->Color = BLACK;
	}

	 // Implementation of the RB-T.Delete-Fixup algorithm
	void RightRotate(Node<T>* x){
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
		x->Max = y->Max;
		x->Max = x->FindMax(x->Left != NIL ? x->Left : nullptr, x->Right != NIL ? x->Right : nullptr);
	}

		// Implementation of the RB-T.Delete-Fixup algorithm
		void LeftRotate(Node<T>* x){
			Node<T> *y = x->Right;
			x->Right = y->Left;			// x->Right = Beta
			y->Left->Parent = x;		// Beta->Parent = x
			y->Parent = x->Parent;		// swap parent (x,y)
	
			if (x->Parent == NIL){		// if parent NIL, it y becomes root
				Root = y;
			}
			else{						// 
				if (x == x->Parent->Left){	//
					x->Parent->Left = y;
				}
				else {
					x->Parent->Right = y;
				}
			}

			y->Left = x;
			x->Parent = y;
			x->Max = y->Max;
			x->Max = x->FindMax(x->Left != NIL ? x->Left : nullptr, x->Right != NIL ? x->Right : nullptr);
		}

		// Variable tracking the number of elments within the Tree
		size_t count;
	
	};
}

