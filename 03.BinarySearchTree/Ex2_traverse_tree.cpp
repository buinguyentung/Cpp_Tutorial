/*          4
          /   \
         2     5
        /  \
       1    3
    Depth First Traversal:
    1. Inorder: 1 2 3 4 5
    2. Preorder: 4 2 1 3 5
    3. Postorder: 1 3 2 5 4
    Breath First Traversal: 4 2 5 1 3
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct node {
    int data;
    struct node *left, *right;
};

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

/* Inorder traversal
    1. Traverse the left subtree
    2. Visit the root
    3. Traverse the right subtree
*/
void printInorder(struct node* root) {
    if (root != NULL) {
        printInorder(root->left);
        cout << root->data << " ";
        printInorder(root->right);
    }
}

/* Preorder traversal
    1. Visit the root
    2. Traverse the left subtree
    3. Traverse the right subtree
*/
void printPreorder(struct node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        printPreorder(root->left);
        printPreorder(root->right);
    }
}

/* Postorder traversal
    1. Traverse the left subtree
    2. Traverse the right subtree
    3. Visit the root
*/
void printPostorder(struct node* root) {
    if (root != NULL) {
        printPostorder(root->left);
        printPostorder(root->right);
        cout << root->data << " ";
    }
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
        printInorder(root);
        cout << endl;

        printPreorder(root);
        cout << endl;

        printPostorder(root);
        cout << endl;

        test_case--;
    }

    fclose(stdin);
    return 0;
}

