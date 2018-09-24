/*
 * expression.h
 *
 *  Created on: Sep 25, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
#include <vector>
#include "token.h"
#include "utility.h"

enum Exp_type {assignment, arithmetic, illegal};
enum States {operand, func, done};


class Expression
{
public:
	Expression(); // Default constructor
	Expression(const string & s); // Constructor with string as one parameter
	void set(const string & s); // Takes the string and uses it as expression
	void display() const; // Used for debugging use
	void postfixCreate(); // Generates the post fix notation for each expression
	void printPostFix() const;
	string get_original()const; // Getter for original member
	vector<Token> get_tokenized() const; // Getter method for token vector of the expression
	vector<Token> get_postfix() const;
	Exp_type get_type() const; // Returns the type of expression
	bool get_valid() const; // Returns if the expression is valid or not
	void isValid(); // Changes the validity value of the value
private:
	string original; // Original string used to construct Expression
	vector<Token> tokenized; // Tokens in expression
	vector<Token> postfix; // Implement a method to change infix to postfix, given in lecture
	bool valid; // Get from syntax checking function, (AD hoc)
	Exp_type type;
};

#endif /* EXPRESSION_H_ */
