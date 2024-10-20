#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    char color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

struct Node* rightRotate(struct Node* curr) {
    struct Node* left = curr->left;
    curr->left = left->right;
    if (curr->left != NULL)
        curr->left->parent = curr;
    left->parent = curr->parent;
    if (curr->parent == NULL)
        return left;
    else if (curr == curr->parent->left)
        curr->parent->left = left;
    else
        curr->parent->right = left;
    left->right = curr;
    curr->parent = left;
    return left;
}

struct Node* leftRotate(struct Node* curr) {
    struct Node* right = curr->right;
    curr->right = right->left;
    if (curr->right != NULL)
        curr->right->parent = curr;
    right->parent = curr->parent;
    if (curr->parent == NULL)
        return right;
    else if (curr == curr->parent->left)
        curr->parent->left = right;
    else
        curr->parent->right = right;
    right->left = curr;
    curr->parent = right;
    return right;
}

struct Node* fixviolation(struct Node* root, struct Node* p) {
    struct Node* parent = NULL;
    struct Node* grandparent = NULL;
    
    while (p != root && p->color != 'B' && p->parent->color == 'R') {
        parent = p->parent;
        grandparent = p->parent->parent;
        
        if (parent == grandparent->left) {
            struct Node* cousin = grandparent->right;
            
            if (cousin && cousin->color == 'R') {
                grandparent->color = 'R';
                parent->color = 'B';
                cousin->color = 'B';
                p = grandparent;
            } else {
                if (p == parent->right) {
                    p = parent;
                    root = leftRotate(parent);
                }
                
                parent->color = 'B';
                grandparent->color = 'R';
                root = rightRotate(grandparent);
            }
        } else {
            struct Node* cousin = grandparent->left;
            if (cousin && cousin->color == 'R') {
                grandparent->color = 'R';
                parent->color = 'B';
                cousin->color = 'B';
                p = grandparent;
            } else {
                if (p == parent->left) {
                    p = parent;
                    root = rightRotate(parent);
                }
                
                parent->color = 'B';
                grandparent->color = 'R';
                root = leftRotate(grandparent);
            }
        }
    }
    root->color = 'B';
    return root;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = 'R';
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* curr, struct Node* newNode) {
    if (curr == NULL)
        return newNode;
    
    if (newNode->data < curr->data) {
        curr->left = insert(curr->left, newNode);
        curr->left->parent = curr;
    } else if (newNode->data > curr->data) {
        curr->right = insert(curr->right, newNode);
        curr->right->parent = curr;
    }
    
    return curr;
}

void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void freeTree(struct Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct Node* root = NULL;
    
    root = insert(root, createNode(41));
    root = insert(root, createNode(22));
    root = insert(root, createNode(5));
    root = insert(root, createNode(51));
    root = insert(root, createNode(48));
    root = insert(root, createNode(29));
    root = insert(root, createNode(18));
    root = insert(root, createNode(21));
    root = insert(root, createNode(45));
    root = insert(root, createNode(3));
    
    printf("Inorder Traversal of Created Tree:\n");
    inorderTraversal(root);
    
    freeTree(root);
    
    return 0;
}

