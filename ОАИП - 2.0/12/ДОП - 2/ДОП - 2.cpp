#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int key;
    int a;
    int b;
    Node* left;
    Node* right;
};

Node* createNode(int key, int a, int b) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->a = a;
    newNode->b = b;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int key, int a, int b) {
    if (!root)
        return createNode(key, a, b);
    if (key < root->key)
        root->left = insert(root->left, key, a, b);
    else if (key > root->key)
        root->right = insert(root->right, key, a, b);
    return root;
}

Node* findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->a = temp->a;
        root->b = temp->b;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void findMaxSum(Node* root, int& maxSum, int& maxKey) {
    if (!root)
        return;
    int sum = root->a + root->b;
    if (sum > maxSum) {
        maxSum = sum;
        maxKey = root->key;
    }
    findMaxSum(root->left, maxSum, maxKey);
    findMaxSum(root->right, maxSum, maxKey);
}

Node* deleteMaxSumNode(Node* root) {
    if (!root)
        return root;
    int maxSum = INT_MIN, maxKey = -1;
    findMaxSum(root, maxSum, maxKey);
    return deleteNode(root, maxKey);
}

void inorder(Node* root) {
    if (!root)
        return;
    inorder(root->left);
    cout << "Key:" << root->key << " a:" << root->a << " b:" << root->b << "\n";
    inorder(root->right);
}

int main() {
    setlocale(LC_ALL, "RU");
    Node* root = nullptr;
    root = insert(root, 50, 3, 4);   // сумма = 7
    root = insert(root, 30, 7, 2);   // сумма = 9
    root = insert(root, 70, 5, 5);   // сумма = 10 (максимальная)
    root = insert(root, 20, 1, 1);   // сумма = 2
    root = insert(root, 40, 4, 3);   // сумма = 7
    root = insert(root, 60, 2, 2);   // сумма = 4
    root = insert(root, 80, 3, 3);   // сумма = 6

    cout << "До удаления (inorder):\n";
    inorder(root);

    root = deleteMaxSumNode(root);

    cout << "\nПосле удаления (inorder):\n";
    inorder(root);
    return 0;
}
