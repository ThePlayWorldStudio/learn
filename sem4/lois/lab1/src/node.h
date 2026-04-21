#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
    std::string value;
    Node *left, *right;

    Node(std::string val) : value(val), left(nullptr), right(nullptr) {}
    Node(std::string val, Node* l, Node* r) : value(val), left(l), right(r) {}
};

#endif