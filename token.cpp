/*
 * token.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */

#include "token.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

Token::Token()
{
	type = invalid;
	token = "";
	priority = -1;
}

Token::Token(string s)
{
	// Conditional statement to differentiate between types

	if(s.front() == '=')
	{
		type = equals;
	}
	else if((int)s.front() >= 97 && (int)s.front() <= 122) // Lowercase letters also need to check that no more letters appear after an integer appears
	{
		type = identifier;
		unsigned int i = 0;
		//int index;

		while(i < s.size()) // Check to make sure identifier has no more characters other than integers or alphabetical characters
		{
			if(!(isalnum(s[i])))
			{
				type = invalid;
			}
			i++;
		}

	}

	else if((int)s.front() >= 65 && (int)s.front() <= 90) // Uppercase letters, same as above
	{
		type = identifier;

		unsigned int i = 0;
		while(i < s.size())
				{
					if(!(isalnum(s[i])))
					{
						type = invalid;
					}
					i++;
				}
	}
	else if(s.front() == '(')
	{
		type = openbrace;
		priority = 0;
	}
	else if(s.front() == ')')
	{
		type = closebrace;
		priority = 0;
	}
	else if(s.front() == '+' || s.front() == '-' || s.front() == '*' || s.front() == '/' || s.front() == '%')
	{
		type = operators;
		if(s.front() == '+' || s.front() == '-')
		{
			priority = 1;
		}
		else if(s.front() == '*' || s.front() == '/' || s.front() == '%') // Takes care of multiply, divide, and modulo
		{
			priority = 2;
		}
	}

	else if((int)s.front() >= 49 && (int)s.front() <= 57)
	{
		type = integer;
		unsigned int i = 0;
		while(i < s.size()) // Loop to check if anything other than a digit proceeds the first integer. EX: 1?ab
		{
			if(!(isdigit(s[i])))
			{
				type = invalid;
			}
			i++;
		}

	}
	else
	{
		type = invalid;
		priority = -1;
	}
	token = s;

}

void Token::set(string s)
{

	type = invalid;  // TODO: Have to check with conditional statement
	token = s;
	priority = -1;



}

int Token::value() const // Not needed for this assignment, but will leave it anyways
{

	if(type == identifier)
	{
		return -1;
	}
	else if(type == invalid) // TODO: Email Dr. Li about types other than specified in Token_type enum
	{
		return -1;
	}
	else if(type == integer)
	{
		return stoi(token);
	}
	else
	{
		return -1;
	}
}

void Token::display() const
{

	// If statement to output the correct ostream statement associated with it's type name.
	if(type == 0)
	{
		cout << "type = identifier" << endl;
	}
	if(type == 1)
		{
			cout << "type = integer" << endl;
		}
	if(type == 2)
		{
			cout << "type = operator" << endl;
		}
	if(type == 3)
		{
			cout << "type = equals" << endl;
		}
	if(type == 4)
		{
			cout << "type = openbrace" << endl;
		}
	if(type == 5)
		{
			cout << "type = closebrace" << endl;
		}
	if(type == 6)
		{
			cout << "type = invalid" << endl;
		}

	cout << "token = " << token << endl;
	cout << "priority = " << priority << endl;
}


// The following methods below are just getters for the private members of the token class
Token_type Token::get_type() const
{
	return type;
}

string Token::get_token() const
{
	return token;
}

int Token::get_priority() const
{
	return priority;
}
