#ifndef BST_GUARD
#define BST_GUARD

/**************************************
Interface for a Binary Tree ADT
Author:  Judi McCuaig
October, 2012
Modfied: James Fraser (Nov 2017)
**************************************/

/**
 * Function pointer tyepdefs
 */
typedef int (*CompareFunc)(const void* a, const void* b);
typedef void (*DeleteFunc)(void* data);
typedef void (*PrintFunc)(void* data);

/*
 * Typedef the void* to make the API cleaner and more readable.
 */
typedef void* TreeDataPtr;

typedef struct binTree Tree; 

/*
 * A Single Binary Tree Node.
 * Left and Right branches
 * void* data
 */
typedef struct binTreeNode TreeNode;
struct binTreeNode{
	TreeDataPtr data;
	TreeNode * left;
	TreeNode * right;
	//TreeNode * parent; //Optional but useful
    Tree* parentTree;  //Optional but gets you access to function pointers.
};

/**
 * This is the definition of the Binary Tree.
 *
 */
struct binTree
{
	TreeNode *root;
	CompareFunc compareFunc;
	DeleteFunc deleteFunc;
	int count; 
};

/**
 * Creates a TreeNode. TreeNode children are set to NULL and data is set to the passed in data.
 * @param data - the data to be stored within the Node. 
 * @return Newly created TreeNode
 *
 */
TreeNode* createTreeNode(TreeDataPtr data);

/**
 * createBinTree allocates memory for Tree and assigned function pointers
 * @param  compare [Function pointer to Compare data in tree nodes]
 * @param  del     [Function pointer to delete data from node]
 * @return Newly created Tree
 */
Tree * createBinTree(CompareFunc compare, DeleteFunc del);

/**
 * destroyBinTree - remove all items and free memory
 * @param  toDestroy - the tree
 * @return
 */
void  destroyBinTree(Tree * toDestroy);

/**
 * Add data to a tree
 * @param theTree 
 * @param data    
 */
void addToTree(Tree * theTree, TreeDataPtr data);

/**
 * Remove data from the tree
 * @param theTree 
 * @param data    
 */
void removeFromTree(Tree * theTree, TreeDataPtr data);


/**
 * This function searches the tree for the target data
 * @param  theTree 
 * @param  data    
 * @return         NULL if fail, otherwise return data
 */
TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data );

/**
 * Get data from the root of the Tree if it exists.
 * @param  theTree 
 * @return NULL if tree is empty, otherwise return root
 */
TreeDataPtr getRootData(Tree * theTree);

/**
 * [printInOrder This function prints the tree using an inOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printInOrder(Tree * theTree, PrintFunc printData);

/**
 * [printPreOrder This function prints the tree using an preOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printPreOrder(Tree * theTree, PrintFunc printData);

/**
 * [printPostOrder This function prints the tree using an postOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printPostOrder(Tree * theTree, PrintFunc printData);

/**
 * Checks if a tree is empty
 * @param  theTee [description]
 * @return        0 if false, 1 otherwise
 */
int isTreeEmpty(Tree* theTee);


/**
 * Helper function for checking if a single node is a leaf (no children)
 * @param  treeNode [description]
 * @return          0 if false, 1 otherwise
 */
int isLeaf( TreeNode * treeNode);

/**
 * Helper funciton for checking if a single node has two children.
 * @param  treeNode [description]
 * @return         0 if false, 1 otherwise
 */
int hasTwoChildren( TreeNode *treeNode);

/**
 * Helper funciton Get the height of a particulat Node in the tree. 
 * @param  treeNode [description]
 * @return    (1-Based) heigh for the tree. 
 */
int getHeight( TreeNode* treeNode );

/**
 * Function gets maximum value of two integers.   
 * @param Integer one to compare. 
 * @param Integer two to compare.
 * @return Integer one or two, whichever is larger, returns integer two if they are equal. 
 */
int getMax (int a, int b);

/**
 * Recursive function to display nodes in order.   
 * @param Root node of the tree to print.  
 * @param Function pointer to the print user defined function.
 */
void displayInOrder (TreeNode *root, PrintFunc print); 

/**
 * Recursive function to display nodes in pre order.   
 * @param Root node of the tree to print.  
 * @param Function pointer to the print user defined function.
 */
void displayPreOrder (TreeNode *root, PrintFunc print);


/**
 * Recursive function to display nodes in post order.   
 * @param Root node of the tree to print.  
 * @param Function pointer to the print user defined function.
 */
void displayPostOrder (TreeNode *root, PrintFunc print);

/**
 * Recursive funtion determines location to insert node, and adds it to tree.   
 * @param Current node being inserted.
 * @param Data to be inserted into the node. 
 * @param The tree to insert the node into.
 * @return Pointer to the new node made. 
 */
TreeNode *insertToTree (TreeNode *currentNode, TreeDataPtr data, Tree * theTree);

/**
 * Recursive funtion determines location to retrieve the data being searched for.   
 * @param Current node being searched.
 * @param Data being searched for. 
 * @param The tree being searched through.
 * @return Pointer to the void data found, NULL otherwise.  
 */
TreeDataPtr retrieve (TreeNode *currentNode, TreeDataPtr data, Tree *theTree); 

/**
 * Recursive function to free all nodes and set them to NULL.    
 * @param Current node being deleted.
 * @param The tree being destroyed.
 */
void destroyTree (TreeNode *currentNode, Tree *theTree); 

/**
 * Recursive function determines location of the node being searched for and removes it.   
 * @param Current node being searched.
 * @param Data being searched for. 
 * @param The tree being searched through.
 * @param Integer to check if node being deleted has two children. 1 if the node has two children, 0 otherwise. 
 * @return Pointer to the node deleted.  
 */
TreeNode *destroyNode (TreeNode *currentNode, TreeDataPtr data, Tree *theTree, int hasTwoChildren);

/**
 * Function iterates to the left-most node and returns it.    
 * @param Root node to start searching at.
 * @return Pointer to the minimum node.
 */
TreeNode *getMinimumValue (TreeNode *node);

#endif
