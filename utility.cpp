/*
 * utility.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */
#include "utility.h"
#include <iostream>
#include <vector>
#include "token.h"
#include "expression.h"

using namespace std;

ostream & operator << (ostream & out, const vector<Token> & t) // Operator overloaded function to print out the tokenized vector
{
	for(unsigned int i = 0; i < t.size(); i++)
	{
		if(t[i].get_type() == 0)
		{
			out << "Type = identifier, ";
		}
		else if(t[i].get_type() == 1)
		{
			out << "Type = integer, ";
		}
		else if(t[i].get_type() == 2)
		{
			out << "Type = operator, ";
		}
		else if(t[i].get_type() == 3)
		{
			out << "Type = equal, ";
		}
		else if(t[i].get_type() == 4)
		{
			out << "Type = openbrace, ";
		}
		else if(t[i].get_type() == 5)
		{
			out << "Type = closebrace, ";
		}
		else if(t[i].get_type() == 6)
		{
			out << "Type = invalid, ";
		}
		out << "Token: " << t[i].get_token() << " ";
		if(i != t.size() - 1) // Makes sure there isn't an extra line space at the end of the print statement
		{
			cout << endl;
		}
	}
	return out;
}
