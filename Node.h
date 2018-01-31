#ifndef NODEH
#define NODEH

#include "Token.h"

using namespace std;

//define tree class
class Node
{
	public:
		Node(Token* newToken) {token = newToken;}
		void setLeft(Node* node) {left = node;}
		void setRight(Node* node) {right = node;}
		void setPrev(Node* node) {prev = node;}
		void setNext(Node* node) {next = node;}
		Token* getToken() {return token;}
		Node* getLeft() {return left;}
		Node* getRight() {return right;}
		Node* getNext() {return next;}
		Node* getPrev() {return prev;}
		~Node(){token = NULL;}

	private:
		Token* token;
		Node* left = NULL;
		Node* right = NULL;
		Node* prev;
		Node* next;
};
#endif
