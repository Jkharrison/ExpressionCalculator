/*
 * main.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: Jasper Harrison
 *      Assignment: Homework 5
 */


#include <iostream>
#include "expression.h"
#include "token.h"
#include "utility.h"
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

//The two global vectors to store the identifiers values within them. TODO: Implement evaluation for the identifiers as well.
vector<string> Identifiers;
vector<int> values;


struct node // Class used for constructor expression tree for evaluation function.
{
public:
	string value;
	// Initial conditions of an empty tree
	node * left;
	node * right;
	void Children(node * l, node * r) // Helper method to assign the left and right children in one step.
	{
		this->left = l;
		this->right = r;
	}
};

//Global variables needed for the expression tree, necessary for my expression tree implementation.
int top = -1;
node * data[100];


//Function Prototypes
void input(vector<Expression> &v); // Input function to allow the user to input an expression or string of expressions.
void printExpressions(vector<Expression> v); // Function to print the expressions
void action(vector<Expression> &v); // Action function to allow the user to chose what they would like to do next.
bool findSemiEnd(string str); // Function to find if the expression or string of expression has a semi colon at the right positions.
void evaluate(vector<Expression> &v); // Evaluate each of the known expressions in memory
void clear(vector<Expression> & v); // Clear all previous inputs of expressions
void convert(vector <Expression> &v); // Method to parenthesize the expressions
void postFix(vector <Expression> &v); // Method to produce the postfix of each expression
void preFix(vector<Expression> &v); // Method to produce the prefix of each expression
void quit();
node * createExpressionTree(vector<Token> v); // Takes in a string of the postfix of the expression.
int eval(node * root); // Function to evaluate the expression tree
void push(node * tree);
node * pop();
void inOrder(node * tree);

void inOrder(node * tree)
{
	//cout << tree->value << endl;
	if(tree != NULL)
	{
		//cout << "(";
		inOrder(tree->left);
		inOrder(tree->right);
		cout << tree->value;
		//cout << ")";
	}
}

int eval(node * root) // This expression tree functions perfectly.
{
	if(root == NULL)
	{
		return 0;
	}
	if(root-> left == NULL && root-> right == NULL)
	{
		return stoi(root->value); // Returns the integer value of the string
	}
	// left and right values from the leaves of the tree recursively as you go up.
	int l_val = eval(root-> left);
	int r_val = eval(root -> right);

	//Checking for operator to apply
	if(root-> value == "+")
	{
		return l_val + r_val;
	}
	if(root-> value == "-")
	{
			return l_val - r_val;
	}
	if(root-> value == "*")
		{
			return l_val * r_val;
		}
	if(root-> value == "/")
		{
			return l_val / r_val;
		}
	else // Used else because modulation is the last operation not above
	{
		return l_val % r_val;
	}
}



void input(vector<Expression> &v) // Function that takes in the user string input
{
	string Expression_input = ""; // Create an empty string
	cout << "input: " << endl;
	getline(cin, Expression_input);
	//cout << "The size of the string is: " << Expression_input.size() << endl;
	//cout << "The contents of the expression input are: " << Expression_input << endl;
	unsigned int index = 0;
	int start = 0;
	bool contains = findSemiEnd(Expression_input);
	if(contains) // TODO: Re-do this logic later, for the case where the string has some semi-colons but also missing some
	{
		while(index < Expression_input.size()) // Loop to look for semi colons
		{
			if(Expression_input[index] == ';') // Looking for semi colon, case where there is a semi colon in the string
			{
				string pusher;
				int j = index;
				for(int i = start; i < j; i++)
				{
					pusher.push_back(Expression_input[i]); // Push characters onto the string
				}
				Expression pusher_E; // Pushes each string into an Expression object
				pusher_E.set(pusher);
				v.push_back(pusher_E); // pushes each expression onto the expression vector
				pusher.clear();
				start = index + 1;
			}
			index++;
		}
	}
	else
	{
		Expression pusher_E;
		pusher_E.set(Expression_input);
		v.push_back(pusher_E);
	}

	cout << "The size of the expression vector is: " << v.size() << endl; // used for error checking in seeing how many expressions have been pushed on to the expression vector
	for(unsigned int i = 0; i < v.size(); i++)
	{
		if(v[i].get_type() == assignment)
		{
			vector<Token> vec = v[i].get_tokenized(); // gets the token vector
			string str = vec[0].get_token();
			Identifiers.push_back(str);
			string data = vec[2].get_token();
			int value = stoi(data);
			cout << value << endl;
			values.push_back(value);
			vec[0].defined = true;
		}
	}
	action(v);

}

