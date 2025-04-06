#include <iostream>
// #include <googletest/googlemock/include/gmock/gmock.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../libs/Tree.h"

using namespace std;

TEST(net, 1){
	Tree tree;
	ASSERT_TRUE(tree.add(10) == 12);
};


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
   	return RUN_ALL_TESTS();
}
