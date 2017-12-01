/* Function mergeList(): merging and reversing two ascendant-ordered singly linked lists
    Output only one unique list which is descendant-ordered
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

void displayList(node *head) {
    node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    cout << endl;
}

/* recursive algorithm */
node *mergeList(node *head1, node *head2) {
    node *temp = new node;

    if (head1 == NULL) {
        temp = head2;
    }
    else if (head2 == NULL) {
        temp = head1;
    }
    else if (head1->data < head2->data) {
        temp->data = head1->data;
        temp->next = mergeList(head1->next, head2);
    }
    else {
        temp->data = head2->data;
        temp->next = mergeList(head1, head2->next);
    }
    return temp;
}

node *reverseList(node *head) {
    node *parent = new node;
    node *me = new node;
    node *child = new node;

    if (head != NULL && head->next != NULL) {
        parent = head;
        me = head->next;
        child = me->next;
        parent->next = NULL;
        while (child != NULL) {
            me->next = parent;
            parent = me;
            me = child;
            child = child->next;
        }
        me->next = parent;
        head = me;
    }
    return head;
}

int main() {
    node *head1 = new node();
    initNode(head1, 1);
    addNote(head1, 3);
    addNote(head1, 4);
    addNote(head1, 7);
    addNote(head1, 9);
    addNote(head1, 10);
    displayList(head1);

    node *head2 = new node();
    initNode(head2, 0);
    addNote(head2, 2);
    addNote(head2, 5);
    addNote(head2, 6);
    addNote(head2, 8);
    displayList(head2);

    cout << "*********** Merged list\n";
    head1 = mergeList(head1, head2);
    displayList(head1);

    cout << "*********** Reversed list\n";
    head1 = reverseList(head1);
    displayList(head1);

    return 0;
}




