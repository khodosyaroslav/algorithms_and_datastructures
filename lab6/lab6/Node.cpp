#include<iostream>
#include "Node.h"

Node::Node()
{
	key = NULL;
	value = NULL;
	next = NULL;
}

Node::Node(int key_, int value_)
{
	key = key_;
	value = value_;
	next = NULL;
}