#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
	head = NULL;
}

void LinkedList::insert_head(int data)
{
	Node* new_node = new Node(data);
	new_node->next = head;
	head = new_node;
}

void LinkedList::insert_head(Node* head_new)
{
	Node* tmp = head;
	head = head_new;
	delete tmp;
}

void LinkedList::insert_after(int n, int data)
{
	if (n >= 0)
	{
		Node* prev = NULL;
		Node* curr = head;
		Node* new_node = new Node(data);

		for (int i = 0; i <= n; i++)
		{
			if (curr != NULL)
			{
				prev = curr;
				curr = curr->next;
			}
			else
			{
				cout << "Incorrect n";
				return;
			}
		}
		prev->next = new_node;
		new_node->next = curr;
	}
}

void LinkedList::move_element_n_positions(int j, int n)
{
	if (j >= 0 && n > 0)
	{
		Node* prev = NULL;
		Node* curr = head;
		Node* curr_n = head;

		for (int i = 0; i < j; i++)
		{
			if (curr != NULL)
			{
				prev = curr;
				curr = curr->next;
			}
			else
			{
				cout << "Incorrect index";
				return;
			}
		}
		if (curr == NULL)
		{
			cout << "Incorrect index";
			return;
		}

		for (int i = 0; i < j + n; i++)
		{
			if (curr_n != NULL)
			{
				curr_n = curr_n->next;
			}
			else
			{
				cout << "Incorrect n";
				return;
			}
		}

		if (prev == NULL)
			head = curr->next;
		else
			prev->next = curr->next;

		if (curr_n != NULL)
		{
			curr->next = curr_n->next;
			curr_n->next = curr;
		}
		else
			cout << "Incorrect n";
	}
}

void LinkedList::delete_by_index(int index)
{
	if (head == NULL)
		return;

	Node* curr = head;

	if (index == 0)
	{
		head = curr->next;
		delete curr;
		return;
	}

	for (int i = 0; i < index - 1; i++)
		curr = curr->next;

	if (curr == NULL || curr->next == NULL)
		return;

	Node* next = curr->next->next;
	delete curr->next;
	curr->next = next;
}

void LinkedList::delete_each_by_n(int n)
{
	int counter = 1;
	int counter_index_changed = 0;
	Node* curr = head;

	while (curr != NULL)
	{
		Node* next_node = curr->next;
		if (counter % n == 0)
		{
			delete_by_index(counter - counter_index_changed - 1);
			counter_index_changed++;
		}

		counter++;
		curr = next_node;
	}
}

LinkedList* LinkedList::sort()
{
	LinkedList* list_new = copy();
	Node* curr = list_new->get_head();
	Node* index = NULL;
	int tmp = 0;

	while (curr != NULL)
	{
		index = curr->next;
		while (index != NULL)
		{
			if (curr->data > index->data)
			{
				list_new->swap_nodes(curr->data, index->data);
				swap(index, curr);
			}

			index = index->next;
		}
		curr = curr->next;
	}

	return list_new;
}

LinkedList* LinkedList::copy()
{
	Node* curr = head;
	LinkedList* list_copy = new LinkedList();

	while (curr != NULL)
	{
		list_copy->insert(curr->data);
		curr = curr->next;
	}

	return list_copy;
}

void LinkedList::clear_list()
{
	Node* curr = head;
	Node* next = NULL;

	while (curr != NULL)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}

	head = NULL;
}

void LinkedList::swap_nodes(int data1, int data2)
{
	Node* prev1 = NULL; Node* curr1 = head;
	Node* prev2 = NULL; Node* curr2 = head;

	if (data1 == data2)
		return;

	while (curr1 != NULL && curr1->data != data1)
	{
		prev1 = curr1;
		curr1 = curr1->next;
	}

	while (curr2 != NULL && curr2->data != data2)
	{
		prev2 = curr2;
		curr2 = curr2->next;
	}

	if (curr1 == NULL || curr2 == NULL)
		return;

	if (prev1 == NULL)
		head = curr2;
	else
		prev1->next = curr2;

	if (prev2 == NULL)
		head = curr1;
	else
		prev2->next = curr1;

	swap(curr1->next, curr2->next);
}

void LinkedList::reverse_list()
{
	Node* curr = head;
	Node* prev = NULL;

	while (curr != NULL)
	{
		Node* next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	head = prev;
}

bool LinkedList::contains_element(int data)
{
	Node* curr = head;

	while (curr != NULL)
	{
		if (curr->data == data)
			return true;

		curr = curr->next;
	}

	return false;
}

void LinkedList::insert(int data)
{
	Node* new_node = new Node(data);
	new_node->next = NULL;

	if (head == NULL)
	{
		head = new_node;
	}
	else
	{
		Node* current = head;

		while (current->next != NULL)
			current = current->next;

		current->next = new_node;
	}
}

void LinkedList::print()
{
	Node* curr = head;

	if (curr == NULL)
	{
		cout << "empty";
		return;
	}

	while (curr != NULL)
	{
		cout << curr->data << " ";
		curr = curr->next;
	}
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