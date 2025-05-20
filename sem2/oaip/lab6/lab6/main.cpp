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
    
    Node(int k, char s[100]){
        key = k;
        strcpy(string, s);
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
    
    int getHeight(Node* node){
        return node ? maxim(getHeight(node->left), getHeight(node->right)) + 1 : 0;
    }

    Node* balance(Node* p) // балансировка узла p
    {
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
    
    void del(int key) {
        Node *curr = root;
        Node *parent = nullptr;
        bool isLeft = false;

        while(curr && curr->key != key) {
            parent = curr;
            if(key < curr->key) {
                curr = curr->left;
                isLeft = true;
            }
            else {
                curr = curr->right;
                isLeft = false;
            }
        }

        if(!curr) {
            std::cout << "Key " << key << " not found\n";
            return;
        }
        
        if(!curr->left && !curr->right) {       // нет детей
            if(!parent) {
                root = nullptr;
            }
            else if(isLeft) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            delete curr;
        }
        else if(!curr->left || !curr->right) {  // один ребенок
            Node *child = curr->left ? curr->left : curr->right;
            if(!parent) {
                root = child;
            }
            else if(isLeft) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
            delete curr;
        }
        else {          // два ребенка
            Node *succ = curr->right;
            Node *succParent = curr;
            while(succ->left) {
                succParent = succ;
                succ = succ->left;
            }

            curr->key = succ->key;
            strncpy(curr->string, succ->string, 99);
            curr->string[99] = '\0';

            if(succParent == curr) {
                succParent->right = succ->right;
            }
            else {
                succParent->left = succ->right;
            }
            delete succ;
        }
        root = balance(root);
        std::cout << "Element was deleted\n";
    }
    
    void getMid(){
        int mid = (getMax(root)->key - getMin(root)->key)/2;
        int bef, next;
        
        Node* curr = root;
        while(curr){
            if(curr->left->key<mid && curr->right->key>mid){
                cout << curr->key << ": " << curr->string << endl;
                return;
            }
            if(curr->key > mid){
                curr = curr->left;
            } else if(curr->key < mid){
                curr = curr->right;
            }
        }
    }
    
    void Print(int k){
        cout << search(k, root)->string;
    }
    
    ~Tree(){
        clearTree();
        root = nullptr;
    }
    
private:
    Node* getMax(Node* node){
        if(node->right == NULL){
            return node;
        } else {
            return getMax(node->right);
        }
    }
    
    Node* getMin(Node* node){
        if(node->left == NULL){
            return node;
        } else {
            return getMin(node->left);
        }
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
        return q;
    }
    
    Node* rotateLeft(Node* p) // левый поворот вокруг p
    {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        return q;
    }
    
    Node* search(int k, Node* node){
        if(!node){
            cout << "element not found!\n";
            return nullptr;
        }
        if(node->key == k)  return node;
        if(k < node->key)   return search(k, node->left);
        if(k > node->key)   return search(k, node->right);
        
        return nullptr;
    }
    
    void clearTree() {
        clearRecursive(root);
        root = nullptr;
    }
    
    void clearRecursive(Node *node) {
        if(!node)   return;
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
};

int main() {
    Tree myTree;
    myTree.add(4, "SUS");
    myTree.add(3, "fes");
    myTree.add(2, "baka");
    myTree.add(10, "nan");
    myTree.add(7, "bs");
    myTree.add(1, "da");
    myTree.del(2);
    myTree.del(7);
    myTree.del(10);
    myTree.del(4);
    myTree.getMid();
    myTree.Print(2);
    
    return 0;
}
