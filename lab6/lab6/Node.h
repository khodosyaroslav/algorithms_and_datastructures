#pragma once

struct Node
{
	int key;
	int value;
	Node* next;

	Node();
	Node(int key_, int value_);
};