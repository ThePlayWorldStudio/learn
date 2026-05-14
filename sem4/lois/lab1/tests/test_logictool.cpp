#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../src/logictool.h"  

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

     
    void ExpectError(const std::string& input, const std::string& expectedMsg) {
        try {
            root = buildTree(input, vars);
            FAIL() << "Ожидалось исключение: " << expectedMsg;
        } catch (const std::string& e) {
            EXPECT_EQ(e, expectedMsg);
        }
    }

     
    bool EvaluateFormula(const std::string& formula, const std::vector<bool>& env) {
        root = buildTree(formula, vars);
        bool result = evaluate(root, env);
        deleteTree(root);
        root = nullptr;
        return result;
    }
};

 

TEST_F(LogicToolFuncTest, ParserOperatorsCoverage) {
     
    root = buildTree("(A/\\B)", vars); EXPECT_EQ(root->type, NodeType::AND); deleteTree(root);
    root = buildTree("(A\\/B)", vars); EXPECT_EQ(root->type, NodeType::OR);  deleteTree(root);
    root = buildTree("(A->B)", vars);  EXPECT_EQ(root->type, NodeType::IMPLIES); deleteTree(root);
    root = buildTree("(A~B)",  vars);  EXPECT_EQ(root->type, NodeType::EQUIV);   deleteTree(root);
    
     
    root = buildTree("!!A", vars);
    EXPECT_EQ(root->type, NodeType::NOT);
    EXPECT_EQ(root->left->type, NodeType::NOT);
    
    root = nullptr; 
}

TEST_F(LogicToolFuncTest, WhitespaceHandling) {
     
    root = buildTree("(  A  /\\ \t B \n )", vars);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->type, NodeType::AND);
    EXPECT_EQ(vars.size(), 2);
}


 

TEST_F(LogicToolFuncTest, EvaluateLogic) {
     
    EXPECT_TRUE(EvaluateFormula("((A/\\B)\\/!C)", {true, true, true}));    
    EXPECT_TRUE(EvaluateFormula("((A/\\B)\\/!C)", {false, false, false}));  
    EXPECT_FALSE(EvaluateFormula("((A/\\B)\\/!C)", {false, true, true}));   
}

TEST_F(LogicToolFuncTest, ComplexFormulasAndTautologies) {
     
    EXPECT_TRUE(EvaluateFormula("(A\\/!A)", {true}));   
    EXPECT_TRUE(EvaluateFormula("(A\\/!A)", {false}));  
    
    EXPECT_FALSE(EvaluateFormula("(A/\\!A)", {true}));   
    EXPECT_FALSE(EvaluateFormula("(A/\\!A)", {false}));  

     
    EXPECT_TRUE(EvaluateFormula("(!(A\\/B)~(!A/\\!B))", {true, true}));
    EXPECT_TRUE(EvaluateFormula("(!(A\\/B)~(!A/\\!B))", {false, false}));
}

TEST_F(LogicToolFuncTest, ConstantsTest) {
    std::vector<bool> emptyEnv;
    EXPECT_TRUE(EvaluateFormula("1", emptyEnv));
    EXPECT_FALSE(EvaluateFormula("0", emptyEnv));
    
     
    EXPECT_TRUE(EvaluateFormula("(A\\/1)", {false}));
    EXPECT_FALSE(EvaluateFormula("(A/\\0)", {true}));
}

 

TEST_F(LogicToolFuncTest, VariableIndexing) {
    root = buildTree("(VarA \\/ (VarB /\\ VarA))", vars);
    
    ASSERT_EQ(vars.size(), 2);
    EXPECT_EQ(vars[0], "VarA");
    EXPECT_EQ(vars[1], "VarB");
    
    EXPECT_EQ(root->varIndex, -1);  
    EXPECT_EQ(root->left->varIndex, 0);  
    EXPECT_EQ(root->right->left->varIndex, 1);  
}

TEST_F(LogicToolFuncTest, AlphanumericVariables) {
     
    root = buildTree("(Signal1 /\\ In2)", vars);
    ASSERT_EQ(vars.size(), 2);
    EXPECT_EQ(vars[0], "Signal1");
    EXPECT_EQ(vars[1], "In2");
}

TEST_F(LogicToolFuncTest, MemorySafety) {
     
    EXPECT_NO_THROW(deleteTree(nullptr));
    EXPECT_FALSE(evaluate(nullptr, {true, false}));
}
