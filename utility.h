/*
 * utility.h
 *
 *  Created on: Sep 25, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <vector>
#include "token.h"

using namespace std;

ostream & operator << (ostream & out, const vector<Token> & t);

#endif /* UTILITY_H_ */
