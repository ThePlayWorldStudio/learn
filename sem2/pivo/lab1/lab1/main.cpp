#include <iostream>
// #include <googletest/googlemock/include/gmock/gmock.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

TEST(Name, 1){
	ASSERT_TRUE(1 == 1);
}

TEST(Name, 2){
	ASSERT_FALSE('b' == 'b');
}

struct Node{
    int value;
    Node* child[4];
};

class Tree : public Node{
    
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
