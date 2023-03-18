#include <iostream>

using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;

	Node()
	{
		data = NULL;
		left = NULL;
		right = NULL;
	}

	Node(int data_, Node* left_, Node* right_)
	{
		data = data_;
		left = left_;
		right = right_;
	}
};

class BinaryTree
{
private:
	Node* root;

	Node* _insert(Node* current, int value)
	{
		if (current == NULL)
			return new Node(value, NULL, NULL);

		if (value < current->data)
			current->left = _insert(current->left, value);
		else
			current->right = _insert(current->right, value);

		return current;
	}

	Node* _remove(Node* current, int value)
	{
		if (current == NULL) return current;

		if (value < current->data)
			current->left = _remove(current->left, value);
		else if (value > current->data)
			current->right = _remove(current->right, value);
		else
		{
			if (current->left == NULL)
			{
				Node* tmp = current->right;
				delete current;
				return tmp;
			}
			else if (current->right == NULL)
			{
				Node* tmp = current->left;
				delete current;
				return tmp;
			}

			Node* tmp = min_node(current->right);
			current->data = tmp->data;
			current->right = _remove(current->right, tmp->data);
		}

		return current;
	}

	Node* min_node(Node* current)
	{
		while (current && current->left != NULL)
			current = current->left;

		return current;
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

	void _print(Node* node, string indent, bool is_left)
	{
		if (node != NULL)
		{
			cout << indent;
			cout << (is_left ? "L--" : "R--");

			cout << node->data << endl;

			_print(node->left, indent + (is_left ? "|  " : "   "), true);
			_print(node->right, indent + (is_left ? "|  " : "   "), false);
		}
	}

	void clear_memory(Node* current)
	{
		if (current == NULL) return;

		clear_memory(current->left);
		clear_memory(current->right);

		delete current;
	}

public:
	BinaryTree()
	{
		root = new Node();
	}
	BinaryTree(int root_value)
	{
		root = new Node(root_value, NULL, NULL);
	}

	void insert(int value)
	{
		root = _insert(root, value);
	}
	
	void remove(int value)
	{
		Node* curr = _find(root, value);
		if (curr != NULL)
			_remove(root, value);
		else
			cout << "no " << value << " element in tree\n";
	}

	void find(int value)
	{
		Node* curr = _find(root, value);
		if (curr != NULL)
			cout << "element " << value << " found!\n";
		else
			cout << "element " << value << " not found\n";
	}

	void print()
	{
		_print(root, "", false);
	}

	~BinaryTree()
	{
		clear_memory(root);
	}
};

int interface_func(BinaryTree* tree)
{
	int action, value;
	cout << "\n\nChoose action (from 0 to 4) "
		"\n {0} print tree"
		"\n {1} insert"
		"\n {2} remove"
		"\n {3} find"
		"\n {4} exit" << endl;
	cin >> action;

	switch (action)
	{
	case 0:
		tree->print();
		break;
	case 1:
	{
		cout << "Enter value: ";
		cin >> value;
		tree->insert(value);
	}
	break;
	case 2:
	{
		cout << "Enter value: ";
		cin >> value;
		tree->remove(value);
	}
	break;
	case 3:
	{
		cout << "Enter value: ";
		cin >> value;
		tree->find(value);
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
	int root_value;
	cout << "Insert root: ";
	cin >> root_value;

	BinaryTree* tree = new BinaryTree(root_value);
	int res = 0;

	do
	{
		res = interface_func(tree);
	} while (res != -1);

	delete tree;

	return 0;
}