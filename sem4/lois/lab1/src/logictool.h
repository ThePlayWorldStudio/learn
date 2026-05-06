#ifndef LOGIC_FUNCTIONS_H
#define LOGIC_FUNCTIONS_H

#include "node.h"
#include <string>
#include <vector>

// Только чистые функции для работы с деревом логики
Node* buildTree(const std::string& input, std::vector<std::string>& vars);
bool evaluate(const Node* root, const std::vector<bool>& env);
void deleteTree(Node* root);

#endif
