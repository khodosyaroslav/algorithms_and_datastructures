#include <iostream>

using namespace std;

class BinaryHeap
{
private:
	int* arr;
	int capacity;
	int size;

	int parent(int i) { return (i - 1) / 2; }

	int left(int i) { return (2 * i + 1); }

	int right(int i) { return (2 * i + 2); }

public:
	BinaryHeap(int size_)
	{
		capacity = 0;
		size = size_;
		arr = new int[size_];
	}

	void sift_up(int i)
	{
		if (i == 0) return;

		if (arr[i] < arr[parent(i)])
		{
			swap(arr[i], arr[parent(i)]);
			sift_up(parent(i));
		}
	}

	void sift_down(int i)
	{
		int left_child_index = left(i);
		int right_child_index = right(i);

		if (left_child_index >= capacity)
			return;

		int min_index = i;

		if (arr[left_child_index] < arr[i])
			min_index = left_child_index;
		if (right_child_index < capacity && arr[right_child_index] < arr[min_index])
			min_index = right_child_index;

		if (min_index != i)
		{
			swap(arr[i], arr[min_index]);
			sift_down(min_index);
		}
	}

	void insert(int item)
	{
		capacity++;
		arr[capacity - 1] = item;
		sift_up(capacity - 1);

		if (capacity == size)
			resize(size * 2);
	}

	void remove(int item)
	{
		if (capacity == 0) return;
		
		int index = get_item_index(item);

		arr[index] = arr[capacity - 1];
		arr[capacity - 1] = NULL;
		capacity--;
		sift_down(index);

		if (((double)capacity / size) < 0.25)
			resize(size / 2);
	}

	int get_item_index(int item)
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr[i] == item)
				return i;
		}
		return -1;
	}

	void resize(int size_new)
	{
		int* arr_resized = new int[size_new];
		for (int i = 0; i < size_new; i++)
			arr_resized[i] = NULL;

		int* tmp = arr;
		int size_old = size;

		size = size_new;
		capacity = 0;
		arr = arr_resized;

		for (int i = 0; i < size_old; i++)
		{
			if (tmp[i] != NULL)
				insert(tmp[i]);
		}

		delete tmp;
	}

	void print()
	{
		int j = 0, level = 0;
		while (j < capacity)
		{
			j += (int)pow(2, level);
			level++;
		}

		int spaces = level;
		for (int i = 0; i < level; i++)
		{
			cout << string((int)pow(2, spaces - 1), ' ');
			for (int h = 0; h < pow(2, i); h++)
			{
				if (pow(2, i) + h > capacity)
					break;
				cout << arr[(int)(pow(2, i) - 1) + h] << string(count_spaces(level - i), ' ');
			}
			cout << endl;
			spaces--;
		}
		cout << endl;
	}
	int count_spaces(int num)
	{
		int res = 1;
		for (int i = 0; i < num; i++)
			res += 2 * i;
		return res;
	}

	~BinaryHeap()
	{
		delete arr;
	}
};

int interface_func(BinaryHeap* heap)
{
	int action, value;
	cout << "\n\nChoose action (from 0 to 3) "
		"\n {0} print binary heap"
		"\n {1} insert"
		"\n {2} remove"
		"\n {3} exit" << endl;
	cin >> action;

	switch (action)
	{
	case 0:
		heap->print();
		break;
	case 1:
	{
		cout << "Enter value: ";
		cin >> value;
		heap->insert(value);
	}
	break;
	case 2:
	{
		cout << "Enter value: ";
		cin >> value;
		heap->remove(value);
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
	BinaryHeap* heap = new BinaryHeap(5);
	int res = 0;

	do
	{
		res = interface_func(heap);
	} while (res != -1);

	delete heap;

	return 0;
}