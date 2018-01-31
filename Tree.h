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
		Token* getToken() {return token;}
		Node* getLeft() {return left;}
		Node* getRight() {return right;}
		~Node(){token = NULL;}

	private:
		Token* token;
		Node* left;
		Node* right;
};
#endif
