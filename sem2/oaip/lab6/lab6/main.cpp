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

    ~Node(){
        delete left;
        delete right;
    }

};

class Tree{
public:
    
    Node* root = nullptr;
    
    void add(int k, char s[100]){
        if(!root){
            root = new Node(k, s);
            return;
        }
        
        Node *curr = root;
        
        while(curr){
            if(k < curr->key){
                if (!curr->left) {
                    curr->left = new Node(k, s);
                    break;
                }
                curr = curr->left;
            }
            else if(k > curr->key) {
                if (!curr->right) {
                    curr->right = new Node(k, s);
                    break;
                }
                curr = curr->right;
                continue;
            }
            else {
                std::cout << "Key " << k << " already exists\n";
                return;
            }
        }
        root = balance(root);
        std::cout << "Element was added\n";
    }
    
    void updateHeight(Node* node){
        node->height = maxim(getHeight(node->left), getHeight(node->right)) + 1;
    }

    Node* balance(Node* p) // балансировка узла p
    {
        updateHeight(p);
        if( bfactor(p)==2 )
        {
            if( bfactor(p->right) < 0 )
                p->right = rotateRight(p->right);
            return rotateLeft(p);
        }
        if( bfactor(p)==-2 )
        {
            if( bfactor(p->left) > 0  )
                p->left = rotateLeft(p->left);
            return rotateRight(p);
        }
        return p; // балансировка не нужна
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
        return node? node->height: 0;
    }

    int bfactor(Node* p)
    {
	    return p? getHeight(p->right)-getHeight(p->left): 0;
    }

    Node* rotateRight(Node* p) // правый поворот вокруг p
    {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        updateHeight(p);
        updateHeight(q);
        return q;
    }
    
    Node* rotateLeft(Node* p) // левый поворот вокруг p
    {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        updateHeight(p);
        updateHeight(q);
        return q;
    }
};

int main() {
    Tree myTree;
    myTree.add(4, "SUS");
    myTree.add(3, "fes");
    myTree.add(2, "baka");
    
    
    
    return 0;
}
