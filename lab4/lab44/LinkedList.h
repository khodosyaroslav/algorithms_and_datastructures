#pragma once

#include "Node.h"

class LinkedList
{
private:
	Node* head;

public:
	LinkedList();
	void insert_head(int data);
	void insert_head(Node* head_new);
	void insert_after(int n, int data);
	void move_element_n_positions(int j, int n);
	void delete_by_index(int index);
	void delete_each_by_n(int n);
	LinkedList* sort();
	LinkedList* copy();
	void clear_list();
	void swap_nodes(int data1, int data2);
	void reverse_list();
	bool contains_element(int data);
	void insert(int data);
	void print();
	Node* get_head();
	~LinkedList();
};