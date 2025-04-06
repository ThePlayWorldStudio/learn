#include "../libs/Tree.h"
#include <iostream>
using namespace std;

Node::~Node (){
	for(int i = 0; i<4; i++)
		delete[] child[i];
	
}


Node::Node (int val, bool stat){
	Node::value = val;
	Node::IsLeaf = stat;
	for(int i = 0; i<4; i++)
		Node::child[i]=nullptr;
}

bool Tree::IsSame (int** matrix, int startx, int endx, int starty, int endy){
	int value = matrix[startx][starty];
	for(int i = 0; i<endx; i++){
		for(int j = 0; j<endy; j++){
			if(matrix[i][j]!=value)
				return false;
			
		}
	}
	return true;
}
Node* Tree::buildTree (int** matrix, int startx, int endx, int starty, int endy, int ind, int depth){
	for(int i = 0; i<depth; i++)
		cout << " ";
	
	cout << "depth: " << depth << " " << ind;
	if(IsSame(matrix, startx, endx, starty, endy)){
		cout << "Same, val = " << matrix[startx][starty];
		return new Node(matrix[startx][starty], true);
	}

	cout << "not same, devides/n"; 
	
	int midx = (startx + endx)/2;
	int midy = (starty + endy)/2;

	Node* node = new Node(0, false);
	node->child[0] = buildTree(matrix, startx, midx, starty, midy, ind, ind+1);
	node->child[1] = buildTree(matrix, startx, midx, midy, endy, ind, ind+1);
	node->child[2] = buildTree(matrix, midx, endx, midy, endy, ind, ind+1);
	node->child[3] = buildTree(matrix, midx, endx, starty, midy, ind, ind+1);
	return node;	
}

void Tree::buildMatrix (Node* root, int** matrix, int startx, int endx, int starty, int endy){
	if(root->IsLeaf){
		for(int i = startx; i<endx; i++){
			for(int j = starty; j<endy; j++){
				matrix[i][j] = root->value;
			}
		}
		return;
	}
	 
	int midx = (startx+endx)/2;
	int midy = (starty+endy)/2;

	buildMatrix(root->child[0], matrix, startx, midx, starty, midy);
	buildMatrix(root->child[1], matrix, startx, midx, midy, endy);
	buildMatrix(root->child[2], matrix, midx, endx, midy, endy);
	buildMatrix(root->child[3], matrix, midx, endx, starty, midy);
}

void Tree::deleteTree (Node* root){
	if(root == nullptr) return;
	delete root;
}

void Tree::printTree (Node* root, int depth){
	if(!root) return;

	for(int i = 0; i < depth; i++)
		cout << " ";
	if(root->IsLeaf){
		cout << "leaf: value - " << root->value << endl;
	}else{
		cout << "node ddevided\n";

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "1: \n";
		printTree(root->child[0], depth+2);

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "2: \n";
		printTree(root->child[1], depth+2);

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "3: \n";
		printTree(root->child[2], depth+2);

		for(int i = 0; i<depth+1; i++) 
			cout << " ";
		cout << "4: \n";
		printTree(root->child[3], depth+2);
	}
}

