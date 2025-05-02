#include <iostream>

using namespace std;

int maxim(int a, int b){
    return a>b? a: b;
}

struct Node{
    int key;
    char string[100];
    Node* left = NULL;
    Node* right = NULL;
    int height = 0;
    
    Node(int k, char s[100]){
        key = k;
        strcpy(string, s);
    }

};

class Tree: Node{
public:
    
    Node* root;
    
    void add(Node* node, int k, char s[100]){
        if(!root){
            root = new Node(k, s);
        } else {
            if(k < node->key){
                if(node->left == NULL){
                    node->left = new Node(k, s);
                } else {
                    add(node->left, k, s);
                    updateHeight(node);
                }
            } else if(k > node->key){
                if(node->right == NULL){
                    node->right = new Node(k, s);
                    updateHeight(node);
                } else {
                    add(node->right, k, s);
                }
            } else {
                cout << "key can't be same\n";
            }
            
        }
    }
    
    void updateHeight(Node* node){
        node->height = maxim(getHeight(node), getHeight(node)) + 1;
    }
    
    ~Tree(){
        
    }
    
private:
    int getMax(Node* node){
        if(node->right == NULL){
            return node->key;
        } else {
            return getMax(node->right);
        }
    }
    
    int getMin(Node* node){
        if(node->left == NULL){
            return node->key;
        } else {
            return getMin(node->left);
        }
    }
    
    int getHeight(Node* node){
        return node == NULL? -1: node->height;
    }
    
    
};

int main() {
    cout << "Hello, World!\n";
    return 0;
}
