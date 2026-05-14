#ifndef NODE_H
#define NODE_H

#include <string>

 
enum class NodeType {
    VAR, CONST_0, CONST_1,
    NOT, AND, OR, IMPLIES, EQUIV
};

struct Node {
    NodeType type;
    int varIndex;      
    std::string name;  
    Node *left, *right;

     
    Node(NodeType t, std::string n = "", int vIdx = -1) 
        : type(t), varIndex(vIdx), name(n), left(nullptr), right(nullptr) {}
    
     
    Node(NodeType t, Node* l, Node* r) 
        : type(t), varIndex(-1), left(l), right(r) {}
};

#endif
