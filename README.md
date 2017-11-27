An example of Singly Linked List using C++

A linked list is a data structure that can store an indefinite amount of items. These items are connected using pointers in a sequential manner.
There are two types of linked list; singly-linked list, and doubly-linked list. 
	+ In a singly-linked list, every element contains some data and a link to the next element. 
	+ On the other hand, every node in a doubly-linked list contains some data, a link to the next node and a link to the previous node.
The elements of a linked list are called the nodes. A node has two fields i.e. data and next.
In C++, our code would look like this:
	struct node {
		int data;
		node *next;
	}

Example 1. linked_list_basics
Using a class linkedList
List of parameter
	1. head - node*
	2. tail - node*
List of operations:
	1. linkedList() - initializing head, tail to NULL
	2. createNode(int value) - creating or inserting at the end
	3. displayNode() - printing all the nodes
	4. insertStart(int value) - insertion at the start
	5. insertEnd(int value) - insertion at the end, same as createNode()
	6. insertPosition(int pos, int value) - insertion at a particular position
	7. deleteFist() - deleting at the start
	8. deleteLast() - deleting at the end
	9. deletePosition(int pos) - deleting at a particular position

Example 2. When the head of the list is not a global pointer
List of functions
	1. initNode(node *head, int value)
	2. addNote(node *head, int value)
	3. insertFront(node **head, int value)
	4. displayList(node *head)
	5. node *searchNode(node *head, int value)
	6. bool deleteNode(node **head, node *ptrDel)
	7. reverseList(node **head) - reversing a linked list using 3 parameters parent, me, child
	8. copyLinkedList(node *source, node **dest) - copying the linked list (Note: &((*dest)->next))
	9. int compareLinkedList(node *n1, node *n2) - comparing two linked list
	10. deleteLinkedList(node **head)

Example 3. Detecting circular (loop) linked list

Example 4. Stack implementation with linked list

Example 5. Finding intersection and union of two lists

Reference:
https://www.codementor.io/codementorteam/a-comprehensive-guide-to-implementation-of-singly-linked-list-using-c_plus_plus-ondlm5azr
http://www.bogotobogo.com/cplusplus/linkedlist.php
