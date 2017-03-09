// Tree.h
// Tree class for creating an operator stack
class Tree{
	private:
		Tree* left;
		Tree* right;
		char val[10];
	public:
		Tree(char*);
		Tree* getLeft();
		Tree* getRight();
		char* getVal();
		void setLeft(Tree*);
		void setRight(Tree*);
};