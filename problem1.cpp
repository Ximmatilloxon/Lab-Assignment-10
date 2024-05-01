#include "iostream"
using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *node){
    if(node == NULL) return 0;
    return node->height;
}

int getBalanceFactor(Node *node){
    if(node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Node *newNode(int key){
    Node *node = new Node();
    node->key = key;
    node->right = NULL;
    node->left = NULL;
    node->height = 1;
    return node;
}

Node *rotateRight(Node *x){
    Node *y = x->left;
    Node *t = y->right;
    y->right = x;
    x->left = t;
    x->height = max(height(x->right), height(x->left)) + 1;
    y->height = max(height(y->right), height(y->left)) + 1;
    return y;
}

Node *rotateLeft(Node *y){
    Node *x = y->right;
    Node *t = x->left;
    x->left = y;
    y->right = t;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *insertNode(Node *node, int key){
    if(node == NULL) return newNode(key);
    if(key < node->key) node->left = insertNode(node->left, key);
    else if(key > node->key) node->right = insertNode(node->right, key);
    else return node;
    node->height = max(height(node->right), height(node->left)) + 1;
    int balanceFactor = getBalanceFactor(node);
    if(balanceFactor > 1){
        if(key < node->left->key) return rotateRight(node);
        else if(key > node->left->key){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if(balanceFactor < -1){
        if(key < node->right->key){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        } else if(key > node->right->key) return rotateLeft(node);
    }
    return node;
}

Node *nodeMinimumValue(Node *node){
    Node *temp = node;
    while (temp->left != NULL) temp = temp->left;
    return temp;
}

Node *deleteNode(Node *node, int key){
    if(node == NULL) return node;
    if(key < node->key) node->left = deleteNode(node->left, key);
    else if(key > node->key) node->right = deleteNode(node->right, key);
    else{
        if(node->right == NULL || node->left == NULL){
            Node* temp = node->left ? node->left : node->right;
            if(temp == NULL){
                temp = node;
                node = NULL;
            }else *node = *temp;
            free(temp);
        }else{
            Node *temp = nodeMinimumValue(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }
    if(node == NULL) return node;
    node->height = max(height(node->right), height(node->left)) + 1;
    int balanceFactor = getBalanceFactor(node);
    if(balanceFactor > 1){
        if(getBalanceFactor(node->left) >= 0) return rotateRight(node);
        else{
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if(balanceFactor < -1){
        if(getBalanceFactor(node->right) <= 0) return rotateLeft(node->right);
        else{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}

void printTree(Node *root) {
    if (root != nullptr) {
        cout << root->key <<" ";
        printTree(root->left);
        printTree(root->right);
    }
}

int main(){
    int n, d;
    cin >> n;
    Node *root = NULL;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        root = insertNode(root, t);
    }
    cin >> d;

    root = deleteNode(root, d);
    printTree(root);
}