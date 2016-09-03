#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Empty_0) {
    {
        EXPECT_NO_THROW(parse(R"()"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}