void action(vector<Expression> &v) // Action function for the user input for the action to be performed
{
	cout << "action: " << endl;
	string str = ""; // Initialize the action variable to the NULL character
	getline(cin, str);
	str[0] = toupper(str[0]);
	while(str.size() != 1 && str[0] != 'C' && str[0] != 'Q' && str[0] != 'S' && str[0] != '=' && str[0] != '<' && str[0] != '>' && str[0] != 'F')
	{
		cout << "Wrong input for the action! Please type one of =, <, >, f(F), q(Q), c(C), s(S)" << endl;
		getline(cin, str);
		str[0] = toupper(str[0]); // Make sure captilization is always right.

	}
	//cout << "The action contents are: " << str << endl; // Just a cout statement to check for the overlap

	char action = str[0];
	
	//TODO: Fix the semi colon checking algorithm, ask about this to Dr. Li
	for(unsigned int i = 0; i < v.size(); i++)
	{
		string common = v[i].get_original();
		//cout << common << endl; helpful cout statement that I will come back to soon.

		bool found = findSemiEnd(common);
		if(!found)
		{
			// This is where the missing ; colon statement should go.
		}
	}
	
	switch(action)
	{
	case 'C':
		input(v);
		break;
	case 'S':
		clear(v);
		break;
	case 'F':
		convert(v);
		break;
	case '=':
		evaluate(v);
		break;
	case '<':
		postFix(v);
		break;
	case '>':
		preFix(v);
		break;
	case 'Q':
		quit();
		break;
	}

}

void printExpressions(vector<Expression> v) // Printer function to print the contents of the expressions.
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		cout << v[i].get_original() << endl;
	}
}

bool findSemiEnd(string str) // Boolean function to check for semi-colons
{
	int x = str.size() - 1; // This the last index of the expression
	if(str[x] != ';')
	{
		return false;
	}
	else
	{
		return true; // Returns true if there is a semi colon at least at the end of the function.
	}
}



void clear(vector<Expression> &v)
{
	v.clear();
	input(v);
}


void evaluate(vector<Expression> &v)
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		if(v[i].get_type() == illegal)
		{
			cout << "cannot evaluate " << v[i].get_original() << " which is an invalid expression" << endl;

		}
		else if(v[i].get_type() == arithmetic)
		{

			int evaluator = 0;
			// Implement binary expression tree, to evaluate the expression in inorder traversal.
			//Push operands on a stack as leaf nodes, not bound to any tree in any direction
			/*For operators, pop the necessary operands off the stack, create a node with operator
			  at the top, and the operands hanging below it, push the new node onto the stack
			*/
			vector<Token> vec = v[i].get_tokenized(); // Gives the token vector
			bool containID = false;
			bool isDefined = false;
			Token original;
			Token tok;
			int pos;
			for(unsigned int k = 0; k < vec.size(); k++) // Loops through each expression looking for identifiers.
			{
				if(vec[k].get_type() == identifier)
				{
					original = vec[k]; // Keeps the original value of the token in token vector
					pos = k;
					containID = true; // Changes boolean variable to true if there is.
					string variable = vec[k].get_token();
					int position;
					for(unsigned int j = 0; j < Identifiers.size(); j++)
					{
						if(variable == Identifiers[j])
						{
							isDefined = true;
							position = j;
						}
					}
					if(isDefined) // boolean to confirm if the identifier is in the vector.
					{
						cout << "Runs this too" << endl;
						//assign this token to the integer value from the vector values.
						string str = to_string(values[position]);
						 tok.set(str);
						cout << tok.get_token() << endl;
						v[i].get_tokenized()[pos] = tok;
						//vec[i] = tok; // Replaces the
					}
				}
			}
			if(containID)
			{
				cout << "running this" << endl;
				const string str2 = tok.get_token();
				cout << str2 << endl;
				v[i].get_tokenized()[pos].set(str2);
				cout << v[i].get_tokenized();
			}
			if(!containID) // Runs this when there are no identifiers in the expression.
			{
				node* tree = createExpressionTree(v[i].get_postfix());
				evaluator = eval(tree);
				cout << v[i].get_original() << " = " << evaluator << endl;
			}
		}
		else
		{
			cout << "cannot evaluate " << v[i].get_original() << " which is not an arithmetic expression but assignment" << endl;
			/* Part where the identifier evaluation failed with my logic.
			vector<Token> vec = v[i].get_tokenized(); // gets the token vector
			string str = vec[0].get_token();
			Identifiers.push_back(str);
			string data = vec[2].get_token();
			int value = stoi(data);
			cout << value << endl;
			values.push_back(value);
			vec[0].defined = true;
			*/
		}
	}
	action(v);
}

