/* Counting BST nodes that lies in a given range
    Input:
        10
      /    \
    5       50
   /       /  \
 1       40   100
    Range: [5, 45]

    Output:  3
    There are three nodes in range, 5, 10 and 40
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

/* Traverse and count the number of node in given range */
void inorderTraverse(struct node* root, int l, int h, int &res) {
    if (root == NULL) {
        return;
    }
    if (root->data < l) {
        inorderTraverse(root->right, l, h, res);
    }
    else if (root->data > h) {
        inorderTraverse(root->left, l, h, res);
    }
    else {
        res++;
        inorderTraverse(root->left, l, h, res);
        inorderTraverse(root->right, l, h, res);
    }
}

int getCountOfNode (node* root, int l, int h) {
    int res = 0;
    inorderTraverse(root, l, h, res);
    return res;
}

int main()
{
    int test_case, N, key, l, h;

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

        cin >> l >> h;
        cout << getCountOfNode(root, l, h) << endl;

        test_case--;
    }

    fclose(stdin);
    return 0;
}
