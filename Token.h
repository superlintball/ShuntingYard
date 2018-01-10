#ifndef TOKENH
#define TOKENH

#include <iostream>

using namespace std;

class Token
{
	public:
		Token(char newToken)
		{
			token = newToken;
			if(token == '+' || token == '-')
			{
				precedence = 1;
				associativity = LEFT;
			} else if(token == 'x' || token == '/')
			{
				precedence = 2;
				associativity = LEFT;
			} else if(token == '^')
			{
				precedence = 3;
				associativity = RIGHT;
			}
		}
		char getToken() {return token;}
		int getPrec() {return precedence;}
		int getAssoc() {return associativity;}
	private:
		char token;
		int precedence;
		int associativity;
};

#endif
