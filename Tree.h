#ifndef NODEH
#define NODEH

#include "Token.h"

using namespace std;

//define node class
class Node()
{
	public:
		Node(Token* newToken);
		void setLeft(Node* node);
		void setRight(Node* node);
		Token* getToken();
		~Node();

	private:
		Token* token;
		Node* left;
		Node* right;
};
#endif
