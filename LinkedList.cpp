// A complete working C++ program to demonstrate
// all insertion methods on Linked List
#include <bits/stdc++.h>
#include <wx/wx.h>
using namespace std;

// A linked list node
class Node
{
public:
    wxBitmapButton* data;
    Node *next;
};

// Linked list class
class LinkedList
{
private:
    Node *head;
    int size;

public:
    LinkedList()
    {
        head = nullptr;
        size = 0;
    }
    Node* getHead()
    {
        return head;
    }
    int getSize()
    {
        return size;
    }
    wxBitmapButton* getIndex(int index)
    {
        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    wxBitmapButton* getButton(int id)
    {
        int index = (((id-(id%10))/10) - 1)*6 + id%10 - 1;
        return getIndex(index);
    }
    
    void push(wxBitmapButton *new_data)
    {
        /* 1. allocate node */
        Node *new_node = new Node();

        /* 2. put in the data */
        new_node->data = new_data;

        /* 3. Make next of new node as head */
        new_node->next = (head);

        /* 4. move the head to point to the new node */
        (head) = new_node;

        size++;
    }

    void insertAfter(Node *prev_node, wxBitmapButton *new_data)
    {
        /*1. check if the given prev_node is nullptr */
        if (prev_node == nullptr)
        {
            cout << "The given previous node cannot be nullptr";
            return;
        }

        /* 2. allocate new node */
        Node *new_node = new Node();

        /* 3. put in the data */
        new_node->data = new_data;

        /* 4. Make next of new node as next of prev_node */
        new_node->next = prev_node->next;

        /* 5. move the next of prev_node as new_node */
        prev_node->next = new_node;

        size++;
    }

    void append(wxBitmapButton *new_data)
    {
        /* 1. allocate node */
        Node *new_node = new Node();

        Node *last = head; /* used in step 5*/

        /* 2. put in the data */
        new_node->data = new_data;

        /* 3. This new node is going to be
        the last node, so make next of
        it as nullptr*/
        new_node->next = nullptr;

        /* 4. If the Linked List is empty,
        then make the new node as head */
        if (head == nullptr)
        {
            head = new_node;
            size++;
            return;
        }

        /* 5. Else traverse till the last node */
        while (last->next != nullptr)
        {
            last = last->next;
        }

        /* 6. Change the next of last node */
        last->next = new_node;

        size++;
        return;
    }

    void clear()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        size = 0;
    }
    // void printList()
    // {
    //     Node *node = (head);
    //     while (node != nullptr)
    //     {
    //         cout << " " << node->data;
    //         node = node->next;
    //     }
    // }
};
