#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "logictool.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    cout << "Введите формулу (/\\, \\/, !, ->, ~): ";
    string input;
    getline(cin, input);

    vector<string> vars; // Вектор заполнится переменными автоматически во время парсинга
    Node* root = nullptr;
    try {
        root = buildTree(input, vars);
    } catch (const string& e) {
        cout << "Ошибка: " << e << endl;
        return 1;
    }

    int varCount = vars.size();
    long long rows = 1ULL << varCount; // Используем unsigned long long для предотвращения переполнения при большом числе переменных

    cout << "\n1. СКНФ\n2. Тест\n> ";
    int mode; cin >> mode;

    if (mode == 1) {
        string sknf = "";
        bool first = true;
        vector<bool> env(varCount);

        for (long long i = 0; i < rows; i++) {
            for (int j = 0; j < varCount; j++) {
                env[j] = (i >> (varCount - j - 1)) & 1;
            }

            try {
                if (!evaluate(root, env)) {
                    if (!first) sknf += " /\\ ";
                    sknf += "(";
                    for (int j = 0; j < varCount; j++) {
                        if (j > 0) sknf += " \\/ ";
                        if (env[j]) sknf += "!" + vars[j];
                        else sknf += vars[j];
                    }
                    sknf += ")";
                    first = false;
                }
            } catch (const string& e) {
                cout << "Ошибка при вычислении: " << e << endl;
                return 1;
            }
        }
        cout << "СКНФ: " << (sknf.empty() ? "Тождественно истинна" : sknf) << endl;
    } else {
        if (rows > 0) {
            long long r = rand() % rows;
            vector<bool> env(varCount);
            
            cout << "Вычислите для: ";
            for (int j = 0; j < varCount; j++) {
                env[j] = (r >> (varCount - j - 1)) & 1;
                cout << vars[j] << "=" << env[j] << " ";
            }
            
            try {
                bool ans = evaluate(root, env);
                cout << "\nВаш ответ (0/1): ";
                int user; cin >> user;
                cout << (user == (int)ans ? "Верно!" : "Ошибка! Ответ: " + to_string(ans)) << endl;
            } catch (const string& e) {
                cout << "\nОшибка: " << e << endl;
            }
        }
    }

    deleteTree(root);
    return 0;
}
