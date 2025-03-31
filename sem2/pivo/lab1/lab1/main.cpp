#include <iostream>
#include <gtest/gtest.h>

using namespace std;

struct Node{
    int value;
    Node* child[4];
};

class Tree : public Node{
    
};

int main() {
    
    std::cout << "Hello, World!\n";
    return 0;
}
