/* 
 * Author: Raveen Karnik
 * Date: February 6, 2018
 * This program uses the shunting yard algorithm to convert an entered mathematical expression
 * from infix notation to postfix notation. It then uses the postfix notation to create a binary
 * expression tree and, from there, can output the expression in either postfix, prefix, or infix.
 */

#include <iostream>
#include "Token.h"
#include "Node.h"
#include <cstring>
#include <stdlib.h>
#include <vector>

using namespace std;

//associativity constants
const int NONE = 0;
const int LEFT = 1;
const int RIGHT = 2;

//type constants
const int NUM = 0; //number
const int OP = 1; //operator
const int PAR = 2; //parenthesis

//global tokens vector for the prefix calculation
vector<Token*> tokens;

//function prototypes
Node* recursiveEnd(Node* head);
Node* push(Node* &head, Token* toAdd);
void pop(Node* head);
void printPostfix(Node* head);
void printInfix(Node* head);
void printPrefix(Node* head);
void visualize(Node* head, int depth);

int main()
{
	//ask user for expression to be parsed
	cout << "Enter a mathematical expression in infix notation." << endl;
	char input[80];
	cin.get(input, 80);
	cin.get();

	//parse expression into a linked list
	Node* expHead = NULL;
	for(int i = 0; i < strlen(input); i++)
	{
		//as numbers can be multiple characters, they are parsed separately
		if(isdigit(input[i]))
		{
			//figure out the length the integer
			int start = i;
			int length = 1;
			while(input[i+1] != ' ' && i <strlen(input))
			{
				length++;
				i++;
			}
			
			//isolate the integer into a char pointer
			char* number = new char[length];
			for(int j = 0; j < length; j++)
			{
				number[j] = input[start+j];
			}
			number[length] = '\0';
			//convert the isolated char pointer into an integer
			int num = atoi(number);

			//create a token containing the integer and add it to the list
			Token* token = new Token();
			token->setNum(num);
			expHead = push(expHead, token);
		}
		//if the character is anything other than a space or digit, it's an operator
		else if(input[i] != ' ')
		{
			//create a token containing the operator and add it to the list
			Token* token = new Token();
			token->setChar(input[i]);
			expHead = push(expHead, token);
		}
	}
/*	Node* test = expHead;
	while(test != NULL)
	{
		if(test->getToken()->getType() == NUM)
		{
			cout << "number: " << test->getToken()->getNumber() << endl;
		}
		else if(test->getToken()->getType() == PAR)
		{
			cout << "parenthesis: " << test->getToken()->getChar() << endl;
		}
		else if(test->getToken()->getType() == OP)
		{
			cout << "operator: " << test->getToken()->getChar() << endl;
		}
		test = test->getNext();
	}
*/
	//convert the expression in infix to postfix
	Node* current = expHead;
	Node* fixHead = NULL;
	Node* stackHead = NULL;
	while(current != NULL)
	{
		//if the token is  a number, immediately add it to the postfix notation
		if(current->getToken()->getType() == NUM)
		{
			push(fixHead, current->getToken());
		}
		//if the token is a parenthesis
		else if(current->getToken()->getType() == PAR)
		{
			//push any open parenthesis onto the stack
			if(current->getToken()->getChar() == '(')
			{
				push(stackHead, current->getToken());
			}
			//if it's a close parenthesis
			else
			{
				//pop operators off the stack until an open parenthesis is reached
				while(recursiveEnd(stackHead)->getToken()->getType() != PAR)
				{
					push(fixHead, recursiveEnd(stackHead)->getToken());
					Node* end = recursiveEnd(stackHead);
					end->getPrev()->setNext(NULL);
					delete end;
				}
				delete recursiveEnd(stackHead)->getToken();
				Node* end = recursiveEnd(stackHead);
				if(end->getPrev() != NULL)
				{
					end->getPrev()->setNext(NULL);
					delete end;
				}
				else
				{
					stackHead = NULL;
				}
			}
		}
		//if the token is an operator
		else
		{
			//if there is an operator on the stack
			if(stackHead != NULL)
			{
				//pop operators off the stack depending on precedence and associativity
				while(((recursiveEnd(stackHead)->getToken()->getPrec() >
					current->getToken()->getPrec()) ||
					(recursiveEnd(stackHead)->getToken()->getPrec() ==
					current->getToken()->getPrec() &&
					recursiveEnd(stackHead)->getToken()->getAssoc() == LEFT)) &&
					(recursiveEnd(stackHead)->getToken()->getChar() != '('))
				{
					push(fixHead, recursiveEnd(stackHead)->getToken());
					Node* end = recursiveEnd(stackHead);
					if(end->getPrev() != NULL)
					{
						end->getPrev()->setNext(NULL);
						delete end;
					}
					else
					{
						stackHead = NULL;
						break;
					}
				}
			}
			push(stackHead, current->getToken());
		}
		//move on to the next node
		Node* prev = current;
		current = current->getNext();
		delete prev;
	}
	//pop the rest of the tokens off the stack until empty
	while(stackHead != NULL)
	{
		push(fixHead, recursiveEnd(stackHead)->getToken());
		Node* end = recursiveEnd(stackHead);
		if(end->getPrev() != NULL)
		{
			end->getPrev()->setNext(NULL);
			delete end;
		}
		else
		{
			stackHead = NULL;
		}
	}
	cout << endl;
	
	//put the list in an expression tree
	Node* treeTop = recursiveEnd(fixHead);
	current = fixHead;
	while(current != NULL)
	{
		if(current->getToken()->getType() == OP)
		{
			current->setLeft(current->getPrev()->getPrev());
			current->setRight(current->getPrev());
			current->setPrev(current->getLeft()->getPrev());
			if(current->getPrev() != NULL)
			{
				current->getPrev()->setNext(current);
			}
			current->getLeft()->setPrev(NULL);
			current->getLeft()->setNext(NULL);
			current->getRight()->setPrev(NULL);
			current->getRight()->setNext(NULL);
		}
		current = current->getNext();
	}
	
	//visualize function test
	//visualize(treeTop, 0);
	//cout << endl;
	
	//ask the user what they want it converted to and print out that
	cout << "Would you like the expression converted to POSTFIX, PREFIX, or INFIX?" << endl;
	char input2[10];
	cin >> input2;
	if(!strcmp(input2, "POSTFIX") || !strcmp(input2, "postfix"))
	{
		printPostfix(treeTop);
	}
	else if(!strcmp(input2, "PREFIX") || !strcmp(input2, "prefix"))
	{
		printPrefix(treeTop);
		for(int i = 1; i <= tokens.size(); i++)
		{
			if(tokens[tokens.size()-i]->getType() == NUM)
			{
				cout << tokens[tokens.size()-i]->getNumber() << " ";
			}
			else
			{
				cout << tokens[tokens.size()-i]->getChar() << " ";
			}
		}
	}
	else if(!strcmp(input2, "INFIX") || !strcmp(input2, "infix"))
	{
		printInfix(treeTop);
	}
	return 0;
}

