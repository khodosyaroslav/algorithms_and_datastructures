#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

const int SIZE = 3;

class HashTable
{
private:
	LinkedList** arr_of_lists;

public:
	HashTable()
	{
		arr_of_lists = new LinkedList * [SIZE];
		for (int i = 0; i < SIZE; i++)
			arr_of_lists[i] = NULL;
	}

	int hash(int key)
	{
		return key % SIZE;
	}

	void insert(int key, int value)
	{
		int index = hash(key);

		LinkedList* current = arr_of_lists[index];

		if (current == NULL)
			current = new LinkedList();
		
		current->insert_head(key, value);

		arr_of_lists[index] = current;
	}

	void remove(int key)
	{
		int index = hash(key);
		if (arr_of_lists[index] != NULL && arr_of_lists[index]->contains_element(key))
			arr_of_lists[index]->delete_by_key(key);
		else
			cout << "No element with key " << key;
	}

	void find(int key)
	{
		int index = hash(key);
		if (arr_of_lists[index] != NULL)
			arr_of_lists[index]->find_element(key);
		else
			cout << "No element with key " << key;
	}

	void print()
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (arr_of_lists[i] == NULL)
				cout << "NULL" << endl;
			else
				arr_of_lists[i]->print();
		}
	}

	~HashTable()
	{
		for (int i = 0; i < SIZE; i++)
			delete arr_of_lists[i];
		delete[] arr_of_lists;
	}
};

int interface_func(HashTable* table)
{
	int action, key, value;
	cout << "\n\nChoose action (from 0 to 4) "
		"\n {0} print hashtable"
		"\n {1} insert element (key, val)"
		"\n {2} remove"
		"\n {3} find"
		"\n {4} exit" << endl;
	cin >> action;

	switch (action)
	{
	case 0:
		table->print();
		break;
	case 1:
	{
		cout << "Enter key: ";
		cin >> key;
		cout << "Entery value: ";
		cin >> value;
		table->insert(key, value);
	}
	break;
	case 2:
	{
		cout << "Enter key: ";
		cin >> key;
		table->remove(key);
	}
	break;
	case 3:
	{
		cout << "Enter key: ";
		cin >> key;
		table->find(key);
	}
	break;
	case 4:
		return -1;
	default:
		cout << "Incorrect number" << endl;
	}

	return 0;
}

int main()
{
	HashTable* table = new HashTable();
	int res = 0;

	do
	{
		res = interface_func(table);
	} while (res != -1);
	
	delete table;

	return 0;
}