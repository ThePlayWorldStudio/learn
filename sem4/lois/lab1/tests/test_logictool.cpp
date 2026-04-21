#include "../libs/googletest/googletest/include/gtest/gtest.h"
#include <string>
#include "../src/logictool.h"

// Фикстура для тестов, чтобы не дублировать создание и удаление дерева
class LogicToolTest : public ::testing::Test {
protected:
    LogicTool tool;
    Node* root = nullptr;
    VarEnv env[10]; // Массив среды с запасом

    void TearDown() override {
        tool.deleteTree(root);
        root = nullptr;
    }
};

// ==========================================
// 1. Тесты извлечения переменных (getVariables)
// ==========================================

TEST_F(LogicToolTest, GetVariables_Single) {
    std::string vars[5];
    int count = tool.getVariables("A", vars, 5);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(vars[0], "A");
}

TEST_F(LogicToolTest, GetVariables_MultipleUniqueAndDuplicates) {
    std::string vars[10];
    // Формула с дубликатами и пробелами
    int count = tool.getVariables("( var1 /\\ (var2 \\/ var1) )", vars, 10);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(vars[0], "var1");
    EXPECT_EQ(vars[1], "var2");
}

TEST_F(LogicToolTest, GetVariables_MaxLimit) {
    std::string vars[2];
    // Пытаемся извлечь 3 переменные, но лимит 2
    int count = tool.getVariables("((A /\\ B) \\/ C)", vars, 2);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(vars[0], "A");
    EXPECT_EQ(vars[1], "B");
}

// ==========================================
// 2. Тесты парсера и синтаксиса (buildTree)
// ==========================================

TEST_F(LogicToolTest, BuildTree_ValidSyntax) {
    EXPECT_NO_THROW(root = tool.buildTree("A"));
    tool.deleteTree(root);
    EXPECT_NO_THROW(root = tool.buildTree("!A"));
    tool.deleteTree(root);
    EXPECT_NO_THROW(root = tool.buildTree("(A/\\B)"));
    tool.deleteTree(root);
    EXPECT_NO_THROW(root = tool.buildTree("((A->B)~(!C))"));
}

TEST_F(LogicToolTest, BuildTree_WhitespaceIgnored) {
    EXPECT_NO_THROW(root = tool.buildTree("  ( A   /\\  B ) \t\n "));
    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root->value, "/\\");
}

// Тестируем генерацию исключений при кривом синтаксисе
TEST_F(LogicToolTest, BuildTree_Exceptions) {
    EXPECT_THROW(tool.buildTree(""), std::string);                   // Пустая формула
    EXPECT_THROW(tool.buildTree("   "), std::string);                // Только пробелы
    EXPECT_THROW(tool.buildTree("(A/\\B"), std::string);             // Нет закрывающей скобки
    EXPECT_THROW(tool.buildTree("A/\\B"), std::string);              // Нет открывающих скобок (в твоей логике они обязательны для бинарных)
    EXPECT_THROW(tool.buildTree("(A B)"), std::string);              // Нет оператора
    EXPECT_THROW(tool.buildTree("(A/\\)"), std::string);             // Нет второго операнда
    EXPECT_THROW(tool.buildTree("!"), std::string);                  // Неожиданный конец
    EXPECT_THROW(tool.buildTree("(A/\\B) C"), std::string);          // Лишние символы в конце
    EXPECT_THROW(tool.buildTree("(A + B)"), std::string);            // Некорректный символ/оператор
}

// ==========================================
// 3. Тесты вычислений логики (evaluate)
// ==========================================

TEST_F(LogicToolTest, Evaluate_Not) {
    root = tool.buildTree("!A");
    env[0] = {"A", true};
    EXPECT_FALSE(tool.evaluate(root, env, 1));
    env[0] = {"A", false};
    EXPECT_TRUE(tool.evaluate(root, env, 1));
}

TEST_F(LogicToolTest, Evaluate_And) {
    root = tool.buildTree("(A/\\B)");
    env[0] = {"A", false}; env[1] = {"B", false}; EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", false}; env[1] = {"B", true};  EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", false}; EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", true};  EXPECT_TRUE(tool.evaluate(root, env, 2));
}

TEST_F(LogicToolTest, Evaluate_Or) {
    root = tool.buildTree("(A\\/B)");
    env[0] = {"A", false}; env[1] = {"B", false}; EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", false}; env[1] = {"B", true};  EXPECT_TRUE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", false}; EXPECT_TRUE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", true};  EXPECT_TRUE(tool.evaluate(root, env, 2));
}

TEST_F(LogicToolTest, Evaluate_Imply) {
    root = tool.buildTree("(A->B)");
    env[0] = {"A", false}; env[1] = {"B", false}; EXPECT_TRUE(tool.evaluate(root, env, 2));
    env[0] = {"A", false}; env[1] = {"B", true};  EXPECT_TRUE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", false}; EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", true};  EXPECT_TRUE(tool.evaluate(root, env, 2));
}

TEST_F(LogicToolTest, Evaluate_Equiv) {
    root = tool.buildTree("(A~B)");
    env[0] = {"A", false}; env[1] = {"B", false}; EXPECT_TRUE(tool.evaluate(root, env, 2));
    env[0] = {"A", false}; env[1] = {"B", true};  EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", false}; EXPECT_FALSE(tool.evaluate(root, env, 2));
    env[0] = {"A", true};  env[1] = {"B", true};  EXPECT_TRUE(tool.evaluate(root, env, 2));
}

TEST_F(LogicToolTest, Evaluate_UnknownVariableThrows) {
    root = tool.buildTree("(A/\\B)");
    // Передаем среду, где есть только A
    env[0] = {"A", true};
    EXPECT_THROW(tool.evaluate(root, env, 1), std::string);
}

// ==========================================
// 4. Тесты управления памятью (deleteTree)
// ==========================================

TEST_F(LogicToolTest, DeleteTree_Nullptr) {
    // Просто проверяем, что вызов с nullptr не крашит программу (в твоем коде есть защита `if (!root) return;`)
    EXPECT_NO_THROW(tool.deleteTree(nullptr));
}

// Точка входа для тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}