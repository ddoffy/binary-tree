/*
 Copyright 2023
 */

#include <bits/stdc++.h>
using std::cout;
using std::endl;
using std::queue;

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

Node* Delete(Node* root, int data) {
    if (root == NULL) return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->data == data) return NULL;
        return root;
    }
    queue<Node*> q;
    q.push(root);

    Node* temp;
    Node* last;
    Node* data_node = NULL;

    while (!q.empty()) {
        temp = q.front();
        q.pop();

        if (temp->data == data) data_node = temp;

        if (temp->left != NULL) {
            last = temp;
            q.push(temp->left);
        }
        if (temp->right != NULL) {
            last = temp;
            q.push(temp->right);
        }
    }
    if (data_node != NULL) {
        data_node->data = temp->data;

        if (last->right == temp)
            last->right = NULL;
        else
            last->left = NULL;
        delete (temp);
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

void PrintCurrentLevel(Node* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        cout << root->data << " ";
        return;
    }

    PrintCurrentLevel(root->left, level - 1);
    PrintCurrentLevel(root->right, level - 1);
}

void PrintLevelOrder(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; ++i) {
        PrintCurrentLevel(root, i);
        cout << endl;
    }
}

void PrintGivenLevel(Node* root, int level, int ltr) {
    if (root == NULL) return;

    if (level == 1) {
        cout << root->data << " ";
        return;
    }

    if (ltr) {
        PrintGivenLevel(root->left, level - 1, ltr);
        PrintGivenLevel(root->right, level - 1, ltr);
    } else {
        PrintGivenLevel(root->right, level - 1, ltr);
        PrintGivenLevel(root->left, level - 1, ltr);
    }
}

void PrintSpiral(Node* root) {
    int h = height(root);

    bool ltr = false;
    for (int i = 1; i <= h; ++i) {
        PrintGivenLevel(root, i, ltr);
        ltr = !ltr;
    }
}

void RevertLevelOrder(Node* root) {
    int h = height(root);
    for (int i = h; i >= 1; --i) PrintGivenLevel(root, i, true);
}


void PreOrder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(Node* root) {
    if (root == NULL) return;
    PreOrder(root->left);
    PreOrder(root->right);
    cout << root->data << " ";
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

    root = Delete(root, 11);

    cout << "Inorder traversal after deletion: ";
    inorder(root);
    cout << endl;

    cout << "Height of tree with height is " << height(root) << endl;

    cout << "Level Order Traversal: " << endl;
    PrintLevelOrder(root);
    cout << endl;
    cout << "Spiral order traversal of binary tree is ";
    PrintSpiral(root);
    cout << endl;

    cout << "Revert level order of binary tree is ";
    RevertLevelOrder(root);

    cout << endl;

    cout << "Pre order ";
    PreOrder(root);
    cout << endl;

    cout << "Post order ";
    PostOrder(root);
    cout << endl;

    getchar();

    return 0;
}
