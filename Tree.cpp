#include "Tree.h"
#include <iostream>
#include <string.h>

Tree::Tree(char* val){
	strcpy(this->val,val);
	left = NULL;
	right = NULL;
};

Tree* Tree::getLeft(){
	return left;
};

Tree* Tree::getRight(){
	return right;
};

char* Tree::getVal(){
	return val;
};

void Tree::setLeft(Tree* Tree){
	left = Tree;
};

void Tree::setRight(Tree* Tree){
	right = Tree;
};