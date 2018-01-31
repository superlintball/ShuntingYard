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
		void setChar(char newToken)
		{
			token = newToken;
			//all operators are type 1
			if(token == '+' || token == '-')
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
		void setNum(int newNumber)
		{
			//all numbers are type 0
			type = 0;
			number = newNumber;
		}
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
