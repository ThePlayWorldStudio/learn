#ifndef LOGIC_FUNCTIONS_H
#define LOGIC_FUNCTIONS_H

#include "node.h"
#include <string>
#include <vector>

 
Node* buildTree(const std::string& input, std::vector<std::string>& vars);
bool evaluate(const Node* root, const std::vector<bool>& env);
void deleteTree(Node* root);

#endif
