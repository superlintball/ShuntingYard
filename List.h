#ifndef LISTH
#define LISTH

#include "Token.h"

using namespace std;

//define list class
class List
{
	public:
		List(Token* newToken) {token = newToken;}
		Token* getToken() {return token;}
		void setPrev(List* node) {previous = node;}
		void setNext(List* node) {next = node;}
		List* getPrev() {return previous;}
		List* getNext() {return next;}
	private:
		Token* token;
		List* previous;
		List* next;
};
#endif
