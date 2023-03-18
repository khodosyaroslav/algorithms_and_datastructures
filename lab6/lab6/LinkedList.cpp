#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
	head = NULL;
}

void LinkedList::insert_head(int key, int value)
{
	Node* new_node = new Node(key, value);
	new_node->next = head;
	head = new_node;
}

void LinkedList::delete_by_key(int key)
{
	if (head == NULL)
		return;

	Node* curr = head;

	if (curr->key == key)
	{
		head = curr->next;
		delete curr;
		return;
	}

	while (curr->next->key != key)
		curr = curr->next;

	if (curr == NULL || curr->next == NULL)
		return;

	Node* next = curr->next->next;
	delete curr->next;
	curr->next = next;
}

void LinkedList::find_element(int key)
{
	Node* curr = head;

	while (curr != NULL)
	{
		if (curr->key == key)
		{
			cout << "Element found (key:" << curr->key << ", val:" << curr->value << ")";
			return;
		}

		curr = curr->next;
	}

	cout << "No element with key " << key << endl;
}

bool LinkedList::contains_element(int key)
{
	Node* curr = head;

	while (curr != NULL)
	{
		if (curr->key == key)
			return true;

		curr = curr->next;
	}

	return false;
}

void LinkedList::print()
{
	Node* curr = head;

	if (curr == NULL)
	{
		cout << "NULL\n";
		return;
	}

	while (curr != NULL)
	{
		cout << "(key:" << curr->key << ", val:" << curr->value << ") -> ";
		curr = curr->next;
	}
	cout << "NULL\n";
}

Node* LinkedList::get_head()
{
	return head;
}

LinkedList::~LinkedList()
{
	Node* curr = head;
	while (curr != NULL)
	{
		Node* tmp = curr;
		curr = curr->next;
		delete tmp;
	}
}