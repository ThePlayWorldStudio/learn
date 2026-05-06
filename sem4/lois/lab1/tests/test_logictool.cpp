#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../src/logic_functions.h" // Путь к новому заголовку

class LogicToolFuncTest : public ::testing::Test {
protected:
    Node* root = nullptr;
    std::vector<std::string> vars;

    void TearDown() override {
        if (root) {
            deleteTree(root);[cite: 8]
            root = nullptr;
        }
        vars.clear();
    }

    // Хелпер для захвата исключений-строк
    void ExpectError(std::string input, std::string expectedMsg) {
        try {
            root = buildTree(input, vars);[cite: 8]
            FAIL() << "Ожидалось исключение: " << expectedMsg;
        } catch (const std::string& e) {
            EXPECT_EQ(e, expectedMsg);
        }
    }
};

// --- Тесты парсинга и структуры дерева ---

TEST_F(LogicToolFuncTest, ParserOperatorsCoverage) {
    // Проверка типов узлов для всех бинарных операторов[cite: 7, 8]
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

TEST_F(LogicToolFuncTest, ParserExceptions) {
    ExpectError("", "Пустая формула!"); 
    ExpectError("(A+B)", "Ожидался бинарный оператор после операнда"); 
    ExpectError("(A/\\B", "Нет закрывающей скобки ')'"); 
    ExpectError("A /\\ B", "Ошибка синтаксиса: пропущены скобки или есть лишние символы"); 
    ExpectError("!", "Неожиданный конец формулы"); 
    ExpectError("#", "Некорректный символ"); 
}

// --- Тесты вычислителя (evaluate) ---

TEST_F(LogicToolFuncTest, EvaluateLogic) {
    // В новой версии vars заполняется при парсинге, а env — это вектор bool
    root = buildTree("((A/\\B)\\/!C)", vars);
    // Допустим vars = {"A", "B", "C"}
    
    auto check = [&](bool a, bool b, bool c) {
        std::vector<bool> env = {a, b, c};[cite: 9]
        return evaluate(root, env);[cite: 8]
    };

    EXPECT_TRUE(check(true, true, true));   // (T && T) || !T  => T
    EXPECT_TRUE(check(false, false, false)); // (F && F) || !F  => T
    EXPECT_FALSE(check(false, true, true));  // (F && T) || !T  => F
}

TEST_F(LogicToolFuncTest, ConstantsTest) {
    std::vector<bool> emptyEnv;
    Node* t1 = buildTree("1", vars);
    EXPECT_TRUE(evaluate(t1, emptyEnv));[cite: 8]
    deleteTree(t1);

    Node* t0 = buildTree("0", vars);
    EXPECT_FALSE(evaluate(t0, emptyEnv));[cite: 8]
    deleteTree(t0);
}

// --- Тесты сбора переменных ---

TEST_F(LogicToolFuncTest, VariableIndexing) {
    // Проверка, что индексы назначаются корректно
    root = buildTree("(VarA \\/ (VarB /\\ VarA))", vars);
    
    ASSERT_EQ(vars.size(), 2);
    EXPECT_EQ(vars[0], "VarA");
    EXPECT_EQ(vars[1], "VarB");
    
    EXPECT_EQ(root->varIndex, 0); // VarA
    EXPECT_EQ(root->right->left->varIndex, 1); // VarB
}

TEST_F(LogicToolFuncTest, MemorySafety) {
    // Проверка корректной обработки nullptr
    EXPECT_NO_THROW(deleteTree(nullptr));
    EXPECT_FALSE(evaluate(nullptr, {true, false}));
}