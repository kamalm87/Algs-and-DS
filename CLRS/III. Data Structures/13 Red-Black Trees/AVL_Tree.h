namespace KNM_DS{
	template <typename T>
	class AVLNode{
	private:
		T data;
		int height;
		AVLNode<T> *parent, *left, *right;
	public:
		AVLNode() : height(0), parent(nullptr), left(nullptr), right(nullptr){}
		AVLNode(T d) : data(d), height(0), parent(nullptr), left(nullptr), right(nullptr){}

		T Data(){
			return this->data;
		}
		int Height(){ return this->height; }
		AVLNode<T>* Parent(){ return parent; };
		AVLNode<T>* Left(){ return left; };
		AVLNode<T>* Right(){ return right; };

		size_t UpdateHeight(){

			if (left != nullptr && right != nullptr){

				if (left->Height() > right->Height())
					height = left->Height() + 1;
				else
					height = right->Height() + 1;
			}
			else if (left != nullptr){
				height = left->Height() + 1;
			}
			else if (right != nullptr){
				height = right->Height() + 1;
			}
			else{
				height = 0;
			}
			return height;
		}

		int Balance(){
			if (this->Left() != nullptr && this->Right() != nullptr){
				return (this->Left()->Height() - this->Right()->Height());
			}
			else if (this->Left() != nullptr){
				return this->Left()->Height() + 1;
			}
			else if (this->Right() != nullptr){
				return (-1) * (this->Right()->Height() + 1);
			}
			else
				return 0;

		}

		void RemoveParent(){
			this->parent = nullptr;
		}

		AVLNode<T>* SetLeft(AVLNode<T>* n){
			if (n != nullptr) n->parent = this;
			left = n;
			UpdateHeight();
			return left;
		}

		AVLNode<T>* SetRight(AVLNode<T>* n){
			if (n != nullptr) n->parent = this;
			right = n;
			UpdateHeight();
			return right;
		}
	};

	template <typename T>
	class TreeAVL{
	private:
		AVLNode<T> *Root;
		size_t height, count;
		void setRoot(AVLNode<T>* n){
			Root = n;
			if (Root != nullptr) Root->RemoveParent();
		}

		void rotateLeft(AVLNode<T>* n){
			AVLNode<T>* p = n->Parent();
			enum { left, right } side;
			if (p != nullptr){

				if (p->Left() == n){
					side = left;
				}
				else
					side = right;
			}
			AVLNode<T>* temp = n->Right();
			n->SetRight(temp->Left());
			temp->SetLeft(n);

			if (p != nullptr){
				if (side == left){
					p->SetLeft(temp);
				}
				if (side == right)
					p->SetRight(temp);
			}
			else{
				setRoot(temp);
			}
		}

		void rotateRight(AVLNode<T>* n){
			AVLNode<T>* p = n->Parent();
			enum { left, right } side;
			if (p != nullptr){

				if (p->Left() == n){
					side = left;
				}
				else
					side = right;
			}
			AVLNode<T>* temp = n->Left();
			n->SetLeft(temp->Right());
			temp->SetRight(n);

			if (p != nullptr){
				if (side == left){
					p->SetLeft(temp);
				}
				if (side == right)
					p->SetRight(temp);
			}
			else{
				setRoot(temp);
			}
		}

		void balanceAt(AVLNode<T>* n){
			int bal = n->Balance();
			if (bal > 1){
				if (n->Left()->Balance() < 0)
					rotateLeft(n->Left());
				rotateRight(n);
			}
			if (bal < -1){
				if (n->Right()->Balance() > 0)
					rotateRight(n->Right());
				rotateLeft(n);
			}
		}

		AVLNode<T>* findNode(T d){
			AVLNode<T>* temp = Root;
			while (temp){

				if (d == temp->Data())
					return temp;
				else if (d < temp->Data())
					temp = temp->Left();
				else
					temp = temp->Right();
			}
			return nullptr;
		}

	public:
		TreeAVL() : Root(nullptr), height(0), count(0){}
		TreeAVL(T d) : Root(new AVLNode<T>(d)), height(0), count(1){}

		bool Insert(T d){
			AVLNode<T>* inserted_node;

			if (Root == nullptr){
				Root = new AVLNode<T>(d);
				count++;
				return true;
			}
			else{

				AVLNode<T>* temp = Root;

				while (true){

					if (temp->Data() > d){
						if (temp->Left() == nullptr){
							inserted_node = temp->SetLeft(new AVLNode<T>(d));
							break;
						}
						else{
							temp = temp->Left();
						}
					}
					else if (temp->Data() < d){
						if (temp->Right() == nullptr){
							inserted_node = temp->SetRight(new AVLNode<T>(d));
							break;
						}
						else{
							temp = temp->Right();
						}
					}
					else{
						return false;
					}

				}

				temp = inserted_node;

				while (temp){
					temp->UpdateHeight();
					balanceAt(temp);
					temp = temp->Parent();
					if (temp == Root) height = Root->Height();
				}
				count++;
				return true;
			}

		}

		bool Delete(T d)
		{
			if (!Root) return false;
			AVLNode<T> *replacement, *replacement_parent, *temp_Node;
			AVLNode<T> * to_be_removed = findNode(d);
			if (!to_be_removed) return false;

			AVLNode<T> * p = to_be_removed->Parent();

			enum { left, right } side;
			if (p != 0)
			{
				if (p->Left() == to_be_removed) side = left;
				else side = right;
			}

			int bal = to_be_removed->Balance();

			if (!to_be_removed->Left() && !to_be_removed->Right() )
			{
				if (p != 0)
				{
					if (side == left) p->SetLeft(nullptr);
					else p->SetRight(nullptr);

					delete to_be_removed;
					p->UpdateHeight();
					balanceAt(p);
				}
				else
				{
					setRoot((AVLNode<T>*)0);
					delete to_be_removed;
				}

			}
			else if (!to_be_removed->Right())
			{
				if (p)
				{
					if (side == left) p->SetLeft(to_be_removed->Left());
					else p->SetRight(to_be_removed->Left());

					delete to_be_removed;
					p->UpdateHeight();
					balanceAt(p);
				}
				else
				{
					setRoot(to_be_removed->Left());
					delete to_be_removed;
				}
			}

			else if (to_be_removed->Left() == 0)
			{
				if (p != 0)
				{
					if (side == left) p->SetLeft(to_be_removed->Right());
					else p->SetRight(to_be_removed->Right());

					delete to_be_removed;
					p->UpdateHeight();
					balanceAt(p);
				}
				else
				{
					setRoot(to_be_removed->Right());
					delete to_be_removed;
				}
			}
			else
			{
				if (bal > 0)
				{
					if (to_be_removed->Left()->Right() == 0)
					{
						replacement = to_be_removed->Left();
						replacement->SetRight(to_be_removed->Right());

						temp_Node = replacement;


					}
					else
					{
						replacement = to_be_removed->Left()->Right();
						while (replacement->Right() != 0)
						{
							replacement = replacement->Right();
						}
						replacement_parent = replacement->Parent();
						replacement_parent->SetRight(replacement->Left());

						temp_Node = replacement_parent;

						replacement->SetLeft(to_be_removed->Left());
						replacement->SetRight(to_be_removed->Right());
					}
				}
				else
				{
					if (to_be_removed->Right()->Left() == 0)
					{
						replacement = to_be_removed->Right();
						replacement->SetLeft(to_be_removed->Left());

						temp_Node = replacement;


					}
					else
					{
						replacement = to_be_removed->Right()->Left();
						while (replacement->Left())
						{
							replacement = replacement->Left();
						}
						replacement_parent = replacement->Parent();
						replacement_parent->SetLeft(replacement->Right());

						temp_Node = replacement_parent;

						replacement->SetLeft(to_be_removed->Left());
						replacement->SetRight(to_be_removed->Right());
					}
				}
				if (p != 0)
				{
					if (side == left) p->SetLeft(replacement);
					else p->SetRight(replacement);

					delete to_be_removed;
				}
				else
				{
					setRoot(replacement);
					delete to_be_removed;
				}

				balanceAt(temp_Node);

			}
			count--;
			height = Height();
			return true;
		}

		size_t Height(){
			return Root->Height();
		}

		size_t Count(){
			return this->count;
		}
	};
}

