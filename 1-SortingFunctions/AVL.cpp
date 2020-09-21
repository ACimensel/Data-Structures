#include <iostream>
#include <algorithm>
#include <queue>
#include "AVL.h"

// Creates a new node with the given 'num' value and inserts at bottom of tree as leaf node, calls Update() to fix heights and rotate nodes
// PRE: 'num' is not a duplicate
// POST: AVL tree property maintained after insertion, and root node returned
AVL::Node* AVL::insert(int& num, Node*& curr) 
{
	if (curr == nullptr) { curr = new Node{ num, nullptr, nullptr, 0 }; } // got to the end, insert as a leaf
	else if (num <= curr->data) { insert(num, curr->left); } // num is less than curr->data, insert in left subtree
	else if (num > curr->data) { insert(num, curr->right); } // num is greater than curr->data, insert in right subtree

	Update(curr); // update heights, and rotate nodes if needed
	return curr;
}

// Goes through the AVL tree to remove the node with data value 'num', updates nodes and rotates them if needed
// PRE: n/a
// POST: AVL tree property maintained after deletion, and root node returned
AVL::Node* AVL::remove(int num, Node*& curr) 
{
	if (curr == nullptr) { return curr; }
	else if (num < curr->data) { remove(num, curr->left); }
	else if (num > curr->data) { remove(num, curr->right); }
	else if (curr->left && curr->right) { // node to remove has 2 children
		curr->data = findMax(curr->left)->data; // find the largest value of the left subtree and set current value equal to it
		remove(curr->data, curr->left); // find that same value in left subtree and remove it, it will be a leaf node this time
	}
	else { // node to remove only has 1 or 0 children
		Node* del = curr; // keep track of the node to delete
		curr = (curr->left) ? curr->left : curr->right; // make curr node point to the child which is not a nullptr
		delete del;
	}

	Update(curr); // update heights, and rotate nodes if needed
	return curr;
}

// Rotates nodes if there are balance factor imbalances, then updates the heights
// PRE: n/a
// POST: maintains the AVL tree property
void AVL::Update(Node*& curr) 
{
	if (curr == nullptr) { return; }
	else if (getBalance(curr) > 1) { // subtree is left heavy
		if (height(curr->left->left) >= height(curr->left->right)) { singleRightRotate(curr); } // if the left left subtree height is greater we do single right rotation
		else { doubleLeftRightRotate(curr); } // if left right subtree height is greater then a double rotation (left right) needs to be done
	}
	else if (getBalance(curr) < -1) { // subtree is right heavy
		if (height(curr->right->right) >= height(curr->right->left)) { singleLeftRotate(curr); } // if the right right subtree height is greater we do single left rotation
		else { doubleRightLeftRotate(curr); } // if right left subtree height is greater then a double rotation (right left) needs to be done
	}

	curr->height = std::max(height(curr->left), height(curr->right)) + 1; // update height after completing needed rotations
}

// Does a single right rotation of parent with its left child
// PRE: Update() function sent the correct node to rotate, no checks are done here
// POST: Pointers are moved correctly and nothing is leaked or lost. New head node returned
AVL::Node* AVL::singleRightRotate(Node*& parent) // rotate parent with left child
{
	Node* leftChild = parent->left;
	parent->left = leftChild->right;
	leftChild->right = parent; // becomes the new parent

	parent->height = std::max(height(parent->left), height(parent->right)) + 1; // parent is the new child, update its height first
	leftChild->height = std::max(height(leftChild->left), parent->height) + 1; // leftChild is the new parent, update its height second

	parent = leftChild; // fix ptr
	return parent;
}

// Does a single left rotation of parent with its right child
// PRE: Update() function sent the correct node to rotate, no checks are done here
// POST: Pointers are moved correctly and nothing is leaked or lost. New head node returned
AVL::Node* AVL::singleLeftRotate(Node*& parent) // rotate parent with left child
{
	Node* rightChild = parent->right;
	parent->right = rightChild->left;
	rightChild->left = parent; // becomes the new parent

	parent->height = std::max(height(parent->left), height(parent->right)) + 1; // parent is the new child, update its height first
	rightChild->height = std::max(parent->height, height(rightChild->right)) + 1; // rightChild is the new parent, update its height second

	parent = rightChild; // fix ptr
	return parent;
}

/*    x1
	 /  \
		 x2     // single right rotation with x2 and x3, then left rotate x1 and x3
		/  \
	   x3    	*/
// Does a double RL rotation
// PRE: Update() function sent the correct node to rotate, no checks are done here
// POST: Nodes are moved correctly and nothing is leaked or lost, tree is balanced. New head node returned
AVL::Node* AVL::doubleRightLeftRotate(Node*& x1) 
{
	singleRightRotate(x1->right);
	return singleLeftRotate(x1);
}

