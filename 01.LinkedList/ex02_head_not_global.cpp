#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

void initNode(node *head, int value) {
    head->data = value;
    head->next = NULL;
}

// insert at the end
void addNote(node *head, int value) {
    node *temp = new node;
    temp->data = value;
    temp->next = NULL;

    node *cur = head;
    while (cur != NULL) {
        if (cur->next == NULL) {
            cur->next = temp;
            return;
        }
        cur = cur->next;
    }
}

// insert at the start
void insertFront(node **head, int value) {
    node *temp = new node;
    temp->data = value;
    temp->next = *head;
    *head = temp;
}

void displayList(node *head) {
    node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    cout << endl;
}

/* Search a node with data equal to value */
node *searchNode(node *head, int value) {
    node *temp = head;
    while (temp != NULL) {
        if (temp->data == value) return temp;
        temp = temp->next;
    }
    cout << "No node " << value << endl;
    return NULL;
}

/* Delete a particular node from the list */
bool deleteNode(node **head, node *ptrDel) {
    node *temp = *head;
    if (ptrDel == *head) {
        *head = temp->next;
        delete ptrDel;
        return true;
    }
    while (temp != NULL) {
        if (temp->next == ptrDel) {
            temp->next = ptrDel->next;
            delete ptrDel;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/* Reverse the list */
void reverseList(node **head) {
    node *parent = *head;
    node *me = parent->next;
    node *child = me->next;

    parent->next = NULL;
    while (child != NULL) {
        me->next = parent;
        parent = me;
        me = child;
        child = child->next;
    }
    me->next = parent;
    *head = me;
}

/* Create a copy of a linked list */
void copyLinkedList(node *source, node **dest) {
    if (source != NULL) {
        *dest = new node;
        (*dest)->data = source->data;
        (*dest)->next = source->next;
        copyLinkedList(source->next, &((*dest)->next));
    }
}

/* Compare two linked list */
int compareLinkedList(node *n1, node *n2) {
    static int flag;
    if (n1 == NULL && n2 == NULL) {
        flag = 1;
    }
    else {
        if (n1 == NULL || n2 == NULL) {
            flag = 0;
        }
        else if (n1->data != n2->data) {
            flag = 0;
        }
        else {
            compareLinkedList(n1->next, n2->next);
        }
    }
    return flag;
}

void deleteLinkedList(node **head) {
    node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = temp->next;
        delete temp;
    }
}

int main() {
    node *head = new node();

    initNode(head, 10);
    displayList(head);
    addNote(head, 20);
    displayList(head);
    addNote(head, 30);
    displayList(head);
    insertFront(&head, 5);
    displayList(head);

    int numDel = 20;
    node *ptrDel = searchNode(head, numDel);
    if (ptrDel != NULL) {
            if (deleteNode(&head, ptrDel)) {
                cout << "Node " << numDel << " deleted\n";
            }
    }
    displayList(head);

    reverseList(&head);
    displayList(head);

    node *newHead;
    copyLinkedList(head, &newHead);
    displayList(newHead);

    if (compareLinkedList(head, newHead)) {
        cout << "They are the same\n\n";
    }
    else
        cout << "They are distinctive\n\n";

    ptrDel = searchNode(newHead, 10);
    if (deleteNode(&newHead, ptrDel)) {
        cout << "newHead after delete\n";
        displayList(newHead);
    }

    if (compareLinkedList(head, newHead)) {
        cout << "They are the same\n\n";
    }
    else
        cout << "They are distinctive\n\n";

    deleteLinkedList(&newHead);
    displayList(head);

    return 0;
}

