#include <iostream>
#include <windows.h>

using namespace std;

enum Color { RED, BLACK };

struct Node
{
	int data;
	Color color;
	Node* left;
	Node* right;
	Node* parent;

	Node()
	{
		data = NULL;
		color = RED;
		left = right = parent = NULL;
	}

	Node(int data_, Color color_, Node* left_, Node* right_, Node* parent_)
	{
		data = data_;
		color = color_;
		left = left_;
		right = right_;
		parent = parent_;
	}

	Node* sibling()
	{
		if (parent == NULL)
			return NULL;
		if (this == parent->left)
			return parent->right;
		return parent->left;
	}

	bool has_red_child()
	{
		return (left != NULL && left->color == RED) || (right != NULL && right->color == RED);
	}
};

class RBTree
{
private:
	Node* root;

	void right_rotate(Node*& root, Node*& node)
	{
		Node* new_root = node->left;
		node->left = new_root->right;

		if (node->left != NULL)
			node->left->parent = node;

		new_root->parent = node->parent;
		
		if (node->parent == NULL)
			root = new_root;
		else if (node == node->parent->left)
			node->parent->left = new_root;
		else
			node->parent->right = new_root;

		new_root->right = node;
		node->parent = new_root;
	}
	void left_rotate(Node*& root, Node*& node)
	{
		Node* new_root = node->right;
		node->right = new_root->left;

		if (node->right != NULL)
			node->right->parent = node;

		new_root->parent = node->parent;

		if (node->parent == NULL)
			root = new_root;
		else if (node == node->parent->left)
			node->parent->left = new_root;
		else
			node->parent->right = new_root;

		new_root->left = node;
		node->parent = new_root;
	}

	Node* bst_insert(Node* root, Node* node)
	{
		if (root == NULL)
			return node;

		if (node->data < root->data)
		{
			root->left = bst_insert(root->left, node);
			root->left->parent = root;
		}
		else if (node->data > root->data)
		{
			root->right = bst_insert(root->right, node);
			root->right->parent = root;
		}

		return root;
	}
	void adjust_insertion(Node*& root, Node*& node)
	{
		Node* parent = NULL;
		Node* grand_parent = NULL;

		if (node == NULL || root == NULL)
			return;

		while (node != root && node->color != BLACK && node->parent->color == RED)
		{
			parent = node->parent;
			grand_parent = node->parent->parent;

			if (parent == grand_parent->left)
			{
				Node* uncle = grand_parent->right;

				if (uncle != NULL && uncle->color == RED)
				{
					grand_parent->color = RED;
					parent->color = BLACK;
					uncle->color = BLACK;
					node = grand_parent; 
				}
				else
				{
					if (node == parent->right)
					{
						left_rotate(root, parent);
						node = parent;
						parent = node->parent;
					}

					right_rotate(root, grand_parent);
					if (parent != NULL && grand_parent != NULL)
						swap(parent->color, grand_parent->color);
					node = parent;
				}
			}
			else
			{
				Node* uncle = grand_parent->left;

				if (uncle != NULL && uncle->color == RED)
				{
					grand_parent->color = RED;
					parent->color = BLACK;
					uncle->color = BLACK;
					node = grand_parent;
				}
				else
				{
					if (node = parent->left)
					{
						right_rotate(root, parent);
						node = parent;
						parent = node->parent;
					}

					left_rotate(root, grand_parent);
					if (parent != NULL && grand_parent != NULL)
						swap(parent->color, grand_parent->color);
					node = parent;
				}
			}
		}

		if (root != NULL)
			root->color = BLACK;
	}

