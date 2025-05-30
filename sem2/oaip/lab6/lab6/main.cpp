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
    
    void Print(int k){
        cout << search(k, root)->string;
    }
    
    ~Tree(){
        clearTree();
        root = nullptr;
    }
    
    void printPreOrder() const {
        if(!root) {
            std::cout << "Tree is empty\n";
            return;
        }
        std::cout << " key       data\n";
        printPreOrderRecursive(root);
    }

    void printPreOrderRecursive(Node *node) const {
        if(!node)   return;
        printNode(node);
        printPreOrderRecursive(node->left);
        printPreOrderRecursive(node->right);
    }

    void printPostOrder() const {
        if(!root) {
            std::cout << "Tree is empty\n";
            return;
        }
        std::cout << " key       data\n";
        printPostOrderRecursive(root);
    }

    void printPostOrderRecursive(Node *node) const {
        if(!node)   return;
        printPostOrderRecursive(node->left);
        printPostOrderRecursive(node->right);
        printNode(node);
    }

    void printInOrder() const {
        if(!root) {
            std::cout << "Tree is empty\n";
            return;
        }
        std::cout << " key       data\n";
        printInOrderRecursive(root);
    }

    void printInOrderRecursive(Node *node) const {
        if(!node)   return;
        printInOrderRecursive(node->left);
        printNode(node);
        printInOrderRecursive(node->right);
    }
    
    void printNode(Node *node) const {
        cout << node->key << " " << node->string << '\n';
    }
    
    void MinMax(){
        swap(getMin(root)->string, getMax(root)->string);
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
    cout << "1. add;\n2. delete;\n3. print string\n4. preorder\n5. in order\n6. postorder\n7. swap min max\n8. exit\n";
    
    int iche;
    int isWork = 1;
    int key;
    char str[99];
    
    while(isWork){
        cin >> iche;
        switch (iche) {
            case 1:
                cout << "string: ";
                cin.ignore();
                cin.getline(str, 99);
                cout << "key: ";
                cin >> key;
                myTree.add(key, str);
                break;
            
            case 2:
                cout << "key: ";
                cin >> key;
                myTree.del(key);
                break;
            
            case 3:
                cout << "key: ";
                cin >> key;
                myTree.Print(key);
                break;
                
            case 4:
                myTree.printPreOrder();
                break;
                
            case 5:
                myTree.printPostOrder();
                break;
                
            case 6:
                myTree.printPostOrder();
                break;
                
            case 7:
                myTree.MinMax();
                break;
                
            case 8:
                isWork = 0;
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
