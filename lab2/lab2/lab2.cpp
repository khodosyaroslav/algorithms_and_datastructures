#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node* next;

	Node(int data_)
	{
		data = data_;
		next = NULL;
	}
	Node()
	{
		data = NULL;
		next = NULL;
	}
};

class LinkedList
{
private:
	Node* head;

	void swap_nodes(int data1, int data2)
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

public:
	LinkedList()
	{
		head = NULL;
	}

	void insert_head(int data)
	{
		Node* new_node = new Node(data);
		new_node->next = head;
		head = new_node;
	}

	void insert_after(int n, int data)
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

	void move_element_n_positions(int j, int n)
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

	void delete_by_index(int index)
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

	void delete_each_by_n(int n)
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

	LinkedList* sort()
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

	LinkedList* copy()
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

	void clear_list()
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

	bool contains_element(int data)
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

	void insert(int data)
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

	void print()
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

	Node* get_head()
	{
		return head;
	}

	~LinkedList()
	{
		Node* curr = head;
		while (curr != NULL)
		{
			Node* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
	}
};

LinkedList* merge_lists(LinkedList* list1, LinkedList* list2)
{
	LinkedList* list_new = list1->copy();
	LinkedList* list2_copy = list2->copy();

	Node* curr = list_new->get_head();
	if (curr == NULL)
	{
		delete list_new;
		return list2_copy;
	}

	while (curr->next != NULL)
		curr = curr->next;

	Node* list2_head = list2_copy->get_head();
	if (list2_head != NULL)
		curr->next = list2_head;

	return list_new;
}

LinkedList* get_list_with_common_elements(LinkedList* list1, LinkedList* list2)
{
	LinkedList* list_new = new LinkedList;
	Node* curr1 = list1->get_head();
	Node* curr2 = list2->get_head();

	while (curr1 != NULL)
	{
		while (curr2 != NULL)
		{
			if (curr1->data == curr2->data && !list_new->contains_element(curr1->data))
			{
				list_new->insert(curr1->data);
			}
			curr2 = curr2->next;
		}

		curr1 = curr1->next;
		curr2 = list2->get_head();
	}

	return list_new;
}

class CircularLinkedList
{
private:
	Node* head;
	Node* tail;
public:
	CircularLinkedList()
	{
		head = tail = NULL;
	}

	void insert(int data)
	{
		Node* new_node = new Node(data);
		new_node->next = NULL;

		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
			tail->next = head;
		}
		else
		{
			new_node->next = head;
			tail->next = new_node;
			tail = new_node;
		}
	}

	void remove(int data)
	{
		Node* prev = NULL;
		Node* curr = head;

		do
		{
			if (curr->data == data)
			{
				if (prev != NULL)
				{
					Node* next = curr->next;
					if (curr == tail)
						tail = prev;
					delete curr;
					prev->next = next;
				}
				else
				{
					Node* next = curr->next;
					delete curr;
					head = next;
					tail->next = next;
				}
				return;
			}
			prev = curr;
			curr = curr->next;
		} while (curr != head);
	}

	CircularLinkedList* get_list_of_nth(int n)
	{
		CircularLinkedList* list_new = new CircularLinkedList();
		CircularLinkedList* list_copy = copy();
		Node* curr = list_copy->get_head();
		int counter = 1;

		while (curr->next != curr)
		{
			Node* tmp = curr;
			if (counter % n == 0)
			{
				list_new->insert(tmp->data);
				curr = tmp->next;
				list_copy->remove(tmp->data);
				counter = 1;
			}
			else
			{
				counter++;
				curr = curr->next;
			}
		}
		list_new->insert(curr->data);
		list_copy->remove(curr->data);

		return list_new;
	}

	void print()
	{
		Node* curr = head;

		if (curr != NULL)
		{
			do
			{
				cout << curr->data << " ";
				curr = curr->next;
			} while (curr != head);
		}
		else
		{
			cout << "circular linked list is empty";
			return;
		}
	}

	CircularLinkedList* copy()
	{
		Node* curr = head;
		CircularLinkedList* list_copy = new CircularLinkedList();

		do
		{
			list_copy->insert(curr->data);
			curr = curr->next;
		} while (curr != head);

		return list_copy;
	}

	Node* get_head()
	{
		return head;
	}

	~CircularLinkedList()
	{
		Node* curr = head;
		do
		{
			Node* tmp = curr;
			curr = curr->next;
			delete tmp;
		} while (curr != head);
	}
};

