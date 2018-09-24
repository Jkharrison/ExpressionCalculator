/*
 * token.h
 *
 *  Created on: Sep 25, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>


using namespace std;

enum Token_type {identifier, integer, operators, equals, openbrace, closebrace, invalid};

class Token
{
	public:
		Token(); // Default Constructor
		Token(string s); // Constructor with string paramters

		void set(string s); // Assigns string to token
		int value() const;
		void display() const;
		Token_type get_type() const;
		string get_token() const;
		int get_priority() const;

		bool defined = false; // Initially state the the defined member is false ine beginning.

	private:
		Token_type type;
		string token;
		int priority;
};

#endif /* TOKEN_H_ */
