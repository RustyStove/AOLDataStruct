#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int num;
	int height;
	Node* right;
	Node* left;
};

int getHeight(Node* newNode){
	if(newNode == NULL){
		return 0;
	}
	
	return newNode->height;
}

//max value from height children
int getMax(int a, int b){
	if(a < b){
		return b;
	}
	return a;
}

int getBalancedFactor(Node* newNode){
	if(newNode == NULL){
		return 0;
	}
	
	return getHeight(newNode->left) - getHeight(newNode->right);
}

Node* createNode(int num){
	Node* newNode= (Node*) malloc(sizeof(Node));
	
	newNode->num = num;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

Node* leftRotate(Node* node){
	Node* right = node->right;
	Node* rightLeft = right->left;
	
	right->left = node;
	node->right = rightLeft;
	
	node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
	
	right->height = getMax(getHeight(right->left), getHeight(right->right)) + 1;
	
	return right;
}

Node* rightRotate(Node* node){
	Node* left = node->left;
	Node* leftRight = left->right;
	
	left->right = node;
	node->left = leftRight;
	
	node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
	
	left->height = getMax(getHeight(left->left), getHeight(left->right)) + 1;
	
	return left;
}

Node* insertNode(Node* root, Node* newNode){
	if(root==NULL){
		return newNode;
	}
	
	if(newNode->num < root->num){
		root->left = insertNode(root->left,newNode);
	}else if (newNode->num >= root->num){
		root->right = insertNode(root->right,newNode);
	}else{
		return root;
	}
 
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
		
	//height from root
	root->height = getMax(leftHeight,rightHeight) + 1;
		
	int bf = getBalancedFactor(root);
	
	//left
	if(bf < -1  && getBalancedFactor(root->right) <= 0){
		return leftRotate(root);
		
	//left right	
	}else if(bf < -1 && getBalancedFactor(root->left) < 0){
		newNode->left = leftRotate(root);
		return rightRotate(root);
		
	//right	
	} else if (bf > 1  && getBalancedFactor(root->left) >= 0){
		return rightRotate(root);
		
	//right left	
	}else if(bf < -1 && getBalancedFactor(root->right) > 0){
		rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Node* popAll(Node* root){
	if(!root){
		return root;
	}else{
		root->left = popAll(root->left);
		root->right = popAll(root->right);
		
		root->left = NULL;
		root->right = NULL;
		
		free(root);
		root = NULL;
	}
	return root;
}

Node* popNode(Node* root, int num){
	if(!root){
		printf("Not found\n");
		return root;
	}else if(num < root->num){
		root->left = popNode(root->left,num);
		
	}else if(num > root->num){
		root->right = popNode(root->right,num);
		
	}else if(num == root->num){
		if(!root->left && !root->right){
			free(root);
			root = NULL;
		}else if(root->left && !root->right){
			Node* temp = root->left;
			free(root);
			root = temp;
		}else if(!root->left && root->right){
			Node* temp = root->right;
			free(root);
			root = temp;
		}else if(root->left && root->right){
			Node* temp = root->left;
			while(temp->right){
				temp = temp->right;
			}
			
			root->num = temp->num;
			
			root->left = popNode(root->left, temp->num);
		}
	}
	if(!root){
		return root;
	}
	
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
		
	//height from root
	root->height = getMax(leftHeight,rightHeight) + 1;
		
	int bf = getBalancedFactor(root);
	
	//left
	if(bf < -1  && getBalancedFactor(root->right) <= 0){
		return leftRotate(root);
		
	//left right	
	}else if(bf < -1 && getBalancedFactor(root->left) < 0){
		root->left = leftRotate(root);
		return rightRotate(root);
		
	//right	
	} else if (bf > 1  && getBalancedFactor(root->left) >= 0){
		return rightRotate(root);
		
	//right left	
	}else if(bf < -1 && getBalancedFactor(root->right) > 0){
		rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}
void printPreOrder(Node* node){
	if(node){
		printf(" %d",node->num);
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
}

void printInOrder(Node* node){
	if(node){
		printInOrder(node->left);
		printf(" %d",node->num);
		printInOrder(node->right);
	}
}

void printPostOrder(Node* node){
	if(node){
		printPostOrder(node->left);
		printPostOrder(node->right);
		printf(" %d",node->num);
	}
}

int main(){
	Node* root = NULL;
	int input = 0;
	while(input != 4){
		printf("---Menu---\n");
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		printf("Choose: ");
		scanf("%d", &input);
		
		switch(input){
			case 1:{
				int insert;
				printf("Insert: ");
				scanf("%d",&insert);
				root = insertNode(root, createNode(insert));
				printf("\n");
				break;
			}
			
			case 2:{
				int del;
				printf("Delete: ");
				scanf("%d",&del);
				root = popNode(root,del);
				printf("\n");
				break;
			}
			
			case 3:{
				printf("\nPreorder: ");
				printPreOrder(root);
				printf("\n");
				
				printf("Inorder: ");
				printInOrder(root);
				printf("\n");
				
				printf("Postorder: ");
				printPostOrder(root);
				printf("\n");
				break;
			}
			
			default:{
				printf("Choose Valid Option!\n\n");
				break;
			}
		}
	}
	
	printf("Thank You\n");
	root = popAll(root);
	return 0;
}
