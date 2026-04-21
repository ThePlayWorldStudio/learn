#include <iostream>
#include <string>
#include <ctime>
// #include <cstdlib>
#include "src/logictool.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    LogicTool tool;

    cout << "Введите формулу (/\\, \\/, !, ->, ~): ";
    string input;
    getline(cin, input);

    Node* root = nullptr;
    try {
        root = tool.buildTree(input);
    } catch (const string& e) {
        cout << "Ошибка: " << e << endl;
        return 1;
    }

    // Выделяем массив под переменные с запасом (100 точно хватит)
    const int MAX_VARS = 100;
    string vars[MAX_VARS];
    int varCount = tool.getVariables(input, vars, MAX_VARS);
    
    // Вместо pow(2, n) из <cmath> юзаем битовый сдвиг
    int rows = 1 << varCount; 

    cout << "\n1. СКНФ\n2. Тест\n> ";
    int mode; cin >> mode;

    if (mode == 1) {
        string sknf = "";
        bool first = true;
        
        // Создаем массив под среду выполнения (как аналог словаря)
        VarEnv* env = new VarEnv[varCount];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < varCount; j++) {
                env[j].name = vars[j];
                env[j].value = (i >> (varCount - j - 1)) & 1;
            }

            try {
                if (!tool.evaluate(root, env, varCount)) {
                    if (!first) sknf += " /\\ ";
                    sknf += "(";
                    for (int j = 0; j < varCount; j++) {
                        if (j > 0) sknf += " \\/ ";
                        if (env[j].value) sknf += "!" + vars[j];
                        else sknf += vars[j];
                    }
                    sknf += ")";
                    first = false;
                }
            } catch (const string& e) {
                cout << "Ошибка при вычислении: " << e << endl;
                delete[] env;
                return 1;
            }
        }
        delete[] env; // Чистим память
        cout << "СКНФ: " << (sknf.empty() ? "Тождественно истинна" : sknf) << endl;
    } else {
        int r = rand() % rows;
        VarEnv* env = new VarEnv[varCount];
        
        cout << "Вычислите для: ";
        for (int j = 0; j < varCount; j++) {
            env[j].name = vars[j];
            env[j].value = (r >> (varCount - j - 1)) & 1;
            cout << vars[j] << "=" << env[j].value << " ";
        }
        
        try {
            bool ans = tool.evaluate(root, env, varCount);
            cout << "\nВаш ответ (0/1): ";
            int user; cin >> user;
            cout << (user == (int)ans ? "Верно!" : "Ошибка! Ответ: " + to_string(ans)) << endl;
        } catch (const string& e) {
            cout << "\nОшибка: " << e << endl;
        }
        delete[] env; // Чистим память
    }

    tool.deleteTree(root);
    return 0;
}