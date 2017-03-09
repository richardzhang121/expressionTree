//ZhangRichard P.7

/*Interface: Your program should then create an expression tree internally. 
After the translation, ask the user if they want the expression in prefix, 
infix, or postfix notation, and print out the corresponding expression.
*/

/*Implementation: Take your postfix string from Shunting Yard, 
and traverse that string to create your expression tree. 
(The root of your tree will be the rightmost operator; you probably want to 
build the tree by going from right to left in your string.)  You simply need
to trace the tree in order to output the proper translation 
(either prefix or postfix).
*/

/*Prefix traversal: Root, Prefix(left), Prefix(Right)
Infix traversal: Infix(left), Root, Infix(Right)
Postfix traversal: Postfix(left), Postfix(Right), Root
*/

#include <iostream>
#include <string.h>
#include "Node.h"
#include "Tree.h"

using namespace std;

// holds a token
struct token{
  char value[10];
};

// pushes an operator onto stack
void push(Node*& stack, char newval){
	Node* newnode = new Node(newval);
	newnode->setNext(stack);
	stack = newnode;
}
// gets value and removes operator from top of stack
char pop(Node*& stack){
	char op = stack->getVal();
	stack = stack->getNext();
	return op;
}
// gets value from top of stack
char peak(Node*& stack){
  return stack->getVal();
}
// checks if stack is empty
bool empty(Node*& stack){
	return (stack==NULL);
}
// checks if token is operator
bool isOperator (char c){
  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')'){
    return true;
  }
  return false;
}
// checks if left parenthesis
bool isLeft (char c){
  if(c == '('){
    return true;
  }
  else{
    return false;
  }
}
// checks if right parenthesis
bool isRight (char c){
  if(c == ')'){
    return true;
  }
  else{
    return false;
  }
}
// gets weight of operator (for precedence)
int getWeight (char c){
  int weight = -1;
  if (c == '+' || c == '-') {
    weight = 1;
  }
  else if (c == '*' || c == '/'){
    weight = 2;
  }
  else if (c == '^'){
    weight = 3;
  }
  return weight;
}
// checks if two operators have lower/equal/higher precednce
int precedence(char a, char b){
// -1: a<b
// 0: a=b
// 1: a>b
  int aWeight = getWeight(a);
  int bWeight = getWeight(b);
  if (aWeight < bWeight){
    return -1;
  }
  else if (aWeight == bWeight){
    return 0;
  }
  else {
    return 1;
  }
}
// checks if operator is right associative
bool isRightAsso(char c){
  return(c == '^');
}

// convert infix expression into postfix
int convert(char* infix, token* postfix){
  int numtokens = 0;
  Node* opstack = NULL;
  char top[10];
  int numchars = 0;
  for(int i = 0; infix[i]!='\0'; i++){
    // if operand, then print
    if(isdigit(infix[i])){
      top[numchars] = infix[i];
      numchars++;
    }
    // if space, end of token
    else if(infix[i] == ' '){
      // print if operand
      if(numchars>0){
        top[numchars] = '\0';
        strcpy(postfix[numtokens].value, top);
        numtokens++;
        numchars = 0;
      }
    }
    // if left, push to stack
    else if(isLeft(infix[i])){
      push(opstack, infix[i]);
    }
    // if right, discard and pop/print stack until left and discard left
    else if(isRight(infix[i])){
      while(peak(opstack)!='('){
        postfix[numtokens].value[0] = pop(opstack);
        postfix[numtokens].value[1] = '\0';
        numtokens++;
      }
      pop(opstack);
    }
    // if operator
    else if(isOperator(infix[i])){
      // if stack is empty or (, push to stack
      if(empty(opstack) || peak(opstack)=='('){
        push(opstack, infix[i]);
      }
      else{
        // pop stack until if operator has higher precedence or rightAsso, then push to stack
        while(!empty(opstack) &&
              (precedence(infix[i], peak(opstack)) < 0 ||
               precedence(infix[i], peak(opstack)) == 0 && !isRightAsso(infix[i])
              )){

          postfix[numtokens].value[0] = pop(opstack);
          postfix[numtokens].value[1] = '\0';
          numtokens++;
        }
        push(opstack, infix[i]);
      }
    }
  }
  if(numchars>0){
    top[numchars] = '\0';
    strcpy(postfix[numtokens].value, top);
    numtokens++;
  }
  // pop and print remaining operators on stack
  while(!empty(opstack)){
    postfix[numtokens].value[0] = pop(opstack);
    postfix[numtokens].value[1] = '\0';
    numtokens++;
  }
  return numtokens;
}

// creates the expression tree from the postfix expression recursively
Tree* makeTree(token* postfix, int& curr){
    Tree* newTree = new Tree(postfix[curr].value);
    curr--;
    if(isOperator(*newTree->getVal())){
      newTree->setRight(makeTree(postfix,curr));
      newTree->setLeft(makeTree(postfix,curr));
    }
    return newTree;
}

// print in prefix (root left right)
void printPre (Tree* tree){
  if(tree != NULL){
    cout<<tree->getVal()<<" ";
    printPre(tree->getLeft());
    printPre(tree->getRight());
  }
}

// print in infix (left root right)
void printIn (Tree* tree){
  if(tree != NULL){
    printIn(tree->getLeft());
    cout<<tree->getVal()<<" ";
    printIn(tree->getRight());
  }
}

// print in postfix (left right root)
void printPost (Tree* tree){
  if(tree != NULL){
    printPost(tree->getLeft());
    printPost(tree->getRight());
    cout<<tree->getVal()<<" ";
  }
}

int main(){
  char input [200];
  char infix [200];
  token postfix[200];
  cout<<"Enter your expression"<<endl;
  cin.getline(infix, 200);
  int numtokens = convert(infix,postfix);
  Tree* tree = makeTree(postfix,--numtokens);
  bool run = true;
  while(run == true){
    cout<<"Prefix(P) Infix(I) Postfix(X) Quit(Q)"<<endl;
        cin>>input;
        if(input[0] == 'P'){
          printPre(tree);
          cout<<endl;
        }
        else if(input[0] == 'I'){
          printIn(tree);
          cout<<endl;
        }
        else if(input[0] == 'X'){
          printPost(tree);
          cout<<endl;
        }
        else if(input[0] == 'Q'){
          run = false;
        }
        else{
          cout<<"Not a valid command."<<endl;
        }
    }
}