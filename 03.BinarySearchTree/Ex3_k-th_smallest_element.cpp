/*          4
          /   \
         2     5
        /  \
       1    3
    Return the K-th smallest element. Ex. K = 3 return 3
    The time complexity would be O(h) where h is the height of the tree
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct node {
    int data;
    int lCount; /* count the number of child node on the left */
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

/* Traverse and count the number of left child */
int inorderTraverse(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lcount = inorderTraverse(root->left);
    //cout << root->data << " " << lcount << endl;
    root->lCount = lcount;
    int rcount = inorderTraverse(root->right);

    return lcount + rcount + 1;
}

int kthSmallestElement(struct node* root, int K) {
    int result = -1;

    inorderTraverse(root);

    if (root != NULL) {
        struct node* temp = root;
        while (temp != NULL) {
            if (temp->lCount + 1 == K) {
                result = temp->data;
                break;
            }
            else if (K > temp->lCount) {
                K = K - temp->lCount - 1;
                temp = temp->right;
            }
            else {
                temp = temp->left;
            }
        }
    }

    return result;
}

int main()
{
    int test_case, N, key, K;

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
        cin >> K;
        cout << kthSmallestElement(root, K) << endl;

        test_case--;
    }

    fclose(stdin);
    return 0;
}

