#include <iostream>
#include "Node.h"

Node::Node(int data_)
{
	data = data_;
	next = NULL;
}

Node::Node()
{
	data = NULL;
	next = NULL;
}