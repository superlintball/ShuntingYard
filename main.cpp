#include <iostream>
#include "Token.h"
#include "Tree.h"
#include <cstring>
#include <stdlib.h>

using namespace std;

//associativity constants
const int NONE = 0;
const int LEFT = 1;
const int RIGHT = 2;

//type constants
const int NUM = 0; //number
const int OP = 1; //operator
const int PAR = 2; //parenthesis

Node* recursiveEnd(Node* head);
Node* push(Node* &head, Token* toAdd);

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
	Node* test = expHead;
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
		test = test->getRight();
	}

	Node* current = expHead;
	Node* fixHead = NULL;
	Node* stackHead = NULL;
	while(current != NULL)
	{
		if(current->getToken()->getType() == NUM)
		{
cout << "started number " << current->getToken()->getNumber() << endl;
			push(fixHead, current->getToken());
cout << "number success" << endl;
		}
		else if(current->getToken()->getType() == PAR)
		{
cout << "started parenthesis " <<  current->getToken()->getChar() << endl;
					cout << "The end of the stack is " << recursiveEnd(stackHead)->getToken()->getChar() << endl;

			if(current->getToken()->getChar() == '(')
			{
				push(stackHead, current->getToken());
			}
			else
			{
				while(recursiveEnd(stackHead)->getToken()->getType() != PAR)
				{
					push(fixHead, recursiveEnd(stackHead)->getToken());
					Node* end = recursiveEnd(stackHead);
					end->getLeft()->setRight(NULL);
					delete end;
				}
				delete recursiveEnd(stackHead)->getToken();
				Node* end = recursiveEnd(stackHead);
				end->getLeft()->setRight(NULL);
				delete end;
			}
					cout << "The end of the stack is " << recursiveEnd(stackHead)->getToken()->getChar() << endl;
cout << "parenthesis success" << endl;
		}
		else
		{
cout << "started operator " <<  current->getToken()->getChar() << endl;
			if(stackHead != NULL)
			{
			cout << "stack head isn't null!" << endl;
				while(((recursiveEnd(stackHead)->getToken()->getPrec() >
					current->getToken()->getPrec()) ||
					(recursiveEnd(stackHead)->getToken()->getPrec() ==
					current->getToken()->getPrec() &&
					recursiveEnd(stackHead)->getToken()->getAssoc() == LEFT)) &&
					(recursiveEnd(stackHead)->getToken()->getChar() != '('))
				{
					cout << "The end of the stack is " << recursiveEnd(stackHead)->getToken()->getChar() << endl;
					push(fixHead, recursiveEnd(stackHead)->getToken());
					Node* end = recursiveEnd(stackHead);
					end->getLeft()->setRight(NULL);
					delete end;
	cout << "The end of the stack is " << recursiveEnd(stackHead)->getToken()->getChar() << endl;

				}
				cout << "I made it out alive" << endl;
			}
			push(stackHead, current->getToken());
cout << "operator success" << endl;
		}
		Node* prev = current;
		current = current->getRight();
		delete prev;
	}
	while(stackHead != NULL)
	{
		push(fixHead, recursiveEnd(stackHead)->getToken());
		Node* end = recursiveEnd(stackHead);
		if(end->getLeft() != NULL)
		{
			end->getLeft()->setRight(NULL);
			delete end;
		}
		else
		{
			break;
		}
	}

	current = fixHead;
	while(current != NULL)
	{
		if(current->getToken()->getType() == NUM)
		{
			cout << current->getToken()->getNumber() << endl;
		}
		else
		{
			cout << current->getToken()->getChar() << endl;
		}
		current = current->getRight();
	}
	return 0;
}

//find the last node in a list recursively
Node* recursiveEnd(Node* head)
{
	if(head->getRight() != NULL)
	{
		return recursiveEnd(head->getRight());
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
		head->setRight(NULL);
		head->setLeft(NULL);
	}
	//otherwise add it to the end
	else
	{
		Node* end = recursiveEnd(head);
		end->setRight(node);
		node->setRight(NULL);
		node->setLeft(end);
	}
	return head;
}

