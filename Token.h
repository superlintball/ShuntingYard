#ifndef TOKENH
#define TOKENH

#include <iostream>
#include <ctype.h>

using namespace std;

class Token
{
	public:
		//token constructor; defines properties for each type of operator
		Token(){}
		void setChar(char newToken);
		void setNum(int newNumber);
		char getChar() {return token;}
		int getPrec() {return precedence;}
		int getAssoc() {return associativity;}
		int getType() {return type;}
		int getNumber() {return number;}
	private:
		char token;

		//numbers and parentheses don't have precedence or associativity, so default to 0
		int precedence = 0;
		int associativity = 0;
		int type;

		int number = -1;

};

#endif
