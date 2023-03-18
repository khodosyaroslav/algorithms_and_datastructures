#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int data;
	Node* leftmost_child;
	Node* right_sibling;
	
	Node()
	{
		data = NULL;
		leftmost_child = NULL;
		right_sibling = NULL;
	}
	
	Node(int data_, Node* leftmost_child_, Node* right_sibling_)
	{
		data = data_;
		leftmost_child = leftmost_child_;
		right_sibling = right_sibling_;
	}
};

class Tree
{
	private:
	Node* root;
	
	Node* _find_node(Node* node, int value)
	{
		if (node == NULL)
			return NULL;
		if (node->data == value)
			return node;
		
		Node* res = _find_node(node->leftmost_child, value);
		if (res == NULL)
		{
			return _find_node(node->right_sibling, value);
		}
		
		return res;
	}
	
	void _remove(Node* node, int value, Node* previous)
	{
		Node* curr = node->leftmost_child;
		if (curr != NULL && node->data == value)
		{
			cout << "node can't be deleted\n";
			return;
		}
		if (curr == NULL && node->data == value)
		{
			Node* prev_child = previous->leftmost_child;
			if (prev_child != NULL && prev_child->data == node->data)
			{
				Node* next = node->right_sibling;
				previous->leftmost_child = next;
				delete node;
				return;
			}
			else
			{
				Node* next = node->right_sibling;
				previous->right_sibling = next;
				delete node;
				return;
			}
		}
		else
		{
			Node* prev = node;
			while (curr != NULL)
			{
				_remove(curr, value, prev);
				
				prev = curr;
				if (!contains(prev))
					return;
				curr = curr->right_sibling;
			}
		}
	}
	
	void _preorder(Node* node)
	{
		cout << node->data << " ";
		Node* curr = node->leftmost_child;
		while (curr != NULL)
		{
			_preorder(curr);
			curr = curr->right_sibling;
		}
	}
	
	void _postorder(Node* node)
	{
		Node* curr = node->leftmost_child;
		while (curr != NULL)
		{
			_postorder(curr);
			curr = curr->right_sibling;
		}
		cout << node->data << " ";
	}
	
	void _inorder(Node* node)
	{
		Node* curr = node->leftmost_child;
		if (curr == NULL)
			cout << node->data << " ";
		else
		{
			_inorder(curr);
			cout << node->data << " ";
			curr = node->leftmost_child->right_sibling;
			while (curr != NULL)
			{
				_inorder(curr);
				curr = curr->right_sibling;
			}
		}
	}
	
	void _print(Node* node, string indent, bool last)
	{
		cout << indent << "+- " << node->data << endl;
		indent += last ? "   " : "|  ";
		
		Node* curr = node->leftmost_child;
		while (curr != NULL)
		{
			_print(curr, indent, curr->right_sibling == NULL);
			curr = curr->right_sibling;
		}
	}
	
	public:
	Tree()
	{
		root = new Node();
	}
	Tree(int root_value)
	{
		root = new Node(root_value, NULL, NULL);
	}
	
	void insert(int value, int parent_val)
	{
		if (root == NULL)
		{
			root = new Node(value, NULL, NULL);
			return;
		}
		
		Node* parent = _find_node(root, parent_val);
		if (parent == NULL) return;
		if (parent->leftmost_child == NULL) 
			parent->leftmost_child = new Node(value, NULL, NULL);
		else 
		{
			Node* curr = parent->leftmost_child;
			while (curr->right_sibling != NULL)
				curr = curr->right_sibling;
			curr->right_sibling = new Node(value, NULL, NULL);
		}
	}
	
	void remove(int value)
	{
		Node* curr = _find_node(root, value);
		if (curr != NULL)
			_remove(root, value, NULL);
		else
			cout << "no " << value << " element in tree\n";
	}
	
	bool contains(Node* node)
	{
		Node* node_in_tree = _find_node(root, node->data);
		if (node_in_tree != NULL)
			return true;
		return false;
	}
	
	// pryamiy
	void preorder()
	{
		_preorder(root);
	}
	
	// zvorotniy
	void postorder()
	{
		_postorder(root);
	}
	
	// symmetry
	void inorder()
	{
		_inorder(root);
	}
	
	void find(int value)
	{
		Node* curr = _find_node(root, value);
		if (curr != NULL)
			cout << "element " << value << " found!\n";
		else
			cout << "element " << value << " not found\n";
	}
	
	void print()
	{
		if (root != NULL)
			_print(root, "", true);
		else
			cout << "Tree is empty\n";
	}
	
	~Tree()
	{
		delete root;
	}
};

int interface_func(Tree* tree)
{
	int action, value, parent_value;
	cout << "\n\nChoose action (from 0 to 5) "
		"\n {0} print tree"
		"\n {1} insert element (val, parent_val)"
		"\n {2} remove"
		"\n {3} find"
		"\n {4} print traversals"
		"\n {5} exit" << endl;
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
			cout << "Enter parent value: ";
			cin >> parent_value;
			tree->insert(value, parent_value);
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
		{
			cout << "Preorder: ";
			tree->preorder();
			
			cout << "\nPostorder: ";
			tree->postorder();
			
			cout << "\nInorder: ";
			tree->inorder();
		}
		break;
		case 5:
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
	
	Tree* tree = new Tree(root_value);
	int res = 0;
	
	do
	{
		res = interface_func(tree);
	} while (res != -1);
	
	delete tree;
	
	return 0;
}