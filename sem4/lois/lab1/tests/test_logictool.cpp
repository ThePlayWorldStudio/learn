#include <gtest/gtest.h>
#include <string>
#include "../src/logictool.h"

class LogicToolDeepTest : public ::testing::Test {
protected:
    LogicTool tool;
    Node* root = nullptr;

    void TearDown() override {
        if (root) {
            tool.deleteTree(root);
            root = nullptr;
        }
    }

    // Хелпер для захвата исключений-строк
    void ExpectError(std::string input, std::string expectedMsg) {
        try {
            root = tool.buildTree(input);
            FAIL() << "Ожидалось исключение: " << expectedMsg;
        } catch (const std::string& e) {
            EXPECT_EQ(e, expectedMsg);
        }
    }
};

// --- Тесты вспомогательных методов и парсинга символов ---
/*
TEST_F(LogicToolDeepTest, HelperMethodsCoverage) {
    // Покрываем isSpace: ' ', '\t', '\n', '\r'
    root = tool.buildTree("A \t \n \r /\\ B");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, "/\\");
    
    // Покрываем isAlnum и сложные имена переменных
    tool.deleteTree(root);
    root = tool.buildTree("Variable123");
    EXPECT_EQ(root->value, "Variable123");
}
*/
// --- Тесты парсера (Branch Coverage для parseFormula) ---

TEST_F(LogicToolDeepTest, ParserBranchCoverage) {
    // Все бинарные операторы
    root = tool.buildTree("(A/\\B)"); EXPECT_EQ(root->value, "/\\"); tool.deleteTree(root);
    root = tool.buildTree("(A\\/B)"); EXPECT_EQ(root->value, "\\/"); tool.deleteTree(root);
    root = tool.buildTree("(A->B)"); EXPECT_EQ(root->value, "->"); tool.deleteTree(root);
    root = tool.buildTree("(A~B)");  EXPECT_EQ(root->value, "~");  tool.deleteTree(root);
    
    // Вложенные отрицания
    root = tool.buildTree("!!A");
    EXPECT_EQ(root->value, "!");
    EXPECT_EQ(root->left->value, "!");
    
    root = nullptr; // Чтобы TearDown не удалил дважды
}

TEST_F(LogicToolDeepTest, ParserExceptions) {
    ExpectError("", "Пустая формула!"); //
    ExpectError("(A+B)", "Ожидался бинарный оператор после операнда"); // Неизвестный бинарный
    ExpectError("(A/\\B", "Нет закрывающей скобки ')'"); //
    ExpectError("A /\\ B", "Ошибка синтаксиса: пропущены скобки или есть лишние символы"); // Проверка pos < length
    ExpectError("!", "Неожиданный конец формулы"); // Конец после '!'
    ExpectError("(", "Неожиданный конец формулы"); // Конец после '('
    ExpectError("#", "Некорректный символ"); //
}

// --- Тесты вычислителя (evaluate) ---

TEST_F(LogicToolDeepTest, EvaluateFullCoverage) {
    VarEnv env[] = {{"A", true}, {"B", false}};
    
    // Проверка всех веток if(v == "...")
    auto check = [&](std::string f, bool expected) {
        Node* t = tool.buildTree(f);
        EXPECT_EQ(tool.evaluate(t, env, 2), expected) << "Ошибка в формуле: " << f;
        tool.deleteTree(t);
    };

    check("!A", false);      // NOT true
    check("!B", true);       // NOT false
    check("(A/\\A)", true);  // AND true true
    check("(A/\\B)", false); // AND true false
    check("(A\\/B)", true);  // OR true false
    check("(B\\/B)", false); // OR false false
    check("(A->B)", false);  // IMPLIES true false
    check("(B->A)", true);   // IMPLIES false true
    check("(A~A)", true);    // EQ true true
    check("(A~B)", false);   // EQ true false
    
    // Покрытие nullptr в evaluate
    EXPECT_FALSE(tool.evaluate(nullptr, env, 2));
}

TEST_F(LogicToolDeepTest, EvaluateUnknownVar) {
    VarEnv env[] = {{"A", true}};
    root = tool.buildTree("X");
    try {
        tool.evaluate(root, env, 1);
        FAIL() << "Должна быть ошибка переменной X";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "Неизвестная переменная X"); //
    }
}

// --- Тесты getVariables ---

TEST_F(LogicToolDeepTest, GetVariablesCoverage) {
    std::string vars[2];
    // Проверка дедупликации и лимита maxVars
    int count = tool.getVariables("(A \\/ (B /\\ A))", vars, 2);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(vars[0], "A");
    EXPECT_EQ(vars[1], "B");

    // Проверка, что не выходим за границы если переменных больше maxVars
    std::string smallVars[1];
    int countSmall = tool.getVariables("(A \\/ B)", smallVars, 1);
    EXPECT_EQ(countSmall, 1);
    EXPECT_EQ(smallVars[0], "A");
}

TEST_F(LogicToolDeepTest, DeleteTreeSafety) {
    // Покрытие if(!root) return;
    EXPECT_NO_THROW(tool.deleteTree(nullptr));
}