/*    x1
	 /  \
	x2			// single left rotation with x2 and x3, then right rotate x1 and x3
   /  \
	   x3		*/
// Does a double LR rotation
// PRE: Update() function sent the correct node to rotate, no checks are done here
// POST: Nodes are moved correctly and nothing is leaked or lost, tree is balanced. New head node returned
AVL::Node* AVL::doubleLeftRightRotate(Node*& x1) 
{
	singleLeftRotate(x1->left);
	return singleRightRotate(x1);
}

// Returns the height of the node passed in, -1 if nullptr
// PRE: Heights are maintained properly by the Update() function
// POST: Returns the 'height' value of the passed in node, -1 if nullptr
int AVL::height(Node* curr) const
{ 
	return (curr == nullptr) ? -1 : curr->height; 
}

// Returns the balance factor of the node passed in, 0 if nullptr
// PRE: Heights are maintained properly by the Update() function
// POST: Returns difference in height of the left and right subtrees, 0 if the current node is a nullptr
int AVL::getBalance(Node* curr) const
{
	return (curr == nullptr) ? 0 : height(curr->left) - height(curr->right); 
}

// Finds the node with the maximum value in the tree by going as right as possible iteratively
// PRE: Assumes that the tree is properly ordered as a BST
// POST: Returns the node ptr of the node with the maximum value
AVL::Node* AVL::findMax(Node* curr) const
{
	if (curr == nullptr) { return nullptr; }
	while (curr->right != nullptr) { curr = curr->right; }
	return curr;
}

// Default constructor
AVL::AVL() : root{ nullptr } 
{
}

// Copy constructor, calls DeepCopy() function to deep copy each element in 'copyit' AVL
AVL::AVL(const AVL& copyit) : root{ nullptr }
{
	DeepCopy(copyit);
}

// Default destructor, calls recursive destructor() function
AVL::~AVL() 
{
	Deallocate(root);
}

// Assignment operator which checks for self reference, deallocates old nodes, and deep copies new nodes in correct positions
// PRE: that the AVL tree passed in is not itself, which is checked for
// POST: the dynamic memory of old nodes deallocated, and 'copyit' elements deep copied into the same positions in new tree
AVL& AVL::operator=(const AVL& copyit)
{
	// return if trying to assign itself. we do not want '*this' AVL to deallocate itself and then fail to deep copy
	if (this == &copyit) { return *this; }

	Deallocate(root);
	DeepCopy(copyit);

	return *this;
}

// Recursive deallocate function, calls itself on its children until it reaches leaves, deletes them, then goes up the stack to delete
// PRE: tree not large enough to cause stack overflow
// POST: all dynamic memory cleared and not leaked
void AVL::Deallocate(Node*& curr)
{
	if (curr == nullptr) { return; }
	Deallocate(curr->left);
	Deallocate(curr->right);
	delete curr;
	curr = nullptr;
}

// Iteratively deep copies elements from 'copyit' to '*this' AVL using a queue and level order traversal to maintain same order of nodes
// PRE: 'copyit' is not empty, otherwise return
// POST: copied values must be in same position on the new tree
void AVL::DeepCopy(const AVL& copyit)
{
	if (copyit.root == nullptr) { return; }

	std::queue<Node*> lvlTravQ;
	lvlTravQ.push(copyit.root);

	while (!lvlTravQ.empty()) {
		Node* tmp = lvlTravQ.front();
		if (tmp->left) { lvlTravQ.push(tmp->left); }
		if (tmp->right) { lvlTravQ.push(tmp->right); }

		insert(tmp->data);
		lvlTravQ.pop(); // pop front node
	}
}

// Calls helper function
// PRE: num is not a duplicate
// POST: num is inserted into AVL tree, tree is balanced, and heights updated
void AVL::insert(int num) 
{ 
	insert(num, root); 
}

// Calls helper function
// PRE: n/a
// POST: num is removed if it exists, tree is balanced, heights updated
void AVL::remove(int num) 
{ 
	remove(num, root); 
}

// Recursive function to get the number of nodes in the tree/subtree
// PRE: tree not large enough to cause stack overflow
// POST: Number of nodes is returned
int AVL::size(Node* curr) const
{
	return (!curr) ? 0 : 1 + size(curr->left) + size(curr->right);
}

// Calls helper function
// PRE: n/a
// POST: returned number of nodes should not overflow
int AVL::size() const
{ 
	return size(root); 
}

// Recursively prints the data component of each node in inorder
// PRE: tree not large enough to cause stack overflow
// POST: prints the data in each nodes in inorder
void AVL::inOrder(Node* curr) const
{
	if (curr == nullptr) { return; }
	inOrder(curr->left);
	std::cout << curr->data << '\n';
	inOrder(curr->right);
}

// Calls helper function
// PRE: n/a
// POST: prints the data portion of the nodes in in-order
void AVL::inOrder() const
{
	inOrder(root);
	std::cout << '\n';
}