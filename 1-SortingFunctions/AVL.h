#pragma once

class AVL {
private:
	struct Node {
		int data;
		Node* left;
		Node* right;
		int height;
	};
	Node* root;

	void Deallocate(Node*& curr);
	void DeepCopy(const AVL& copyit);

	Node* insert(int& num, Node*& curr);
	Node* remove(int num, Node*& curr);

	void Update(Node*& curr);
	Node* singleRightRotate(Node*& parent);
	Node* singleLeftRotate(Node*& parent);
	Node* doubleRightLeftRotate(Node*& x1);
	Node* doubleLeftRightRotate(Node*& x1);

	int size(Node* curr) const;
	int height(Node* curr) const;
	int getBalance(Node* curr) const;
	Node* findMax(Node* curr) const;
	void inOrder(Node* curr) const;

public:
	AVL();
	~AVL();
	AVL(const AVL&);
	AVL& operator=(const AVL&);

	void insert(int num);
	void remove(int num);

	int size() const;
	void inOrder() const;
};