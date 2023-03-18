#include <iostream>
#include "Node.h"

using namespace std;

class HashTable
{
private:
	Node** arr;
	int size;
	int capacity;

public:
	HashTable()
	{
		size = 0;
		capacity = 3;
		arr = new Node * [capacity];
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;
	}

	int hash(int key)
	{
		return key % capacity;
	}

	void insert(int key, int value)
	{
		int index = hash(key);
		while (arr[index] != NULL)
		{
			if (arr[index]->key == -1 && arr[index]->value == -1) break;
			index++;
			index %= capacity;
		}

		arr[index] = new Node(key, value);
		size++;

		if (((double)size / capacity) > 0.75)
			resize(capacity * 2);
	}

	void remove(int key)
	{
		int index = hash(key);
		while (arr[index] != NULL)
		{
			if (arr[index]->key == key)
			{
				arr[index]->key = -1;
				arr[index]->value = -1;
				size--;
				if (((double)size / capacity) < 0.25)
					resize(capacity / 2);
				return;
			}
			index++;
			index %= capacity;
		}
		cout << "No element with key " << key << endl;
	}

	void find(int key)
	{
		int index = hash(key);
		while (arr[index] != NULL)
		{
			if (arr[index]->key == key)
			{
				cout << "Element found (key:" << arr[index]->key << ", val:" << arr[index]->value << ")";
				return;
			}
			index++;
			index %= capacity;
		}
		cout << "No element with key " << key << endl;
	}

	void print()
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr[i] != NULL)
				cout << "(key:" << arr[i]->key << ", val:" << arr[i]->value << ")\n";
			else
				cout << "NULL\n";
		}
	}

	void resize(int capacity_new)
	{
		Node** arr_resized = new Node * [capacity_new];
		for (int i = 0; i < capacity_new; i++)
			arr_resized[i] = NULL;

		Node** tmp = arr;
		int capacity_old = capacity;

		capacity = capacity_new;
		size = 0;
		arr = arr_resized;

		for (int i = 0; i < capacity_old; i++)
		{
			if (tmp[i] != NULL && tmp[i]->key != -1 && tmp[i]->value != -1)
				insert(tmp[i]->key, tmp[i]->value);
		}

		for (int i = 0; i < capacity_old; i++)
			delete tmp[i];
		delete[] tmp;
	}
	
	~HashTable()
	{
		for (int i = 0; i < capacity; i++)
			delete arr[i];
		delete[] arr;
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