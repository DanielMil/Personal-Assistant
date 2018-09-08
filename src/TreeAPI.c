#include <stdio.h>
#include <stdlib.h>
#include "../include/TreeAPI.h"

TreeNode* createTreeNode(TreeDataPtr data) {

	TreeNode *node = malloc(sizeof(TreeNode));

	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parentTree = NULL; 

	return node;
}


Tree * createBinTree(CompareFunc compare, DeleteFunc del) {

	Tree *newTree = malloc(sizeof(Tree));

	newTree->root = NULL;
	newTree->compareFunc = compare; 
	newTree->deleteFunc = del;
	newTree->count = 0; 

	return newTree;
}


void destroyBinTree(Tree * toDestroy) {

	destroyTree(toDestroy->root, toDestroy);
	free(toDestroy);
	toDestroy = NULL;
}


void destroyTree (TreeNode *root, Tree *theTree) {

	if (root) {
		destroyTree(root->left, theTree);
		destroyTree(root->right, theTree);
		theTree->deleteFunc(root->data);
	}
}

void addToTree(Tree * theTree, TreeDataPtr data) {

	if (findInTree(theTree, data) != NULL) {
		return; 
	}

	theTree->root = insertToTree(theTree->root, data, theTree); 
	theTree->count++;  
}

TreeNode *insertToTree (TreeNode *currentNode, TreeDataPtr data, Tree * theTree) {

	if (!currentNode) 
		return createTreeNode(data);
	if (theTree->compareFunc(currentNode->data, data) > 0) 
		currentNode->right = insertToTree(currentNode->right, data, theTree);
	else if (theTree->compareFunc(currentNode->data, data) < 0)
		currentNode->left = insertToTree(currentNode->left, data, theTree);
	return currentNode; 
}

void removeFromTree(Tree * theTree, TreeDataPtr data) {

	theTree->root = destroyNode(theTree->root, data, theTree, 0);
}

TreeNode *destroyNode (TreeNode *currentNode, TreeDataPtr data, Tree *theTree, int hasTwoChildren) {

	if (currentNode == NULL) 
		return currentNode;

	if (theTree->compareFunc(currentNode->data, data) > 0){

		if (hasTwoChildren == 1)
			currentNode->right = destroyNode(currentNode->right, data, theTree, 1);
		else 
			currentNode->right = destroyNode(currentNode->right, data, theTree, 0);

	} else if (theTree->compareFunc(currentNode->data, data) < 0){

		if (hasTwoChildren == 1)
			currentNode->left = destroyNode(currentNode->left, data, theTree, 1);
		else
			currentNode->left = destroyNode(currentNode->left, data, theTree, 0);

	}else {

		if (isLeaf(currentNode) == 1) {

			if (hasTwoChildren == 0)
				theTree->deleteFunc(currentNode->data);
			
			free(currentNode);
			currentNode = NULL;
			theTree->count--;
			return currentNode;
	
		} else if (currentNode->left == NULL) {
			
			TreeNode *temp = currentNode;
			currentNode = currentNode->right;
			theTree->deleteFunc(temp->data);
			free(temp);
			temp = NULL; 
			theTree->count--;
			return currentNode; 
	
		} else if (currentNode->right == NULL) {
			
			TreeNode *temp = currentNode;
			currentNode = currentNode->left;
			theTree->deleteFunc(temp->data);
			free(temp);
			temp = NULL; 
			theTree->count--; 
			return currentNode;
		
		}else {
 
			TreeNode *temp = getMinimumValue(currentNode->right); 
			theTree->deleteFunc(currentNode->data); 
			currentNode->data = temp->data;

			destroyNode(currentNode->right, temp->data, theTree, 1); 
		}
	}

	return currentNode; 
}

TreeNode *getMinimumValue (TreeNode *node) {

	while (node->left) {
		node = node->left;
	}

	return node;
}

TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data ) {
	
	return retrieve(theTree->root, data, theTree);
}

TreeDataPtr retrieve (TreeNode *currentNode, TreeDataPtr data, Tree *theTree) {

	if (!currentNode) 
		return NULL;
	if (theTree->compareFunc(currentNode->data, data) == 0)
		return currentNode->data;
	else if (theTree->compareFunc(currentNode->data, data) > 0) 
		return retrieve(currentNode->right, data, theTree);
	else 
		return retrieve(currentNode->left, data, theTree);  
}

TreeDataPtr getRootData(Tree * theTree) {

	return theTree->root->data; 
}

void printInOrder(Tree * theTree, PrintFunc printData) {

	displayInOrder(theTree->root, printData);
}

void displayInOrder (TreeNode *root, PrintFunc print) {

	if (root) {
		displayInOrder(root->left, print);
		print(root->data);
		displayInOrder(root->right, print);
	}
}


void printPreOrder(Tree * theTree, PrintFunc printData) {

	displayPreOrder(theTree->root, printData);
}

void displayPreOrder (TreeNode *root, PrintFunc print) {

	if (root) {
		displayPreOrder(root->left, print);
		displayPreOrder(root->right, print);
		print(root->data);
	}
}

void printPostOrder(Tree * theTree, PrintFunc printData) {

	displayPostOrder(theTree->root, printData);
}

void displayPostOrder (TreeNode *root, PrintFunc print) {

	if (root) {
		print(root->data);
		displayPostOrder(root->left, print);
		displayPostOrder(root->right, print);
	}
}

int isTreeEmpty(Tree* theTree) {

	if (theTree->root == NULL)
		return 1;

	return 0; 
}


int isLeaf( TreeNode * treeNode) {

	if (treeNode->left == NULL && treeNode->right == NULL) 
			return 1;

	return 0;
}


int hasTwoChildren( TreeNode *treeNode) {

	if (treeNode->left != NULL && treeNode->right != NULL)
		return 1;

	return 0;
}


int getHeight( TreeNode* treeNode ) {

	if (treeNode ==  NULL) {
		return 0;
	}

	int left = getHeight(treeNode->left);
	int right = getHeight(treeNode->right);
	int max = getMax(left, right); 

	return max;
}

int getMax (int a, int b) {

	if (a > b)
		return a;

	return b; 
}
