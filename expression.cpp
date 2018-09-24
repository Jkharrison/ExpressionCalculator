	/*
 * expression.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */

#include "expression.h"
#include <iostream>
#include <string>
#include <vector>
#include "utility.h"
#include "token.h"
#include <stack>

using namespace std;

Expression::Expression() // Default Constructor and the default attribute values
{
	original = "";
	valid  = false;
	type = illegal;
}

Expression::Expression(const string & s)
{
	//Two types of expression, those with spaces and those without
	set(s);


	// Takes in a string and treats it as an expression. It tokenizes the input
	// string and sets the original and tokenized members accordingly. Algorithm to tokenize
	// String that contains spaces

}

void Expression::set(const string & s)
{
		// Similar to the method above, follows same algorithm
		original = s;
		type = illegal;
		valid = false;

		string str;
		string str2;
		for(unsigned int i = 0; i < s.size(); i++)
		{
			if(s[i] != ' ')
			{
				str2.push_back(s[i]); // Gets rid of spaces in
			}
		}
		for(unsigned int i = 0; i < str2.size(); i++)
		{
			if(str2[i] == '+' || str2[i] == '%' || str2[i] == '*' || str2[i] == '-' || str2[i] == '/' || str2[i] == '=' || str2[i] == '(' || str2[i] == ')')
			// Check for special characters
			{
				str.push_back(' ');
				str.push_back(str2[i]);
				str.push_back(' ');
			}
			else
			{
				if(str2[i] != ' ')
				{
					str.push_back(str2[i]); // Adds characters that are not special delimiters or spaces
				}
			}
		}
		vector<string> tokens; // Creates an empty vector
		string tok; // Creates an empty string
		unsigned int index = 0; // Creates an index to iterate from
		for (unsigned int i = 0; i < str.size(); i++)
		{

			if(str[i] == ' ')
			{

				for(unsigned int j = index; j < i; j++)
				{
					if(str[j] != ' ')
					{
						tok.push_back(str[j]); // Loop to push characters into token string
					}
				}
				index = i + 1; // Keeps track of index after space is found
				tokens.push_back(tok); // Pushes string onto string vector
				tok.clear(); // Clears the string to empty
			}

		}
		while(index < str.size())
		{
			tok.push_back(str[index]); // Adds the remaining characters into a string after all spaces have been found
			index++;
		}
		tokens.push_back(tok); //pushing the token string onto the tokens vector

	for (unsigned int i = 0; i < tokens.size(); i++)
	{
		//cout << "These are the tokens: " << tokens[i] << endl;
		Token push(tokens[i]); // Create a single token from the tokens vector and push it onto the private member token vector
		if(push.get_type() != invalid)
		{
			tokenized.push_back(push); // The pushing
		}
	}
	isValid(); // Method to check the validity of the Expression
	if(valid == true)
	{
		postfixCreate(); // Method to create the post fix for the expression
	}

}

void Expression::display() const
{
	cout << "Original: " << original << endl;
	cout << "Tokenized: " << endl << tokenized << endl;
	 // Need to write an operator overloaded function to use << because it is of type token
	cout << "Postfix: ";
	printPostFix();

	cout << "Type: ";
	if(type == 0)
	{
		cout <<"assignment" << endl;
	}
	if(type == 1)
	{
		cout <<"arithmetic" << endl;
	}
	if(type == 2)
	{
		cout << "illegal" << endl;
	}
	cout << "Valid: " << valid << endl;
}

string Expression::get_original() const
{
	return original; // Getter for original member
}

vector<Token> Expression::get_tokenized() const
{
	return tokenized; // Getter for tokenized member
}

bool Expression::get_valid() const
{
	return valid; // Getter for valid member
}

void Expression::isValid()
{
	// TODO: finish later, reference pseudo code, from lecture notes.
	States state = operand;
	valid = true; // Initialize valid to true
	bool eqtrue = false;
	int braceCount = 0;
	vector<Token> v = tokenized;
	int i = 0;
	int size = v.size();
	while(state != done && i < size)
	{
		if(state == operand) // State where the current token should be an integer or identifier or a brace (open/close)
		{
			if(v[i].get_type() == openbrace)
			{
				braceCount++; // Increment the brace count by one. once one is found
			}
			else if(v[i].get_type() == integer || v[i].get_type() == identifier)
			{
				state = func;
			}
			else
			{
				valid = false;
				state = done;
			}
		}
		else if(state == func) // State where the current token should be an operator or a brace(open/close)
		{
			if(v[i].get_type() == closebrace)
			{
				braceCount--;
				if(braceCount < 0)
				{
					valid = false;
					state = done;
				}
			}
			else if(v[i].get_type() == equals) // State is assignment.
			{
				eqtrue = true;
				state = operand;
			}
			else if(v[i].get_type() == operators)
			{
				state = operand;
			}
			else
			{
				valid = false;
				state = done;
			}
		}
			
	i++;
}
	if(braceCount != 0)
	{
		valid = false;
	}
	if(state == operand)
	{
		valid = false;
	}
	if(valid)
	{
		if(eqtrue)
		{
			if(v.size() == 3 && v[0].get_type() == identifier && v[2].get_type() == integer)
			{
				type = assignment;

					//TODO: Add a hash table or some other data structure to store the values of the assignment.
			}
			else
			{
				valid = false;
			}
		}
		else
		{
			type = arithmetic;
			// may obtain postfix here, or is the set method after check
		}
	}
}



void Expression::postfixCreate()
{
	vector<Token> temp;
	stack <Token> s;
	vector<Token> current = tokenized;
	int i = 0;
	int size = tokenized.size();
	while(i < size)
	{
		if(tokenized[i].get_type() == integer || tokenized[i].get_type() == identifier) // Case where the index is an integer or identifier like a, or 2.
		{
			temp.push_back(tokenized[i]);
		}
		if(tokenized[i].get_type() == operators || tokenized[i].get_type() == openbrace || tokenized[i].get_type() == closebrace)
		{
			if(s.empty())
			{
				s.push(tokenized[i]);
			}
			else
			{
				if(tokenized[i].get_priority() <= s.top().get_priority()) // Case for instance, * then  +
				{

					while(!s.empty() && (s.top().get_priority() >= tokenized[i].get_priority())) // Terminating conditions to make sure the only operators popped off are the ones that are less than or equal to the specific token
					{
						if(s.top().get_type() != openbrace  && s.top().get_type() != closebrace)
						{
							temp.push_back(s.top()); // Make sure the vector doesn't have any braces on top of it
						}
						s.pop();
					}
					s.push(tokenized[i]);
				}
				else // Case when you have a + *, where the priority is greater, tokenized priority > s.top priority
				{
					s.push(tokenized[i]); // Pushes the operator onto the stack
				}
			}
		}

		i++;
	}

	while(!s.empty())
	{
		if(s.top().get_type() != openbrace  && s.top().get_type() != closebrace)
		{
			temp.push_back(s.top()); // Pushes everything off the stack at the end
		}
		s.pop(); // This pops off the elements off the stack
	}

	postfix = temp; // Assigns the post fix vector to the one created by the algorithm above
}

vector<Token> Expression::get_postfix() const
{
	return postfix; // Getter for the post fix vector of tokens
}

Exp_type Expression::get_type() const
{
	return type; // Getter for the type member variable
}

void Expression::printPostFix() const
{
	string str = ""; // Generate an empty string
	vector<Token> v = this->get_postfix();
	for(unsigned int i = 0; i < v.size(); i++)
	{
		string pusher = v[i].get_token();
		str.push_back(' ');
		str.append(pusher);
	}
	cout << str << endl;
}



