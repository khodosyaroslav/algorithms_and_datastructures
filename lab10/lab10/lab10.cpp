#include <iostream>

using namespace std;

struct Node
{
	int data;
	int height;
	Node* left;
	Node* right;

	Node()
	{
		data = NULL;
		height = 1;
		left = NULL;
		right = NULL;
	}

	Node(int data_, Node* left_, Node* right_)
	{
		data = data_;
		height = 1;
		left = left_;
		right = right_;
	}
};

class AVLTree
{
private:
	Node* root;

	Node* balance(Node* current)
	{
		int balance_factor = get_balance_factor(current);
		if (balance_factor == 2)
		{
			if (height(current->left->left) >= height(current->left->right))
				return right_rotate(current);
			else
			{
				current->left = left_rotate(current->left);
				return right_rotate(current);
			}
		}
		if (balance_factor == -2)
		{
			if (height(current->right->left) <= height(current->right->right))
				return left_rotate(current);
			else
			{
				current->right = right_rotate(current->right);
				return left_rotate(current);
			}
		}
		return current;
	}

	Node* _insert(Node* current, int value)
	{
		if (current == NULL)
			return new Node(value, NULL, NULL);

		if (value < current->data)
			current->left = _insert(current->left, value);
		else if (value > current->data)
			current->right = _insert(current->right, value);
		else
			return current;

		update_height(current);
		
		return balance(current);
	}

	Node* right_rotate(Node* node)
	{
		Node* new_root = node->left;
		node->left = new_root->right;
		new_root->right = node;

		update_height(node);
		update_height(new_root);

		return new_root;
	}

	Node* left_rotate(Node* node)
	{
		Node* new_root = node->right;
		node->right = new_root->left;
		new_root->left = node;

		update_height(node);
		update_height(new_root);

		return new_root;
	}

	int height(Node* node)
	{
		if (node == NULL)
			return 0;
		return node->height;
	}

	void update_height(Node* node)
	{
		node->height = max(height(node->left), height(node->right)) + 1;
	}

	int get_balance_factor(Node* node)
	{
		if (node == NULL)
			return 0;
		return height(node->left) - height(node->right);
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

			Node* tmp = node_with_max_value(current->left);
			current->data = tmp->data;
			current->left = _remove(current->left, tmp->data);
		}

		if (current == NULL) return current;

		update_height(current);

		return balance(current);
	}

	Node* node_with_max_value(Node* current)
	{
		while (current && current->right != NULL)
			current = current->right;
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
	AVLTree()
	{
		root = new Node();
	}
	AVLTree(int root_value)
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
			root = _remove(root, value);
		else
			cout << "no " << value << " element in tree\n";
	}

	void print()
	{
		_print(root, "", false);
	}

	~AVLTree()
	{
		clear_memory(root);
	}
};

int interface_func(AVLTree* tree)
{
	int action, value;
	cout << "\n\nChoose action (from 0 to 3) "
		"\n {0} print tree"
		"\n {1} insert"
		"\n {2} remove"
		"\n {3} exit" << endl;
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

	AVLTree* tree = new AVLTree(root_value);
	int res = 0;

	do
	{
		res = interface_func(tree);
	} while (res != -1);

	delete tree;

	return 0;
}