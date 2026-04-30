#include "logictool.h"

// Ручные проверки символов
bool LogicTool::isSpace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
bool LogicTool::isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
bool LogicTool::isAlnum(char c) { return isAlpha(c) || (c >= '0' && c <= '9'); }

std::string LogicTool::prepare(std::string s) {
    std::string res = "";
    for (int i = 0; i < (int)s.length(); i++) {
        if (!isSpace(s[i])) res += s[i];
    }
    return res;
}

Node* LogicTool::buildTree(std::string input) {
    formula = prepare(input);
    pos = 0;
    if (formula.empty()) throw std::string("Пустая формула!");
    
    Node* root = parseFormula();
    
    if (pos < (int)formula.length()) {
        throw std::string("Ошибка синтаксиса: пропущены скобки или есть лишние символы");
    }
    return root;
}

Node* LogicTool::parseFormula() {
    if (pos >= (int)formula.length()) throw std::string("Неожиданный конец формулы");

    if (formula[pos] == '!') {
        pos++;
        return new Node("!", parseFormula(), nullptr);
    }

    if (formula[pos] == '(') {
        pos++;
        Node* left = parseFormula();

        std::string op = "";
        if (pos < (int)formula.length() - 1 && formula.substr(pos, 2) == "/\\") { op = "/\\"; pos += 2; }
        else if (pos < (int)formula.length() - 1 && formula.substr(pos, 2) == "\\/") { op = "\\/"; pos += 2; }
        else if (pos < (int)formula.length() - 1 && formula.substr(pos, 2) == "->") { op = "->"; pos += 2; }
        else if (pos < (int)formula.length() && formula[pos] == '~') { op = "~"; pos += 1; }
        else throw std::string("Ожидался бинарный оператор после операнда");

        Node* right = parseFormula();

        if (pos >= (int)formula.length() || formula[pos] != ')') {
            throw std::string("Нет закрывающей скобки ')'");
        }
        pos++;
        
        return new Node(op, left, right);
    }

    // Добавлена обработка констант 0 и 1
    if (formula[pos] == '0' || formula[pos] == '1') {
        std::string constVal = "";
        constVal += formula[pos++];
        return new Node(constVal);
    }

    if (isAlpha(formula[pos])) {
        std::string varName = "";
        while (pos < (int)formula.length() && isAlnum(formula[pos])) {
            varName += formula[pos++];
        }
        return new Node(varName);
    }

    throw std::string("Некорректный символ");
}

bool LogicTool::evaluate(Node* root, const VarEnv* env, int envSize) {
    if (!root) return false;
    std::string v = root->value;
    
    // Добавлены проверки на константы 1 и 0
    if (v == "1") return true;
    if (v == "0") return false;
    
    if (v == "~") return evaluate(root->left, env, envSize) == evaluate(root->right, env, envSize);
    if (v == "->") return !evaluate(root->left, env, envSize) || evaluate(root->right, env, envSize);
    if (v == "\\/") return evaluate(root->left, env, envSize) || evaluate(root->right, env, envSize);
    if (v == "/\\") return evaluate(root->left, env, envSize) && evaluate(root->right, env, envSize);
    if (v == "!") return !evaluate(root->left, env, envSize);
    
    // Линейный поиск по массиву среды (работает моментально для 10-20 переменных)
    for (int i = 0; i < envSize; i++) {
        if (env[i].name == v) {
            return env[i].value;
        }
    }
    throw std::string("Неизвестная переменная " + v);
}

void LogicTool::deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int LogicTool::getVariables(const std::string& s, std::string* vars, int maxVars) {
    int count = 0;
    std::string form = prepare(s);
    for (int i = 0; i < (int)form.length(); i++) {
        if (isAlpha(form[i])) {
            std::string varName = "";
            while (i < (int)form.length() && isAlnum(form[i])) {
                varName += form[i++];
            }
            
            // Проверяем, есть ли уже такая переменная в нашем массиве
            bool exists = false;
            for (int j = 0; j < count; j++) {
                if (vars[j] == varName) {
                    exists = true;
                    break;
                }
            }
            // Добавляем, если новая
            if (!exists && count < maxVars) {
                vars[count++] = varName;
            }
            i--; // Отыгрываем один шаг назад
        }
    }
    return count;
}