int interface_func(LinkedList* list)
{
	int action, n, j;
	int element_data;
	cout << "\n\nChoose action (from 0 to 12) "
		"\n {0} print list"
		"\n {1} insert element to the beginning"
		"\n {2} insert element after the n-th element"
		"\n {3} move element to n positions"
		"\n {4} delete n-th element from the list"
		"\n {5} delete each n-th element of the list"
		"\n {6} sort elements in ascending order"
		"\n {7} create a copy of the list"
		"\n {8} clear list"
		"\n {9} merge two lists"
		"\n {10} create a list that contains the common elements of two lists"
		"\n {11} task with circular linked list "
		"\n {12} exit" << endl;
	cin >> action;

	switch (action)
	{
	case 0:
		list->print();
		break;
	case 1:
		cout << "Enter data: ";
		cin >> element_data;
		list->insert_head(element_data);
		break;
	case 2:
		cout << "Enter n: ";
		cin >> n;
		cout << "Enter data: ";
		cin >> element_data;
		list->insert_after(n, element_data);
		break;
	case 3:
		cout << "Enter index: ";
		cin >> j;
		cout << "Enter n: ";
		cin >> n;
		list->move_element_n_positions(j, n);
		break;
	case 4:
		cout << "Enter n: ";
		cin >> n;
		list->delete_by_index(n);
		break;
	case 5:
		cout << "Enter n: ";
		cin >> n;
		list->delete_each_by_n(n);
		break;
	case 6:
	{
		LinkedList* list_sorted = list->sort();
		cout << "Sorted list: ";
		list_sorted->print();
		delete list_sorted;
	}
	break;
	case 7:
	{
		LinkedList* list_copied = list->copy();
		cout << "my list: ";
		list->print();
		cout << "\ncopied list: ";
		list_copied->print();
		delete list_copied;
	}
	break;
	case 8:
		list->clear_list();
		break;
	case 9:
	{
		LinkedList* list1 = new LinkedList();
		LinkedList* list2 = new LinkedList();
		int n, m, element;

		cout << "Enter the number of elements of the first list: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "\nEnter " << i << "th elemnt in list1: " << endl;
			cin >> element;
			list1->insert(element);
		}

		cout << "\nEnter the number of elements of the second list: ";
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			cout << "\nEnter " << i << "th elemnt in list2: " << endl;
			cin >> element;
			list2->insert(element);
		}

		cout << "\nlist1: "; list1->print();
		cout << "\nlist2: "; list2->print();

		LinkedList* list_merged = merge_lists(list1, list2);
		cout << endl;
		list_merged->print();

		delete list1;
		delete list2;
		delete list_merged;
	}
	break;
	case 10:
	{
		LinkedList* list1 = new LinkedList;
		LinkedList* list2 = new LinkedList;
		int n, m, element;

		cout << "Enter the number of elements of the first list: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "\nEnter " << i << "th elemnt in list1: " << endl;
			cin >> element;
			list1->insert(element);
		}

		cout << "\nEnter the number of elements of the second list: ";
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			cout << "\nEnter " << i << "th elemnt in list2: " << endl;
			cin >> element;
			list2->insert(element);
		}

		cout << "\nlist1: "; list1->print();
		cout << "\nlist2: "; list2->print();

		LinkedList* list_intersection = get_list_with_common_elements(list1, list2);

		cout << "\nlist of common elements: ";
		list_intersection->print();

		delete list1;
		delete list2;
		delete list_intersection;
	}
	break;
	case 11:
	{
		CircularLinkedList* team1 = new CircularLinkedList();
		CircularLinkedList* team2 = new CircularLinkedList();
		int n, m, count, element;

		cout << "Enter the number of elements in the teams: ";
		cin >> count;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				cout << "\nEnter " << i << "th element in team1: " << endl;
				cin >> element;
				team1->insert(element);
			}
			cout << endl;
			for (int i = 0; i < count; i++)
			{
				cout << "\nEnter " << i << "th element in team2: " << endl;
				cin >> element;
				team2->insert(element);
			}

			cout << "Enter n for 1-st team: ";
			cin >> n;
			cout << "Enter m for 2-nd team: ";
			cin >> m;

			cout << "team1 : "; team1->print();
			cout << "\nteam2: "; team2->print();

			if (n >= 1 && m >= 1)
			{
				CircularLinkedList* team1_new = team1->get_list_of_nth(n);
				CircularLinkedList* team2_new = team2->get_list_of_nth(m);

				cout << "\n\nnew team1 : "; team1_new->print();
				cout << "\nnew team2: "; team2_new->print();

				delete team1_new;
				delete team2_new;
			}

			delete team1;
			delete team2;
		}
		else
		{
			cout << "n must be greater than 0";
		}
	}
	break;
	case 12:
		return -1;
	default:
		cout << "Incorrect number" << endl;
	}
	return 0;
}

LinkedList* init_by_default()
{
	LinkedList* list_default = new LinkedList();
	for (int i = 1; i < 7; i++)
		list_default->insert(i);

	return list_default;
}

int main()
{
	LinkedList* list = new LinkedList();
	list = init_by_default();
	int res = 0;

	do
	{
		res = interface_func(list);
	} while (res != -1);

	delete list;

	return 0;
}