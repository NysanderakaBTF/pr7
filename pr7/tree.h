#pragma once
#include <utility>
#include <iostream>
using namespace std;
class tree
{
protected:
	class node
	{
	public:
		node* left;
		node* right;
		pair<char, string> info;
		node(char a, string);
		~node();
	};
public:
	node* root;
	tree();
	void add_node(char ch, string s);
	void print(node* n, string  rpref = "", string cpref = "", string lpref = "");
	


};


