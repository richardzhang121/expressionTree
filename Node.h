#ifndef NODE_H
#define NODE_H
// the header for the node class that the stack class uses
#include <iostream>

using namespace std;

class Node{
	private:
		Node* next;
		char val;
	public:
		Node(char);
		Node* getNext();
		char getVal();
		void setNext(Node*);
};

#endif