/*
 Copyright 2023
 */

#include <bits/stdc++.h>
using std::queue;
using std::cout;
using std::endl;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* NewNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

Node* InsertNode(Node* root, int data) {
    if (root == NULL) {
        root = NewNode(data);
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp->left != NULL) {
            q.push(temp->left);
        } else {
            temp->left = NewNode(data);
            break;
        }

        if (temp->right != NULL) {
            q.push(temp->right);
        } else {
            temp->right = NewNode(data);
            break;
        }
    }
    return root;
}

void inorder(Node* temp) {
    if (temp == NULL) return;
    inorder(temp->left);
    cout << temp->data << ' ';
    inorder(temp->right);
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

// time complexity O(n)
int maxDepth(Node* node) {
    if (node == NULL) return 0;
    int lDepth = maxDepth(node->left);
    int rDepth = maxDepth(node->right);

    return max(lDepth, rDepth) + 1;
}

// using level order traversal
// time complexity O(n)
int height(Node* root) {
    int depth = 0;
    queue<Node*> q;

    q.push(root);
    q.push(NULL);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp == NULL) depth++;

        if (temp != NULL) {
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        } else if (!q.empty()) {
            q.push(NULL);
        }
    }
    return depth;
}

int main(int argc, char** argv) {
    Node* root = NewNode(10);
    root->left = NewNode(11);
    root->right = NewNode(9);
    root->left->left = NewNode(7);
    root->right->left = NewNode(15);
    root->right->right = NewNode(8);

    // printf("Height of tree with maxDepth is %d\n", maxDepth(root));
    // printf("Height of tree with height is %d\n", height(root));

    cout << "Inorder traversal before insertion: ";
    inorder(root);
    cout << endl;
    root = InsertNode(root, 12);

    cout << "Inorder traversal after insertion: ";
    inorder(root);
    cout << endl;

    return 0;
}
