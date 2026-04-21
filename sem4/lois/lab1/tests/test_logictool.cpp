#include <gtest/gtest.h>
#include <string>
#include "../src/logictool.h"

// Фикстура для тестов: автоматически чистит память после каждого теста
class LogicToolTest : public ::testing::Test {
protected:
    LogicTool tool;
    Node* root = nullptr;

    void TearDown() override {
        tool.deleteTree(root);
        root = nullptr;
    }

    // Хелпер для проверки точного текста исключения (т.к. выбрасывается std::string)
    void ExpectError(const std::string& input, const std::string& expected_msg) {
        try {
            root = tool.buildTree(input);
            FAIL() << "Ожидалось исключение, но формула скомпилировалась";
        } catch (const std::string& e) {
            EXPECT_EQ(e, expected_msg);
        }
    }
};

// ==========================================
// 1. ТЕСТЫ ПАРСИНГА (buildTree и parseFormula)
// ==========================================

TEST_F(LogicToolTest, ParseVariablesAndSpaces) {
    // Проверка isSpace, prepare, isAlpha и isAlnum
    root = tool.buildTree(" \t\n\r ( A1 /\\ B2 ) \n");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, "/\\");
    EXPECT_EQ(root->left->value, "A1");
    EXPECT_EQ(root->right->value, "B2");
}

TEST_F(LogicToolTest, ParseUnaryOperator) {
    root = tool.buildTree("!A");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, "!");
    EXPECT_EQ(root->left->value, "A");
    EXPECT_EQ(root->right, nullptr);
}

TEST_F(LogicToolTest, ParseBinaryOperators) {
    Node* nAnd = tool.buildTree("(A/\\B)"); EXPECT_EQ(nAnd->value, "/\\"); tool.deleteTree(nAnd);
    Node* nOr  = tool.buildTree("(A\\/B)"); EXPECT_EQ(nOr->value, "\\/");  tool.deleteTree(nOr);
    Node* nImp = tool.buildTree("(A->B)"); EXPECT_EQ(nImp->value, "->"); tool.deleteTree(nImp);
    Node* nEq  = tool.buildTree("(A~B)");  EXPECT_EQ(nEq->value, "~");   tool.deleteTree(nEq);
}

// ==========================================
// 2. ТЕСТЫ ОШИБОК ПАРСИНГА (Синтаксис)
// ==========================================


// ==========================================
// 3. ТЕСТЫ ВЫЧИСЛЕНИЯ (evaluate)
// ==========================================

TEST_F(LogicToolTest, EvaluateOperators) {
    VarEnv env[] = {{"A", true}, {"B", false}};
    int envSize = 2;

    // Проверка nullptr
    EXPECT_FALSE(tool.evaluate(nullptr, env, envSize));

    // Проверка переменных
    Node* vA = tool.buildTree("A"); EXPECT_TRUE(tool.evaluate(vA, env, envSize)); tool.deleteTree(vA);
    Node* vB = tool.buildTree("B"); EXPECT_FALSE(tool.evaluate(vB, env, envSize)); tool.deleteTree(vB);

    // Проверка операций (!, /\, \/, ->, ~)
    Node* nNot = tool.buildTree("!A");     EXPECT_FALSE(tool.evaluate(nNot, env, envSize)); tool.deleteTree(nNot);
    Node* nAnd = tool.buildTree("(A/\\B)"); EXPECT_FALSE(tool.evaluate(nAnd, env, envSize)); tool.deleteTree(nAnd);
    Node* nOr  = tool.buildTree("(A\\/B)"); EXPECT_TRUE(tool.evaluate(nOr, env, envSize));  tool.deleteTree(nOr);
    Node* nImp = tool.buildTree("(A->B)"); EXPECT_FALSE(tool.evaluate(nImp, env, envSize)); tool.deleteTree(nImp);
    Node* nImp2= tool.buildTree("(B->A)"); EXPECT_TRUE(tool.evaluate(nImp2, env, envSize)); tool.deleteTree(nImp2);
    Node* nEq  = tool.buildTree("(A~B)");  EXPECT_FALSE(tool.evaluate(nEq, env, envSize));  tool.deleteTree(nEq);
    Node* nEq2 = tool.buildTree("(A~A)");  EXPECT_TRUE(tool.evaluate(nEq2, env, envSize));  tool.deleteTree(nEq2);
}

TEST_F(LogicToolTest, EvaluateUnknownVariable) {
    VarEnv env[] = {{"A", true}};
    root = tool.buildTree("C"); // Переменная C не задана в среде
    
    try {
        tool.evaluate(root, env, 1);
        FAIL() << "Ожидалась ошибка отсутствующей переменной";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "Неизвестная переменная C");
    }
}

// ==========================================
// 4. ТЕСТЫ ДОП МЕТОДОВ (getVariables и deleteTree)
// ==========================================

TEST_F(LogicToolTest, GetVariablesExtraction) {
    std::string vars[5];
    
    // Проверка извлечения и дедупликации (A встречается дважды)
    int count = tool.getVariables("((A/\\A)\\/B1)", vars, 5);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(vars[0], "A");
    EXPECT_EQ(vars[1], "B1");

    // Проверка лимита массива (maxVars = 2, хотя уникальных 3)
    int countLimit = tool.getVariables("((A/\\B)\\/C)", vars, 2);
    EXPECT_EQ(countLimit, 2);
    EXPECT_EQ(vars[0], "A");
    EXPECT_EQ(vars[1], "B");
}

TEST_F(LogicToolTest, DeleteTreeNullptrHandling) {
    // Просто проверяем, что удаление пустой ноды не крашит программу (Segfault)
    EXPECT_NO_THROW(tool.deleteTree(nullptr));
}

// Запуск всех тестов (если пишешь без CMake или кастомного main)
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
