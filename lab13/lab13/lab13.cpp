#include <iostream>

using namespace std;

struct Node
{
	int data;
	int priority;
	Node* left;
	Node* right;

	Node()
	{
		data = NULL;
		priority = NULL;
		left = NULL;
		right = NULL;
	}

	Node(int data_, int priority_, Node* left_, Node* right_)
	{
		data = data_;
		priority = priority_;
		left = left_;
		right = right_;
	}
};

class Treap
{
private:
	Node* root;

	void split(Node* node, int x0, Node*& l, Node*& r)
	{
		if (node == NULL)
			l = r = NULL;
		else if (x0 > node->data)
		{
			split(node->right, x0, node->right, r);
			l = node;
		}
		else
		{
			split(node->left, x0, l, node->left);
			r = node;
		}
	}

	Node* merge(Node* l, Node* r)
	{
		if (!l || !r)
			return l ? l : r;
		else if (l->priority > r->priority)
		{
			l->right = merge(l->right, r);
			return l;
		}
		else
		{
			r->left = merge(l, r->left);
			return r;
		}
	}

	Node* _find(Node* current, int value)
	{
		if (current == NULL || current->data == value)
			return current;

		if (value < current->data)
			return _find(current->left, value);
		else
			return _find(current->right, value);
	}
	void _remove(Node*& node, int data)
	{
		if (node->data == data)
		{
			Node* curr = node;
			node = merge(node->left, node->right);
			delete curr;
		}
		else
			_remove(data < node->data ? node->left : node->right, data);
	}

	void _print(Node* node, string indent, bool is_left)
	{
		if (node != NULL)
		{
			cout << indent;
			cout << (is_left ? "L--" : "R--");

			cout << "(" << node->data << ", " << node->priority << ")" << endl;

			_print(node->left, indent + (is_left ? "|  " : "   "), true);
			_print(node->right, indent + (is_left ? "|  " : "   "), false);
		}
	}

public:
	Treap()
	{
		root = new Node();
	}
	Treap(int root_data, int root_priority)
	{
		root = new Node(root_data, root_priority, NULL, NULL);
	}

	void insert(int data, int priority)
	{
		Node* node = new Node(data, priority, NULL, NULL);
		Node* l = NULL; Node* r = NULL;
		split(root, data, l, r);
		root = merge(merge(l, node), r);
	}
	
	void remove(int data)
	{
		Node* curr = _find(root, data);
		if (curr != NULL)
			_remove(root, data);
		else
			cout << "no " << data << " element in tree\n";
	}
	
	void print()
	{
		_print(root, "", false);
	}

	void clear_memory(Node* current)
	{
		if (current == NULL) return;

		clear_memory(current->left);
		clear_memory(current->right);

		delete current;
	}

	~Treap()
	{
		clear_memory(root);
	}
};

int interface_func(Treap* treap)
{
	int action, value, priority;
	cout << "\n\nChoose action (from 0 to 3) "
		"\n {0} print treap"
		"\n {1} insert"
		"\n {2} remove"
		"\n {3} exit" << endl;
	cin >> action;
	switch (action)
	{
	case 0:
		treap->print();
		break;
	case 1:
	{
		cout << "Enter value: ";
		cin >> value;
		cout << "Enter priority: ";
		cin >> priority;
		treap->insert(value, priority);
	}
	break;
	case 2:
	{
		cout << "Enter value: ";
		cin >> value;
		treap->remove(value);
	}
	break;
	case 3:
		return -1;
	default:
		cout << "Incorrect number" << endl;
	}

	return 0;
}

int main()
{
	int root_value, root_priority;
	cout << "Insert root value: ";
	cin >> root_value;
	cout << "Insert root priority: ";
	cin >> root_priority;

	Treap* treap = new Treap(root_value, root_priority);
	int res = 0;

	do
	{
		res = interface_func(treap);
	} while (res != -1);

	delete treap;

	return 0;
}