//find the last node in a list recursively
Node* recursiveEnd(Node* head)
{
	if(head->getNext() != NULL)
	{
		return recursiveEnd(head->getNext());
	}
	else
	{
		return head;
	}
}

//push a new node to the back of a list that starts with a given token
Node* push(Node* &head, Token* toAdd)
{
	Node* node = new Node(toAdd);

	//if there is no head right now, make it the head
	if(head == NULL)
	{
		head = node;
		head->setNext(NULL);
		head->setPrev(NULL);
	}
	//otherwise add it to the end
	else
	{
		Node* end = recursiveEnd(head);
		end->setNext(node);
		node->setNext(NULL);
		node->setPrev(end);
	}
	return head;
}

//remove the last object from a linked list
void pop(Node* head)
{
	Node* end = recursiveEnd(head);
	if(end->getPrev() != NULL)
	{
		end->getPrev()->setNext(NULL);
		delete end;
	}
	else
	{
		head = NULL;
	}
}

//print postfix notation from a binary expression tree recursively
void printPostfix(Node* head)
{
	if(head->getLeft() != NULL)
	{
		printPostfix(head->getLeft());
	}
	if(head->getRight() != NULL)
	{
		printPostfix(head->getRight());
	}	
	if(head->getToken()->getType() == NUM)
	{
		cout << head->getToken()->getNumber() << " ";
	}
	else
	{
		cout << head->getToken()->getChar() << " ";
	}
}

//print infix notation from a binary expression tree recursively
void printInfix(Node* head)
{
	if(head->getLeft() != NULL)
	{
	cout << "( ";
		printInfix(head->getLeft());
	}
	if(head->getToken()->getType() == NUM)
	{
		cout << head->getToken()->getNumber() << " ";
	}
	else
	{
		cout << head->getToken()->getChar() << " ";
	}
	if(head->getRight() != NULL)
	{
		printInfix(head->getRight());
		cout << ") ";
	}
}

//create a vector to put the expression into prefix notation from a binary tree recursively
void printPrefix(Node* head)
{
	if(head->getRight() != NULL)
	{
		printPrefix(head->getRight());
	}
	if(head->getLeft() != NULL)
	{
		printPrefix(head->getLeft());
	}	
	tokens.push_back(head->getToken());
}

//print out the tree in a simple form
void visualize(Node* head, int depth)
{
	for(int i = 0; i < depth; i++)
	{
		cout << "   ";
	}
	if(head->getToken()->getType() == NUM)
	{
		cout << head->getToken()->getNumber() << endl;
	}
	else
	{
		cout << head->getToken()->getChar() << endl;
	}
	if(head->getLeft() != NULL)
	{
		visualize(head->getLeft(), depth+1);
	}
	if(head->getRight() != NULL)
	{
		visualize(head->getRight(), depth+1);
	}
}