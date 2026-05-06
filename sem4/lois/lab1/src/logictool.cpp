#include "logictool.h"
#include <algorithm>
#include <stdexcept>

namespace { // Анонимное пространство имен для скрытия вспомогательных функций
    bool isSpace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
    bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
    bool isAlnum(char c) { return isAlpha(c) || (c >= '0' && c <= '9'); }

    std::string prepare(const std::string& s) {
        std::string res;
        res.reserve(s.length()); // Резервируем память, чтобы избежать реаллокаций
        for (char c : s) {
            if (!isSpace(c)) res += c;
        }
        return res;
    }

    // Возвращает индекс переменной (существующий или новый)
    int getVarIndex(const std::string& name, std::vector<std::string>& vars) {
        auto it = std::find(vars.begin(), vars.end(), name);
        if (it != vars.end()) {
            return std::distance(vars.begin(), it);
        }
        vars.push_back(name);
        return vars.size() - 1;
    }

    Node* parseFormula(const std::string& formula, int& pos, std::vector<std::string>& vars) {
        if (pos >= (int)formula.length()) throw std::string("Неожиданный конец формулы");

        if (formula[pos] == '!') {
            pos++;
            return new Node(NodeType::NOT, parseFormula(formula, pos, vars), nullptr);
        }

        if (formula[pos] == '(') {
            pos++;
            Node* left = parseFormula(formula, pos, vars);

            NodeType opType;
            if (pos < (int)formula.length() - 1 && formula.substr(pos, 2) == "/\\") { opType = NodeType::AND; pos += 2; }
            else if (pos < (int)formula.length() - 1 && formula.substr(pos, 2) == "\\/") { opType = NodeType::OR; pos += 2; }
            else if (pos < (int)formula.length() - 1 && formula.substr(pos, 2) == "->") { opType = NodeType::IMPLIES; pos += 2; }
            else if (pos < (int)formula.length() && formula[pos] == '~') { opType = NodeType::EQUIV; pos += 1; }
            else throw std::string("Ожидался бинарный оператор после операнда");

            Node* right = parseFormula(formula, pos, vars);

            if (pos >= (int)formula.length() || formula[pos] != ')') {
                throw std::string("Нет закрывающей скобки ')'");
            }
            pos++;
            
            return new Node(opType, left, right);
        }

        if (formula[pos] == '0') { pos++; return new Node(NodeType::CONST_0); }
        if (formula[pos] == '1') { pos++; return new Node(NodeType::CONST_1); }

        if (isAlpha(formula[pos])) {
            std::string varName = "";
            while (pos < (int)formula.length() && isAlnum(formula[pos])) {
                varName += formula[pos++];
            }
            int idx = getVarIndex(varName, vars); // Сразу получаем O(1) индекс
            return new Node(NodeType::VAR, varName, idx);
        }

        throw std::string("Некорректный символ");
    }
}

Node* buildTree(const std::string& input, std::vector<std::string>& vars) {
    std::string formula = prepare(input);
    int pos = 0;
    if (formula.empty()) throw std::string("Пустая формула!");
    
    Node* root = parseFormula(formula, pos, vars);
    
    if (pos < (int)formula.length()) {
        throw std::string("Ошибка синтаксиса: пропущены скобки или есть лишние символы");
    }
    return root;
}

// Теперь вычисление работает в десятки раз быстрее благодаря switch(enum) и быстрому доступу к вектору
bool evaluate(const Node* root, const std::vector<bool>& env) {
    if (!root) return false;
    
    switch(root->type) {
        case NodeType::CONST_1: return true;
        case NodeType::CONST_0: return false;
        case NodeType::VAR:     return env[root->varIndex];
        case NodeType::NOT:     return !evaluate(root->left, env);
        case NodeType::AND:     return evaluate(root->left, env) && evaluate(root->right, env);
        case NodeType::OR:      return evaluate(root->left, env) || evaluate(root->right, env);
        case NodeType::IMPLIES: return !evaluate(root->left, env) || evaluate(root->right, env);
        case NodeType::EQUIV:   return evaluate(root->left, env) == evaluate(root->right, env);
    }
    return false;
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
