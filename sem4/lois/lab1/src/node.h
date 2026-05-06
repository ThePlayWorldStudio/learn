#ifndef NODE_H
#define NODE_H

#include <string>

// Используем enum для мгновенной идентификации операции
enum class NodeType {
    VAR, CONST_0, CONST_1,
    NOT, AND, OR, IMPLIES, EQUIV
};

struct Node {
    NodeType type;
    int varIndex;     // Индекс переменной для быстрого доступа O(1)
    std::string name; // Имя оставляем только для VAR (если нужно при отладке)
    Node *left, *right;

    // Конструктор для переменных и констант
    Node(NodeType t, std::string n = "", int vIdx = -1) 
        : type(t), varIndex(vIdx), name(n), left(nullptr), right(nullptr) {}
    
    // Конструктор для бинарных операций
    Node(NodeType t, Node* l, Node* r) 
        : type(t), varIndex(-1), left(l), right(r) {}
};

#endif