	void _remove(Node* v)
	{
		Node* u = bst_node_replace(v);

		bool uv_black = (u == NULL || u->color == BLACK) && (v->color == BLACK);
		Node* parent = v->parent;

		if (u == NULL)
		{
			if (v == root)
				root = NULL;
			else
			{
				if (uv_black)
					adjust_double_black(v);
				else
				{
					if (v->sibling() != NULL)
						v->sibling()->color = RED;
				}

				if (v == parent->left)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			delete v;
			return;
		}

		if (v->left == NULL || v->right == NULL)
		{
			if (v == root)
			{
				v->data = u->data;
				v->left = v->right = NULL;
				delete u;
			}
			else
			{
				if (v == parent->left)
					parent->left = u;
				else
					parent->right = u;
				delete v;
				u->parent = parent;
				if (uv_black)
					adjust_double_black(u);
				else
					u->color = BLACK;
			}
			return;
		}

		swap(u->data, v->data);
		_remove(u);
	}
	Node* bst_node_replace(Node* node)
	{
		if (node->left != NULL && node->right != NULL)
			return node_with_max_value(node->left);

		if (node->left == NULL && node->right == NULL)
			return NULL;

		if (node->left != NULL)
			return node->left;
		else
			return node->right;
	}
	void adjust_double_black(Node* node)
	{
		if (node == root) return;

		Node* sibling = node->sibling();
		Node* parent = node->parent;

		if (sibling == NULL)
			adjust_double_black(parent);
		else
		{
			if (sibling->color == RED)
			{
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling == parent->left)
					right_rotate(root, parent);
				else
					left_rotate(root, parent);
				adjust_double_black(node);
			}
			else
			{
				if (sibling->has_red_child())
				{
					if (sibling->left != NULL and sibling->left->color == RED)
					{
						if (sibling == parent->left)
						{
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							right_rotate(root, parent);
						}
						else
						{
							sibling->left->color = parent->color;
							right_rotate(root, sibling);
							left_rotate(root, parent);
						}
					}
					else
					{
						if (sibling == parent->left)
						{
							sibling->right->color = parent->color;
							left_rotate(root, sibling);
							right_rotate(root, parent);
						}
						else
						{
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							left_rotate(root, parent);
						}
					}
					parent->color = BLACK;
				}
				else
				{
					sibling->color = RED;
					if (parent->color == BLACK)
						adjust_double_black(parent);
					else
						parent->color = BLACK;
				}
			}
		}
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

	void _print(Node* node, string indent, bool is_left, HANDLE console_color)
	{
		SetConsoleTextAttribute(console_color, 240);
		if (node != NULL)
		{
			cout << indent;

			if (node->color == BLACK)
				SetConsoleTextAttribute(console_color, 240);
			else
				SetConsoleTextAttribute(console_color, 244);
			cout << (is_left ? "L--" : "R--");
			cout << node->data << endl;

			_print(node->left, indent + (is_left ? "|  " : "   "), true, console_color);
			_print(node->right, indent + (is_left ? "|  " : "   "), false, console_color);
		}
	}

public:
	RBTree(int root_value)
	{
		root = new Node(root_value, BLACK, NULL, NULL, NULL);
	}

	void insert(int value)
	{
		Node* node = new Node(value, RED, NULL, NULL, NULL);

		root = bst_insert(root, node);

		adjust_insertion(root, node);
	}
	
	void remove(int value)
	{
		Node* curr = _find(root, value);
		if (curr != NULL)
			_remove(curr);
		else
			cout << "no " << value << " element in tree\n";
	}
	
	void print()
	{
		HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		_print(root, "", false, console_color);
	}

	void clear_memory(Node* current)
	{
		if (current == NULL) return;

		clear_memory(current->left);
		clear_memory(current->right);

		delete current;
	}
	~RBTree()
	{
		clear_memory(root);
	}
};

int interface_func(RBTree* tree, HANDLE console_color)
{
	SetConsoleTextAttribute(console_color, 240);

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
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 240);
	
	int root_value;
	cout << "Insert root: ";
	cin >> root_value;

	RBTree* tree = new RBTree(root_value);

	int res = 0;

	do
	{
		res = interface_func(tree, console_color);
	} while (res != -1);

	delete tree;

    return 0;
}