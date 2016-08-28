#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Empty_0) {
    {
        ASSERT_TRUE(parse(R"()"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}
