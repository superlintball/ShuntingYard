#ifndef TOKENH
#define TOKENH

#include <iostream>
#include <ctype.h>

using namespace std;

class Token
{
	public:
		//token constructor; defines properties for each type of operator
		Token(char newToken)
		{
			token = newToken;

			//all numbers are type 0
			if(isdigit(token))
			{
				type = 0;
			}
			
			//all operators are type 1
			else if(token == '+' || token == '-')
			{
				precedence = 1;
				associativity = 1;
				type = 1;
			} else if(token == '*' || token == '/')
			{
				precedence = 2;
				associativity = 1;
				type = 1;
			} else if(token == '^')
			{
				precedence = 3;
				associativity = 2;
				type = 1;
			}
			
			//parentheses are type 2
			else if(token == '(' || token == ')')
			{
				type = 2;
			}
		}
		char getToken() {return token;}
		int getPrec() {return precedence;}
		int getAssoc() {return associativity;}
		int getType() {return type;}
	private:
		char token;

		//numbers and parentheses don't have precedence or associativity, so default to 0
		int precedence = 0;
		int associativity = 0;

		int type;
};

#endif
