#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

class linkedList {
private:
    node *head, *tail;
public:
    linkedList() {
        head = NULL;
        tail = NULL;
    }
    void createNode(int value);
    void displayNode();
    void insertStart(int value);
    void insertPosition(int pos, int value);
    void deleteFist();
    void deleteLast();
    void deletePosition(int pos);
};

int main_0() {
    linkedList *l1 = new linkedList();

    cout << "--- Create a new node at the End ---\n";
    l1->createNode(100);
    l1->displayNode();

    l1->createNode(23);
    l1->displayNode();

    l1->createNode(24);
    l1->displayNode();

    cout << "--- Insert a new node at the Start ---\n";
    l1->insertStart(8);
    l1->displayNode();

    l1->insertPosition(2, 15);
    l1->displayNode();

    l1->insertPosition(10, 1);
    l1->displayNode();

    cout << "--- Delete a node at the Start ---\n";
    l1->deleteFist();
    l1->displayNode();

    cout << "--- Delete a node at the End ---\n";
    l1->deleteLast();
    l1->displayNode();

    l1->deletePosition(3);
    l1->displayNode();

    return 0;
}

void linkedList::createNode(int value) {
    node *temp = new node;
    temp->data = value;
    temp->next = NULL;
    if (NULL == head) {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else {
        tail->next = temp;
        tail = temp;
        temp = NULL;
    }
}

void linkedList::displayNode() {
    node *temp = new node;
    temp = head;
    while (NULL != temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n\n";
}

void linkedList::insertStart(int value) {
    node *temp = new node;
    temp->data = value;
    temp->next = head;
    head = temp;
}

void linkedList::insertPosition(int pos, int value) {
    cout << "--- Insert a new node at a particular position " << pos << " ---\n";
    node *temp = new node;
    node *cur = new node;
    node *pre = new node;

    if (1 >= pos) {
        insertStart(value);
    }
    else {
        cur = head;
        for (int i = 1; i < pos; i++) {
            pre = cur;
            if (NULL == pre) {
                cout << pos << " is out of range, insert at the end, value = " << value << endl;
                createNode(value);
                return;
            }
            cur = cur->next;
        }
        temp->data = value;
        pre->next = temp;
        temp->next = cur;
    }
}

void linkedList::deleteFist() {
    node *temp = new node;
    temp = head;
    head = head->next;
    delete temp;
}

void linkedList::deleteLast() {
    node *pre = new node;
    node *cur = new node;
    cur = head;
    while (NULL != cur->next) {
        pre = cur;
        cur = cur->next;
    }
    tail = pre;
    pre->next = NULL;
    delete cur;
}

void linkedList::deletePosition(int pos) {
    cout << "--- Delete a node at position " << pos << " ---\n";
    node *pre = new node;
    node *cur = new node;
    cur = head;
    for (int i = 1; i < pos; i++) {
        pre = cur;
        cur = cur->next;
    }
    pre->next = cur->next;
    delete cur;
}


