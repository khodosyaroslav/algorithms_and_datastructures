#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

class Queue
{
private:
    LinkedList* list;

public:
    Queue()
    {
        list = new LinkedList();
    }

    void enqueue(int data)
    {
        list->insert(data);
    }

    Node* dequeue()
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
            cout << "First element: " << head->data;
        else
            cout << "Queue is empty";
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
            cout << "Queue is empty";
    }

    void reverse_queue()
    {
        list->reverse_list();
    }

    bool contains(int data)
    {
        return list->contains_element(data);
    }

    void clear_queue()
    {
        list->clear_list();
    }

    void print()
    {
        list->print();
    }

    ~Queue()
    {
        delete list;
    }
};

int interface_func(Queue* queue)
{
    int action, element_data;
    cout << "\n\nChoose action (from 0 to 8) "
        "\n {0} print queue"
        "\n {1} enqueue element"
        "\n {2} dequeue element"
        "\n {3} peek element"
        "\n {4} swap the first and last element of the queue"
        "\n {5} reverse the queue"
        "\n {6} check if element in the queue"
        "\n {7} clear queue"
        "\n {8} exit" << endl;
    cin >> action;

    switch (action)
    {
    case 0:
        queue->print();
        break;
    case 1:
        cout << "Enter data: ";
        cin >> element_data;
        queue->enqueue(element_data);
        break;
    case 2:
    {
        Node* head = queue->dequeue();
        if (head != NULL)
        {
            cout << "Top element: " << head->data << endl;
            cout << "Queue: ";
            queue->print();
        }
        else
            cout << "Queue is empty";
    }
    break;
    case 3:
        queue->peek();
        break;
    case 4:
        queue->swap_top_bottom();
        break;
    case 5:
        queue->reverse_queue();
        break;
    case 6:
    {
        cout << "Enter data: ";
        cin >> element_data;
        bool is_in_queue = queue->contains(element_data);
        cout << "Is this element on the queue: " << (is_in_queue ? "yes" : "no");
    }
    break;
    case 7:
        queue->clear_queue();
        break;
    case 8:
        return -1;
    default:
        cout << "Incorrect number" << endl;
    }

    return 0;
}

Queue* init_by_default()
{
    Queue* queue_default = new Queue();
    for (int i = 1; i < 7; i++)
        queue_default->enqueue(i);

    return queue_default;
}

int main()
{
    Queue* queue = new Queue();
    queue = init_by_default();
    int res = 0;

    do
    {
        res = interface_func(queue);
    } while (res != -1);

    delete queue;

    return 0;
}