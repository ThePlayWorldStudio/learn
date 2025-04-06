#ifndef TREE_H
#define TREE_H
#include <vector>

struct Node{
	int value;
	bool IsLeaf;
	Node* child[4];
	Node(int val, bool stat);
	~Node();
};

class Tree: public Node{
public:
	bool IsSame(int** matrix, int startx, int endx, int starty, int endy);

	Node* buildTree(int** matrix, int startx, int endx, int starty, int endy, int ind, int depth);
	
	void buildMatrix(Node* root, int** matrix, int startx, int endx, int starty, int endy);

	void deleteTree(Node* root);

	void printTree(Node* root, int depth);
};
#endif
