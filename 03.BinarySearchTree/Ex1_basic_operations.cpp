/* Basic operations on BST
    1. Searching for a key
    2. Printing a BST inorder
    3. Inserting a new value
    4. Deleting a node
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct node {
    int data;
    struct node *left, *right;
};

struct node* searchTree(struct node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (root->data > key) {
        return searchTree(root->left, key);
    }
    return searchTree(root->right, key);
}

void printTree(struct node* root) {
    if (root != NULL) {
        printTree(root->left);
        cout << root->data << " ";
        printTree(root->right);
    }
}

struct node* newNode(int value) {
    struct node *temp = new node;
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insertTree(struct node* root, int key) {
    if (root == NULL) {
        return newNode(key);
    }
    if (key < root->data) {
        root->left = insertTree(root->left, key);
    }
    else if (key > root->data) {
        root->right = insertTree(root->right, key);
    }

    return root;
}

struct node* minValueNode(struct node* root) {
    struct node* curr = root;
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

struct node* deleteNote(struct node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNote(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNote(root->right, key);
    }
    else {
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNote(root->right, temp->data);
    }
    return root;
}

int main()
{
    int test_case, N, key;

    freopen("input.txt", "r", stdin);

    cin >> test_case;
    while (test_case > 0) {
        cin >> N;
        struct node *root = NULL;
        while (N > 0) {
            cin >> key;
            root = insertTree(root, key);
            N--;
        }
        printTree(root);
        cout << endl;

        /* delete a node */
        cin >> key;
        root = deleteNote(root, key);
        printTree(root);
        cout << endl;

        test_case--;
    }

    fclose(stdin);
    return 0;
}

