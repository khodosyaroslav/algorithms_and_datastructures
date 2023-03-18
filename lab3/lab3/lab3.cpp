#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

class Stack
{
private:
	LinkedList* list;

public:
	Stack()
	{
		list = new LinkedList();
	}

	void push(int data)
	{
		list->insert_head(data);
	}

	Node* pop()
	{
		Node* head = list->get_head();
		if (head != NULL)
		{
			Node* top_element = new Node(head->data);
			list->delete_by_index(0);
			return top_element;
		}
		return NULL;
	}

	void peek()
	{
		Node* head = list->get_head();
		if (head != NULL)
			cout << "Element at top: " << head->data;
		else
			cout << "Stack is empty";
	}

	void swap_top_bottom()
	{
		Node* head = list->get_head();
		Node* curr = head;
		
		if (head != NULL)
		{
			while (curr->next != NULL)
				curr = curr->next;

			list->swap_nodes(head->data, curr->data);
		}
		else
			cout << "Stack is empty";
	}

	void reverse_stack()
	{
		list->reverse_list();
	}

	bool contains(int data)
	{
		return list->contains_element(data);
	}

	void clear_stack()
	{
		list->clear_list();
	}

	void print()
	{
		list->print();
	}

	~Stack()
	{
		delete list;
	}
};

int interface_func(Stack* stack)
{
	int action, element_data;
	cout << "\n\nChoose action (from 0 to 8) "
		"\n {0} print stack"
		"\n {1} push element"
		"\n {2} pop element"
		"\n {3} peek element"
		"\n {4} swap the first and last element of the stack"
		"\n {5} reverse the stack"
		"\n {6} check if element in the stack"
		"\n {7} clear stack"
		"\n {8} exit" << endl;
	cin >> action;

	switch (action)
	{
	case 0:
		stack->print();
		break;
	case 1:
		cout << "Enter data: ";
		cin >> element_data;
		stack->push(element_data);
		break;
	case 2:
	{
		Node* head = stack->pop();
		if (head != NULL)
		{
			cout << "Top element: " << head->data << endl;
			cout << "Stack: ";
			stack->print();
		}
		else
			cout << "Stack is empty";
	}
	break;
	case 3:
		stack->peek();
		break;
	case 4:
		stack->swap_top_bottom();
		break;
	case 5:
		stack->reverse_stack();
		break;
	case 6:
	{
		cout << "Enter data: ";
		cin >> element_data;
		bool is_in_stack = stack->contains(element_data);
		cout << "Is this element on the stack: " << (is_in_stack ? "yes" : "no");
	}
	break;
	case 7:
		stack->clear_stack();
		break;
	case 8:
		return -1;
	default :
		cout << "Incorrect number" << endl;
	}
	return 0;
}

Stack* init_by_default()
{
	Stack* stack_default = new Stack();
	for (int i = 1; i < 7; i++)
		stack_default->push(i);

	return stack_default;
}

int main()
{
	Stack* stack = new Stack();
	stack = init_by_default();
	int res = 0;

	do
	{
		res = interface_func(stack);
	} while (res != -1);

	delete stack;

	return 0;
}