void convert(vector<Expression> &v)
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		if(v[i].get_type() == arithmetic)
		{
			string str; // String that will print out the prefix.
			stack<string> s; // Stack that will push and pop tokens off
			vector<Token> vec = v[i].get_postfix(); // Retrieves the token vector from each expression in the expression vector4
			for(unsigned int j = 0; j < vec.size(); j++)
			{
				if(vec[j].get_type() == integer || vec[j].get_type() == identifier)
				{
					s.push(vec[j].get_token()); // Pushes the integer/identifier onto the stack
				}
				else if(vec[j].get_type() == operators)
				{
					if(s.size() >= 2)
					{
						str.push_back('('); // Initially push back the open brace
						string op2 = s.top(); // assign the right hand side of the operator to the top of the stack
						s.pop(); // Pop that token off the stack to acquire the left hand side operand
						string op1 = s.top(); // assign the left hand side of the operator to the top of the stack
						str.append(op1); // Append the left hand side operand
						str.append(vec[j].get_token()); // append the operator
						str.append(op2); // Append the right hand side of the operator
						s.pop();
						str.push_back(')'); // At the very end push the close brace onto the string
						s.push(str);
						str.clear();
						//op2.clear();
						//op1.clear();
					}

				}
			}
			cout << "The parenthesize version of the " << v[i].get_original() <<" is: " << s.top() << endl;
			str.clear(); // Clear the string after using it.
			while(!s.empty())
			{
				s.pop(); // Clears the stack of all elements at the end
			}
		}
		else if(v[i].get_type() == assignment)
		{
			cout << "no fully parenthesizing of " << v[i].get_original() << " which is not arithmetic but assignment" << endl;
		}
		else if(v[i].get_type() == illegal)
		{
			cout << "no fully parenthesizing of " << v[i].get_original() << " which is an invalid expression" << endl;
		}
	}
	action(v);
}

void postFix(vector<Expression> &v)
{

	for(unsigned int i = 0; i < v.size(); i++)
	{
		if(v[i].get_type() == assignment)
		{
			cout << "no postfix of " << v[i].get_original() << " which is not  an arithmetic expression but assignment" << endl;
		}
		else if(v[i].get_type() == illegal)
		{
			cout <<"no postfix of " << v[i].get_original() << " which is invalid expression" << endl;
		}
		else
		{
			cout << "postfix of " << v[i].get_original() << " is: ";
			v[i].printPostFix();
		}

	}
	action(v);
}
void preFix(vector<Expression> &v) //TODO: Write the algorithm to create the pre fix of a function.
{

	for(unsigned int i = 0; i < v.size(); i++)
	{
		if(v[i].get_type() == assignment)
		{
			cout << "no prefix of " << v[i].get_original() << " which is not  an arithmetic expression but assignment" << endl;
		}
		else if(v[i].get_type() == illegal)
		{
			cout <<"no prefix of " << v[i].get_original() << " which is invalid expression" << endl;
		}
		else
		{
			//Calculate, take the two numbers off the top, add the operator at the front and push that back onto the stack.
			//pop the only element off the stack and should be prefix.
			cout << "prefix of " << v[i].get_original() << " is: ";
			stack<string> s;
			vector<Token> vec = v[i].get_postfix();
			for(unsigned int j = 0; j < vec.size(); j++)
			{
				if(vec[j].get_type() == integer || vec[j].get_type() == identifier)
				{
					s.push(vec[j].get_token());
				}
				else if(vec[j].get_type() == operators)
				{
					if(s.size() >= 2)
					{
						string op2 = s.top();
						s.pop();
						string op1 = s.top();
						s.pop();
						op2 = op1 + op2; //appends the strings together
						string str = vec[j].get_token();
						str = str + op2;
						s.push(str);
					}

				}
				else
				{

				}
			}

			string prefix = s.top();

			while(!s.empty())
			{
				s.pop();
			}
			cout << prefix << endl;
		}

	}
	action(v);
}

void quit()
{
	cout << "=== expression evaluation program ends" << endl;
	exit(0);
}

node * createExpressionTree(vector<Token> v)
{
	string symbol;
	node * op, *ptr1, *ptr2;
	for(unsigned int i = 0; i < v.size(); i++)
	{
		if(v[i].get_type() == integer || v[i].get_type() == identifier)
		{
			op = new node();
			op->value = v[i].get_token();
			op->left = NULL;
			op->right = NULL;
			push(op); // Pushes the operand onto the expression tree
			//Create a function to pop and push the elements onto the tree
		}
		else
		{
			ptr1 = pop(); // pop the rhs
			ptr2 = pop(); // pops the lhs
			op = new node();
			op->value = v[i].get_token();
			op->left = ptr2;
			op->right = ptr1;
			push(op);
		}
	}
	//cout << "Crashing here" << endl;
	// << data[top - 1]->value << endl;
	return data[top];
}

void push(node * tree) // Pushes a single node onto the tree.
{
	top++; // Increment the top of the node pointer array by 1.
	data[top] = tree; // The top of the node pointer array is the root of the tree assignemnt.
}

node * pop() // Pops a single node from the tree
{
	//Could have simply returned data[top] and then decremented top, but either works
	top--;
	return (data[top + 1]);
}


int main()
{
	vector<Expression> Expressions;
	cout << "=== expression evaluation programs starts ===" << endl; // Beginning of program
	input(Expressions);
	return 0;
}
