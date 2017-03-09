using namespace std;


#include "Node.h"
#include <iostream>

Node::Node(char val){
	this->val = val;
	next = NULL;
};

Node* Node::getNext(){
	return next;
};

char Node::getVal(){
	return val;
};

void Node::setNext(Node* node){
	next = node;
};