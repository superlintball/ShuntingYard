#include "Token.h"

//if the token is an operator or parenthesis
void Token::setChar(char newToken)
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

//if the token is a number
void Token::setNum(int newNumber)
{
	//all numbers are type 0
	type = 0;
	number = newNumber;
}
