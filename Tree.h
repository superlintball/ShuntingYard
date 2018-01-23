#ifndef TREEH
#define TREEH

#include "Token.h"

using namespace std;

//define tree class
class Tree()
{
	public:
		Tree(Token* newToken) {token = newToken;}
		void setLeft(Tree* node) {left = node;}
		void setRight(Tree* node) {right = node;}
		Token* getToken() {return token;}
		Tree* getLeft() {return left;}
		Tree* getRight() {return right;}
		~Tree(){token = NULL;}

	private:
		Token* token;
		Tree* left;
		Tree* right;
};
#endif
