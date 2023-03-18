#pragma once

class LinkedList
{
private:
	Node* head;
public:
	LinkedList();
	void insert_head(int key, int value);
	void delete_by_key(int key);
	void find_element(int key);
	bool contains_element(int key);
	void print();
	Node* get_head();
	~LinkedList();
};