#ifndef LOGICTOOL_H
#define LOGICTOOL_H

#include "node.h"
#include <string>

struct VarEnv {
    std::string name;
    bool value;
};

class LogicTool {
private:
    std::string formula;
    int pos;

    // Свои методы проверки символов (вместо <cctype>)
    bool isSpace(char c);
    bool isAlpha(char c);
    bool isAlnum(char c);

    std::string prepare(std::string s);
    Node* parseFormula();

public:
    Node* buildTree(std::string input);
    
    // Вместо map передаем указатель на обычный массив
    bool evaluate(Node* root, const VarEnv* env, int envSize);
    
    void deleteTree(Node* root);
    
    // Пишем уникальные переменные в обычный массив, возвращаем их количество (вместо set и vector)
    int getVariables(const std::string& s, std::string* vars, int maxVars);
};

#endif