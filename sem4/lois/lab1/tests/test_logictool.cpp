#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "src/logictool.h" // Исправлен путь к правильному заголовку

class LogicToolFuncTest : public ::testing::Test {
protected:
    Node* root = nullptr;
    std::vector<std::string> vars;

    void TearDown() override {
        if (root) {
            deleteTree(root);
            root = nullptr;
        }
        vars.clear();
    }

    // Хелпер для захвата исключений-строк
    void ExpectError(const std::string& input, const std::string& expectedMsg) {
        try {
            root = buildTree(input, vars);
            FAIL() << "Ожидалось исключение: " << expectedMsg;
        } catch (const std::string& e) {
            EXPECT_EQ(e, expectedMsg);
        }
    }

    // Хелпер для быстрого прогона вычислений
    bool EvaluateFormula(const std::string& formula, const std::vector<bool>& env) {
        root = buildTree(formula, vars);
        bool result = evaluate(root, env);
        deleteTree(root);
        root = nullptr;
        return result;
    }
};

// --- Тесты парсинга и структуры дерева ---

TEST_F(LogicToolFuncTest, ParserOperatorsCoverage) {
    // Проверка типов узлов для всех бинарных операторов
    root = buildTree("(A/\\B)", vars); EXPECT_EQ(root->type, NodeType::AND); deleteTree(root);
    root = buildTree("(A\\/B)", vars); EXPECT_EQ(root->type, NodeType::OR);  deleteTree(root);
    root = buildTree("(A->B)", vars);  EXPECT_EQ(root->type, NodeType::IMPLIES); deleteTree(root);
    root = buildTree("(A~B)",  vars);  EXPECT_EQ(root->type, NodeType::EQUIV);   deleteTree(root);
    
    // Вложенные отрицания
    root = buildTree("!!A", vars);
    EXPECT_EQ(root->type, NodeType::NOT);
    EXPECT_EQ(root->left->type, NodeType::NOT);
    
    root = nullptr; 
}

TEST_F(LogicToolFuncTest, WhitespaceHandling) {
    // Функция prepare должна успешно игнорировать любые пробелы и табы
    root = buildTree("(  A  /\\ \t B \n )", vars);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->type, NodeType::AND);
    EXPECT_EQ(vars.size(), 2);
}

TEST_F(LogicToolFuncTest, ParserExceptions) {
    ExpectError("", "Пустая формула!"); 
    ExpectError("(A+B)", "Ожидался бинарный оператор после операнда"); 
    ExpectError("(A/\\B", "Нет закрывающей скобки ')'"); 
    // Поскольку парсер строго требует скобки для бинарных операций, проверяем это:
    ExpectError("A /\\ B", "Ошибка синтаксиса: пропущены скобки или есть лишние символы"); 
    ExpectError("!", "Неожиданный конец формулы"); 
    ExpectError("#", "Некорректный символ"); 
    ExpectError("((A/\\B)", "Нет закрывающей скобки ')'");
}

// --- Тесты вычислителя (evaluate) ---

TEST_F(LogicToolFuncTest, EvaluateLogic) {
    // vars заполнится как {"A", "B", "C"}
    EXPECT_TRUE(EvaluateFormula("((A/\\B)\\/!C)", {true, true, true}));   // (T && T) || !T  => T
    EXPECT_TRUE(EvaluateFormula("((A/\\B)\\/!C)", {false, false, false})); // (F && F) || !F  => T
    EXPECT_FALSE(EvaluateFormula("((A/\\B)\\/!C)", {false, true, true}));  // (F && T) || !T  => F
}

TEST_F(LogicToolFuncTest, ComplexFormulasAndTautologies) {
    // Проверка базовых законов логики
    EXPECT_TRUE(EvaluateFormula("(A\\/!A)", {true}));  // Тавтология
    EXPECT_TRUE(EvaluateFormula("(A\\/!A)", {false})); // Тавтология
    
    EXPECT_FALSE(EvaluateFormula("(A/\\!A)", {true}));  // Противоречие
    EXPECT_FALSE(EvaluateFormula("(A/\\!A)", {false})); // Противоречие

    // Закон Де Моргана: !(A \/ B) ~ (!A /\ !B)
    EXPECT_TRUE(EvaluateFormula("(!(A\\/B)~(!A/\\!B))", {true, true}));
    EXPECT_TRUE(EvaluateFormula("(!(A\\/B)~(!A/\\!B))", {false, false}));
}

TEST_F(LogicToolFuncTest, ConstantsTest) {
    std::vector<bool> emptyEnv;
    EXPECT_TRUE(EvaluateFormula("1", emptyEnv));
    EXPECT_FALSE(EvaluateFormula("0", emptyEnv));
    
    // Выражения с константами
    EXPECT_TRUE(EvaluateFormula("(A\\/1)", {false}));
    EXPECT_FALSE(EvaluateFormula("(A/\\0)", {true}));
}

// --- Тесты сбора переменных ---

TEST_F(LogicToolFuncTest, VariableIndexing) {
    root = buildTree("(VarA \\/ (VarB /\\ VarA))", vars);
    
    ASSERT_EQ(vars.size(), 2);
    EXPECT_EQ(vars[0], "VarA");
    EXPECT_EQ(vars[1], "VarB");
    
    EXPECT_EQ(root->varIndex, -1); // У OR нет индекса переменной
    EXPECT_EQ(root->left->varIndex, 0); // VarA
    EXPECT_EQ(root->right->left->varIndex, 1); // VarB
}

TEST_F(LogicToolFuncTest, AlphanumericVariables) {
    // Проверка того, что переменные могут содержать цифры
    root = buildTree("(Signal1 /\\ In2)", vars);
    ASSERT_EQ(vars.size(), 2);
    EXPECT_EQ(vars[0], "Signal1");
    EXPECT_EQ(vars[1], "In2");
}

TEST_F(LogicToolFuncTest, MemorySafety) {
    // Проверка корректной обработки nullptr
    EXPECT_NO_THROW(deleteTree(nullptr));
    EXPECT_FALSE(evaluate(nullptr, {true, false}));
}