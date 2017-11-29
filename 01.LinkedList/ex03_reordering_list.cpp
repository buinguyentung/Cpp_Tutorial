/* Function reorderList(): Reordering a singly linked list
    From: L0->L1->...->Ln-1->Ln
    To: L0->Ln->L1->Ln-1->...
*/
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

// insert new node at the end
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

// insert new node at the start
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

void reorderList(node **head) {
    if (*head == NULL) {
        return;
    }
    node *cur = *head;
    while (cur != NULL) {
        if (cur->next == NULL || (cur->next)->next == NULL) {
            return;
        }
        /* Find tail and pre_tail pointers */
        node *pre_tail = cur->next;
        node *tail = pre_tail->next;
        while (tail->next != NULL) {
            pre_tail = tail;
            tail = tail->next;
        }
        /* Reorder tail */
        node *temp = cur->next;
        cur->next = tail;
        tail->next = temp;
        cur = temp;
        pre_tail->next = NULL; /* pre_tail is the new tail */
    }
}

int main() {
    node *head = new node();

    initNode(head, 1);
    displayList(head);
    addNote(head, 2);
    displayList(head);
    addNote(head, 3);
    displayList(head);
    addNote(head, 4);
    displayList(head);
    addNote(head, 5);
    displayList(head);

    reorderList(&head);
    displayList(head);

    return 0;
}




