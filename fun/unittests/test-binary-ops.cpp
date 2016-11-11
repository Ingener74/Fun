#include "test.h"

using namespace std;
using namespace fun;

#define CHECK_OPERAND(TYPE, N, VALUE)                              \
	ASSERT_LT(N, operands->count());                               \
    auto op_##N = operands->operand(N).cast<TYPE>();               \
    ASSERT_FALSE(op_##N.isNull());                                 \
    EXPECT_EQ(op_##N->value, VALUE);

#define CHECK_INTEGER_OPERAND(N, VALUE) CHECK_OPERAND(Integer, N, VALUE)
#define CHECK_STRING_OPERAND(N, VALUE) CHECK_OPERAND(String, N, VALUE)
#define CHECK_REAL_OPERAND(N, VALUE) CHECK_OPERAND(Real, N, VALUE)
#define CHECK_BOOLEAN_OPERAND(N, VALUE) CHECK_OPERAND(Boolean, N, VALUE)

// TODO последовательность операции, проверка приоритета

PARSE_ERR(BinaryOp, 1, R"(42 + )", ParserError);

PARSE(BinaryOp, 2, R"(42 + 42)");

PARSE(BinaryOp, 3, R"(42 + " test string")");

PARSE(BinaryOp, 4, R"(42 + nil)");

PARSE(BinaryOp, 5, R"(42 + 3.1415)");

PARSE(BinaryOp, 6, R"(42 + true)");

PARSE(BinaryOp, 7, R"(42 + false)");


PARSE(BinaryOp, 8, R"(2.72 + 42)");

PARSE(BinaryOp, 9, R"(2.72 + " test string")");

PARSE(BinaryOp, 10, R"(2.72 + nil)");

PARSE(BinaryOp, 11, R"(2.72 + 3.1415)");

PARSE(BinaryOp, 12, R"(2.72 + true)");

PARSE(BinaryOp, 13, R"(2.72 + false)");


PARSE(BinaryOp, 14, R"("Fun " + 42)");

PARSE(BinaryOp, 15, R"("Fun " + " test string")");

PARSE(BinaryOp, 16, R"("Fun " + nil)");

PARSE(BinaryOp, 17, R"("Fun " + 3.1415)");

PARSE(BinaryOp, 18, R"("Fun " + true)");

PARSE(BinaryOp, 19, R"("Fun " + false)");


PARSE(BinaryOp, 20, R"(true + true)");

PARSE(BinaryOp, 21, R"(true + " test string")");

PARSE(BinaryOp, 22, R"(true + nil)");

PARSE(BinaryOp, 23, R"(true + 3.1415)");

PARSE(BinaryOp, 24, R"(true + true)");

PARSE(BinaryOp, 25, R"(true + false)");


PARSE(BinaryOp, 26, R"(false + false)");

PARSE(BinaryOp, 27, R"(false + " test string")");

PARSE(BinaryOp, 28, R"(false + nil)");

PARSE(BinaryOp, 29, R"(false + 3.1415)");

PARSE(BinaryOp, 30, R"(false + true)");

PARSE(BinaryOp, 31, R"(false + false)");


PARSE(BinaryOp, 32, R"(nil + nil)");

PARSE(BinaryOp, 33, R"(nil + " test string")");

PARSE(BinaryOp, 34, R"(nil + nil)");

PARSE(BinaryOp, 35, R"(nil + 3.1415)");

PARSE(BinaryOp, 36, R"(nil + true)");

PARSE(BinaryOp, 37, R"(nil + nil)");




PARSE(BinaryOp, 38, R"(42 - 42)");

PARSE(BinaryOp, 39, R"(42 - " test string")");

PARSE(BinaryOp, 40, R"(42 - nil)");

PARSE(BinaryOp, 41, R"(42 - 3.1415)");

PARSE(BinaryOp, 42, R"(42 - true)");

PARSE(BinaryOp, 43, R"(42 - false)");


PARSE(BinaryOp, 44, R"(2.72 - 42)");

PARSE(BinaryOp, 45, R"(2.72 - " test string")");

PARSE(BinaryOp, 46, R"(2.72 - nil)");

PARSE(BinaryOp, 47, R"(2.72 - 3.1415)");

PARSE(BinaryOp, 48, R"(2.72 - true)");

PARSE(BinaryOp, 49, R"(2.72 - false)");


PARSE(BinaryOp, 50, R"("Fun " - 42)");

PARSE(BinaryOp, 51, R"("Fun " - " test string")");

PARSE(BinaryOp, 52, R"("Fun " - nil)");

PARSE(BinaryOp, 53, R"("Fun " - 3.1415)");

PARSE(BinaryOp, 54, R"("Fun " - true)");

PARSE(BinaryOp, 55, R"("Fun " - false)");


PARSE(BinaryOp, 56, R"(true - true)");

PARSE(BinaryOp, 57, R"(true - " test string")");

PARSE(BinaryOp, 58, R"(true - nil)");

PARSE(BinaryOp, 59, R"(true - 3.1415)");

PARSE(BinaryOp, 60, R"(true - true)");

PARSE(BinaryOp, 61, R"(true - false)");


PARSE(BinaryOp, 62, R"(false - false)");

PARSE(BinaryOp, 63, R"(false - " test string")");

PARSE(BinaryOp, 64, R"(false - nil)");

PARSE(BinaryOp, 65, R"(false - 3.1415)");

PARSE(BinaryOp, 66, R"(false - true)");

PARSE(BinaryOp, 67, R"(false - false)");


PARSE(BinaryOp, 68, R"(nil - nil)");

PARSE(BinaryOp, 69, R"(nil - " test string")");

PARSE(BinaryOp, 70, R"(nil - nil)");

PARSE(BinaryOp, 71, R"(nil - 3.1415)");

PARSE(BinaryOp, 72, R"(nil - true)");

PARSE(BinaryOp, 73, R"(nil - nil)");


PARSE(BinaryOp, 74, R"(42 * 42)");

PARSE(BinaryOp, 75, R"(42 * " test string")");

PARSE(BinaryOp, 76, R"(42 * nil)");

PARSE(BinaryOp, 77, R"(42 * 3.1415)");

PARSE(BinaryOp, 78, R"(42 * true)");

PARSE(BinaryOp, 79, R"(42 * false)");


PARSE(BinaryOp, 80, R"(2.72 * 42)");

PARSE(BinaryOp, 81, R"(2.72 * " test string")");

PARSE(BinaryOp, 82, R"(2.72 * nil)");

PARSE(BinaryOp, 83, R"(2.72 * 3.1415)");

PARSE(BinaryOp, 84, R"(2.72 * true)");

PARSE(BinaryOp, 85, R"(2.72 * false)");


PARSE(BinaryOp, 86, R"("Fun " * 42)");

PARSE(BinaryOp, 87, R"("Fun " * " test string")");

PARSE(BinaryOp, 88, R"("Fun " * nil)");

PARSE(BinaryOp, 89, R"("Fun " * 3.1415)");

PARSE(BinaryOp, 90, R"("Fun " * true)");

PARSE(BinaryOp, 91, R"("Fun " * false)");


PARSE(BinaryOp, 92, R"(true * true)");

PARSE(BinaryOp, 93, R"(true * " test string")");

PARSE(BinaryOp, 94, R"(true * nil)");

PARSE(BinaryOp, 95, R"(true * 3.1415)");

PARSE(BinaryOp, 96, R"(true * true)");

PARSE(BinaryOp, 97, R"(true * false)");


PARSE(BinaryOp, 98, R"(false * false)");

PARSE(BinaryOp, 99, R"(false * " test string")");

PARSE(BinaryOp, 100, R"(false * nil)");

PARSE(BinaryOp, 101, R"(false * 3.1415)");

PARSE(BinaryOp, 102, R"(false * true)");

PARSE(BinaryOp, 103, R"(false * false)");


PARSE(BinaryOp, 104, R"(nil * nil)");

PARSE(BinaryOp, 105, R"(nil * " test string")");

PARSE(BinaryOp, 106, R"(nil * nil)");

PARSE(BinaryOp, 107, R"(nil * 3.1415)");

PARSE(BinaryOp, 108, R"(nil * true)");

PARSE(BinaryOp, 109, R"(nil * nil)");




PARSE(BinaryOp, 110, R"(42 / 42)");

PARSE(BinaryOp, 111, R"(42 / " test string")");

PARSE(BinaryOp, 112, R"(42 / nil)");

PARSE(BinaryOp, 113, R"(42 / 3.1415)");

PARSE(BinaryOp, 114, R"(42 / true)");

PARSE(BinaryOp, 115, R"(42 / false)");


PARSE(BinaryOp, 116, R"(2.72 / 42)");

PARSE(BinaryOp, 117, R"(2.72 / " test string")");

PARSE(BinaryOp, 118, R"(2.72 / nil)");

PARSE(BinaryOp, 119, R"(2.72 / 3.1415)");

PARSE(BinaryOp, 120, R"(2.72 / true)");

PARSE(BinaryOp, 121, R"(2.72 / false)");


PARSE(BinaryOp, 122, R"("Fun " / 42)");

PARSE(BinaryOp, 123, R"("Fun " / " test string")");

PARSE(BinaryOp, 124, R"("Fun " / nil)");

PARSE(BinaryOp, 125, R"("Fun " / 3.1415)");

PARSE(BinaryOp, 126, R"("Fun " / true)");

PARSE(BinaryOp, 127, R"("Fun " / false)");


PARSE(BinaryOp, 128, R"(true / true)");

PARSE(BinaryOp, 129, R"(true / " test string")");

PARSE(BinaryOp, 130, R"(true / nil)");

PARSE(BinaryOp, 131, R"(true / 3.1415)");

PARSE(BinaryOp, 132, R"(true / true)");

PARSE(BinaryOp, 133, R"(true / false)");


PARSE(BinaryOp, 134, R"(false / false)");

PARSE(BinaryOp, 135, R"(false / " test string")");

PARSE(BinaryOp, 136, R"(false / nil)");

PARSE(BinaryOp, 137, R"(false / 3.1415)");

PARSE(BinaryOp, 138, R"(false / true)");

PARSE(BinaryOp, 139, R"(false / false)");


PARSE(BinaryOp, 140, R"(nil / nil)");

PARSE(BinaryOp, 141, R"(nil / " test string")");

PARSE(BinaryOp, 142, R"(nil / nil)");

PARSE(BinaryOp, 143, R"(nil / 3.1415)");

PARSE(BinaryOp, 144, R"(nil / true)");

PARSE(BinaryOp, 145, R"(nil / nil)");




PARSE(BinaryOp, 146, R"(42 % 42)");

PARSE(BinaryOp, 147, R"(42 % " test string")");

PARSE(BinaryOp, 148, R"(42 % nil)");

PARSE(BinaryOp, 149, R"(42 % 3.1415)");

PARSE(BinaryOp, 150, R"(42 % true)");

PARSE(BinaryOp, 151, R"(42 % false)");


PARSE(BinaryOp, 152, R"(2.72 % 42)");

PARSE(BinaryOp, 153, R"(2.72 % " test string")");

PARSE(BinaryOp, 154, R"(2.72 % nil)");

PARSE(BinaryOp, 155, R"(2.72 % 3.1415)");

PARSE(BinaryOp, 156, R"(2.72 % true)");

PARSE(BinaryOp, 157, R"(2.72 % false)");


PARSE(BinaryOp, 158, R"("Fun " % 42)");

PARSE(BinaryOp, 159, R"("Fun " % " test string")");

PARSE(BinaryOp, 160, R"("Fun " % nil)");

PARSE(BinaryOp, 161, R"("Fun " % 3.1415)");

PARSE(BinaryOp, 162, R"("Fun " % true)");

PARSE(BinaryOp, 163, R"("Fun " % false)");


PARSE(BinaryOp, 164, R"(true % true)");

PARSE(BinaryOp, 165, R"(true % " test string")");

PARSE(BinaryOp, 166, R"(true % nil)");

PARSE(BinaryOp, 167, R"(true % 3.1415)");

PARSE(BinaryOp, 168, R"(true % true)");

PARSE(BinaryOp, 169, R"(true % false)");


PARSE(BinaryOp, 170, R"(false % false)");

PARSE(BinaryOp, 171, R"(false % " test string")");

PARSE(BinaryOp, 172, R"(false % nil)");

PARSE(BinaryOp, 173, R"(false % 3.1415)");

PARSE(BinaryOp, 174, R"(false % true)");

PARSE(BinaryOp, 175, R"(false % false)");


PARSE(BinaryOp, 176, R"(nil % nil)");

PARSE(BinaryOp, 177, R"(nil % " test string")");

PARSE(BinaryOp, 178, R"(nil % nil)");

PARSE(BinaryOp, 179, R"(nil % 3.1415)");

PARSE(BinaryOp, 180, R"(nil % true)");

PARSE(BinaryOp, 181, R"(nil % nil)");




PARSE(BinaryOp, 182, R"(42 << 42)");

PARSE(BinaryOp, 183, R"(42 << " test string")");

PARSE(BinaryOp, 184, R"(42 << nil)");

PARSE(BinaryOp, 185, R"(42 << 3.1415)");

PARSE(BinaryOp, 186, R"(42 << true)");

PARSE(BinaryOp, 187, R"(42 << false)");


PARSE(BinaryOp, 188, R"(2.72 << 42)");

PARSE(BinaryOp, 189, R"(2.72 << " test string")");

PARSE(BinaryOp, 190, R"(2.72 << nil)");

PARSE(BinaryOp, 191, R"(2.72 << 3.1415)");

PARSE(BinaryOp, 192, R"(2.72 << true)");

PARSE(BinaryOp, 193, R"(2.72 << false)");


PARSE(BinaryOp, 194, R"("Fun " << 42)");

PARSE(BinaryOp, 195, R"("Fun " << " test string")");

PARSE(BinaryOp, 196, R"("Fun " << nil)");

PARSE(BinaryOp, 197, R"("Fun " << 3.1415)");

PARSE(BinaryOp, 198, R"("Fun " << true)");

PARSE(BinaryOp, 199, R"("Fun " << false)");


PARSE(BinaryOp, 200, R"(true << true)");

PARSE(BinaryOp, 201, R"(true << " test string")");

PARSE(BinaryOp, 202, R"(true << nil)");

PARSE(BinaryOp, 203, R"(true << 3.1415)");

PARSE(BinaryOp, 204, R"(true << true)");

PARSE(BinaryOp, 205, R"(true << false)");


PARSE(BinaryOp, 206, R"(false << false)");

PARSE(BinaryOp, 207, R"(false << " test string")");

PARSE(BinaryOp, 208, R"(false << nil)");

PARSE(BinaryOp, 209, R"(false << 3.1415)");

PARSE(BinaryOp, 210, R"(false << true)");

PARSE(BinaryOp, 211, R"(false << false)");


PARSE(BinaryOp, 212, R"(nil << nil)");

PARSE(BinaryOp, 213, R"(nil << " test string")");

PARSE(BinaryOp, 214, R"(nil << nil)");

PARSE(BinaryOp, 215, R"(nil << 3.1415)");

PARSE(BinaryOp, 216, R"(nil << true)");

PARSE(BinaryOp, 217, R"(nil << nil)");




PARSE(BinaryOp, 218, R"(42 >> 42)");

PARSE(BinaryOp, 219, R"(42 >> " test string")");

PARSE(BinaryOp, 220, R"(42 >> nil)");

PARSE(BinaryOp, 221, R"(42 >> 3.1415)");

PARSE(BinaryOp, 222, R"(42 >> true)");

PARSE(BinaryOp, 223, R"(42 >> false)");


PARSE(BinaryOp, 224, R"(2.72 >> 42)");

PARSE(BinaryOp, 225, R"(2.72 >> " test string")");

PARSE(BinaryOp, 226, R"(2.72 >> nil)");

PARSE(BinaryOp, 227, R"(2.72 >> 3.1415)");

PARSE(BinaryOp, 228, R"(2.72 >> true)");

PARSE(BinaryOp, 229, R"(2.72 >> false)");


PARSE(BinaryOp, 230, R"("Fun " >> 42)");

PARSE(BinaryOp, 231, R"("Fun " >> " test string")");

PARSE(BinaryOp, 232, R"("Fun " >> nil)");

PARSE(BinaryOp, 233, R"("Fun " >> 3.1415)");

PARSE(BinaryOp, 234, R"("Fun " >> true)");

PARSE(BinaryOp, 235, R"("Fun " >> false)");


PARSE(BinaryOp, 236, R"(true >> true)");

PARSE(BinaryOp, 237, R"(true >> " test string")");

PARSE(BinaryOp, 238, R"(true >> nil)");

PARSE(BinaryOp, 239, R"(true >> 3.1415)");

PARSE(BinaryOp, 240, R"(true >> true)");

PARSE(BinaryOp, 241, R"(true >> false)");


PARSE(BinaryOp, 242, R"(false >> false)");

PARSE(BinaryOp, 243, R"(false >> " test string")");

PARSE(BinaryOp, 244, R"(false >> nil)");

PARSE(BinaryOp, 245, R"(false >> 3.1415)");

PARSE(BinaryOp, 246, R"(false >> true)");

PARSE(BinaryOp, 247, R"(false >> false)");


PARSE(BinaryOp, 248, R"(nil >> nil)");

PARSE(BinaryOp, 249, R"(nil >> " test string")");

PARSE(BinaryOp, 250, R"(nil >> nil)");

PARSE(BinaryOp, 251, R"(nil >> 3.1415)");

PARSE(BinaryOp, 252, R"(nil >> true)");

PARSE(BinaryOp, 253, R"(nil >> nil)");




PARSE(BinaryOp, 254, R"(42 & 42)");

PARSE(BinaryOp, 255, R"(42 & " test string")");

PARSE(BinaryOp, 256, R"(42 & nil)");

PARSE(BinaryOp, 257, R"(42 & 3.1415)");

PARSE(BinaryOp, 258, R"(42 & true)");

PARSE(BinaryOp, 259, R"(42 & false)");


PARSE(BinaryOp, 260, R"(2.72 & 42)");

PARSE(BinaryOp, 261, R"(2.72 & " test string")");

PARSE(BinaryOp, 262, R"(2.72 & nil)");

PARSE(BinaryOp, 263, R"(2.72 & 3.1415)");

PARSE(BinaryOp, 264, R"(2.72 & true)");

PARSE(BinaryOp, 265, R"(2.72 & false)");


PARSE(BinaryOp, 266, R"("Fun " & 42)");

PARSE(BinaryOp, 267, R"("Fun " & " test string")");

PARSE(BinaryOp, 268, R"("Fun " & nil)");

PARSE(BinaryOp, 269, R"("Fun " & 3.1415)");

PARSE(BinaryOp, 270, R"("Fun " & true)");

PARSE(BinaryOp, 271, R"("Fun " & false)");


PARSE(BinaryOp, 272, R"(true & true)");

PARSE(BinaryOp, 273, R"(true & " test string")");

PARSE(BinaryOp, 274, R"(true & nil)");

PARSE(BinaryOp, 275, R"(true & 3.1415)");

PARSE(BinaryOp, 276, R"(true & true)");

PARSE(BinaryOp, 277, R"(true & false)");


PARSE(BinaryOp, 278, R"(false & false)");

PARSE(BinaryOp, 279, R"(false & " test string")");

PARSE(BinaryOp, 280, R"(false & nil)");

PARSE(BinaryOp, 281, R"(false & 3.1415)");

PARSE(BinaryOp, 282, R"(false & true)");

PARSE(BinaryOp, 283, R"(false & false)");


PARSE(BinaryOp, 284, R"(nil & nil)");

PARSE(BinaryOp, 285, R"(nil & " test string")");

PARSE(BinaryOp, 286, R"(nil & nil)");

PARSE(BinaryOp, 287, R"(nil & 3.1415)");

PARSE(BinaryOp, 288, R"(nil & true)");

PARSE(BinaryOp, 289, R"(nil & nil)");




PARSE(BinaryOp, 290, R"(42 | 42)");

PARSE(BinaryOp, 291, R"(42 | " test string")");

PARSE(BinaryOp, 292, R"(42 | nil)");

PARSE(BinaryOp, 293, R"(42 | 3.1415)");

PARSE(BinaryOp, 294, R"(42 | true)");

PARSE(BinaryOp, 295, R"(42 | false)");


PARSE(BinaryOp, 296, R"(2.72 | 42)");

PARSE(BinaryOp, 297, R"(2.72 | " test string")");

PARSE(BinaryOp, 298, R"(2.72 | nil)");

PARSE(BinaryOp, 299, R"(2.72 | 3.1415)");

PARSE(BinaryOp, 300, R"(2.72 | true)");

PARSE(BinaryOp, 301, R"(2.72 | false)");


PARSE(BinaryOp, 302, R"("Fun " | 42)");

PARSE(BinaryOp, 303, R"("Fun " | " test string")");

PARSE(BinaryOp, 304, R"("Fun " | nil)");

PARSE(BinaryOp, 305, R"("Fun " | 3.1415)");

PARSE(BinaryOp, 306, R"("Fun " | true)");

PARSE(BinaryOp, 307, R"("Fun " | false)");


PARSE(BinaryOp, 308, R"(true | true)");

PARSE(BinaryOp, 309, R"(true | " test string")");

PARSE(BinaryOp, 310, R"(true | nil)");

PARSE(BinaryOp, 311, R"(true | 3.1415)");

PARSE(BinaryOp, 312, R"(true | true)");

PARSE(BinaryOp, 313, R"(true | false)");


PARSE(BinaryOp, 314, R"(false | false)");

PARSE(BinaryOp, 315, R"(false | " test string")");

PARSE(BinaryOp, 316, R"(false | nil)");

PARSE(BinaryOp, 317, R"(false | 3.1415)");

PARSE(BinaryOp, 318, R"(false | true)");

PARSE(BinaryOp, 319, R"(false | false)");


PARSE(BinaryOp, 320, R"(nil | nil)");

PARSE(BinaryOp, 321, R"(nil | " test string")");

PARSE(BinaryOp, 322, R"(nil | nil)");

PARSE(BinaryOp, 323, R"(nil | 3.1415)");

PARSE(BinaryOp, 324, R"(nil | true)");

PARSE(BinaryOp, 325, R"(nil | nil)");




PARSE(BinaryOp, 326, R"(42 ^ 42)");

PARSE(BinaryOp, 327, R"(42 ^ " test string")");

PARSE(BinaryOp, 328, R"(42 ^ nil)");

PARSE(BinaryOp, 329, R"(42 ^ 3.1415)");

PARSE(BinaryOp, 330, R"(42 ^ true)");

PARSE(BinaryOp, 331, R"(42 ^ false)");


PARSE(BinaryOp, 332, R"(2.72 ^ 42)");

PARSE(BinaryOp, 333, R"(2.72 ^ " test string")");

PARSE(BinaryOp, 334, R"(2.72 ^ nil)");

PARSE(BinaryOp, 335, R"(2.72 ^ 3.1415)");

PARSE(BinaryOp, 336, R"(2.72 ^ true)");

PARSE(BinaryOp, 337, R"(2.72 ^ false)");


PARSE(BinaryOp, 338, R"("Fun " ^ 42)");

PARSE(BinaryOp, 339, R"("Fun " ^ " test string")");

PARSE(BinaryOp, 340, R"("Fun " ^ nil)");

PARSE(BinaryOp, 341, R"("Fun " ^ 3.1415)");

PARSE(BinaryOp, 342, R"("Fun " ^ true)");

PARSE(BinaryOp, 343, R"("Fun " ^ false)");


PARSE(BinaryOp, 344, R"(true ^ true)");

PARSE(BinaryOp, 345, R"(true ^ " test string")");

PARSE(BinaryOp, 346, R"(true ^ nil)");

PARSE(BinaryOp, 347, R"(true ^ 3.1415)");

PARSE(BinaryOp, 348, R"(true ^ true)");

PARSE(BinaryOp, 349, R"(true ^ false)");


PARSE(BinaryOp, 350, R"(false ^ false)");

PARSE(BinaryOp, 351, R"(false ^ " test string")");

PARSE(BinaryOp, 352, R"(false ^ nil)");

PARSE(BinaryOp, 353, R"(false ^ 3.1415)");

PARSE(BinaryOp, 354, R"(false ^ true)");

PARSE(BinaryOp, 355, R"(false ^ false)");


PARSE(BinaryOp, 356, R"(nil ^ nil)");

PARSE(BinaryOp, 357, R"(nil ^ " test string")");

PARSE(BinaryOp, 358, R"(nil ^ nil)");

PARSE(BinaryOp, 359, R"(nil ^ 3.1415)");

PARSE(BinaryOp, 360, R"(nil ^ true)");

PARSE(BinaryOp, 361, R"(nil ^ nil)");




PARSE(BinaryOp, 362, R"(42 && 42)");

PARSE(BinaryOp, 363, R"(42 && " test string")");

PARSE(BinaryOp, 364, R"(42 && nil)");

PARSE(BinaryOp, 365, R"(42 && 3.1415)");

PARSE(BinaryOp, 366, R"(42 && true)");

PARSE(BinaryOp, 367, R"(42 && false)");


PARSE(BinaryOp, 368, R"(2.72 && 42)");

PARSE(BinaryOp, 369, R"(2.72 && " test string")");

PARSE(BinaryOp, 370, R"(2.72 && nil)");

PARSE(BinaryOp, 371, R"(2.72 && 3.1415)");

PARSE(BinaryOp, 372, R"(2.72 && true)");

PARSE(BinaryOp, 373, R"(2.72 && false)");


PARSE(BinaryOp, 374, R"("Fun " && 42)");

PARSE(BinaryOp, 375, R"("Fun " && " test string")");

PARSE(BinaryOp, 376, R"("Fun " && nil)");

PARSE(BinaryOp, 377, R"("Fun " && 3.1415)");

PARSE(BinaryOp, 378, R"("Fun " && true)");

PARSE(BinaryOp, 379, R"("Fun " && false)");


PARSE(BinaryOp, 380, R"(true && true)");

PARSE(BinaryOp, 381, R"(true && " test string")");

PARSE(BinaryOp, 382, R"(true && nil)");

PARSE(BinaryOp, 383, R"(true && 3.1415)");

PARSE(BinaryOp, 384, R"(true && true)");

PARSE(BinaryOp, 385, R"(true && false)");


PARSE(BinaryOp, 386, R"(false && false)");

PARSE(BinaryOp, 387, R"(false && " test string")");

PARSE(BinaryOp, 388, R"(false && nil)");

PARSE(BinaryOp, 389, R"(false && 3.1415)");

PARSE(BinaryOp, 390, R"(false && true)");

PARSE(BinaryOp, 391, R"(false && false)");


PARSE(BinaryOp, 392, R"(nil && nil)");

PARSE(BinaryOp, 393, R"(nil && " test string")");

PARSE(BinaryOp, 394, R"(nil && nil)");

PARSE(BinaryOp, 395, R"(nil && 3.1415)");

PARSE(BinaryOp, 396, R"(nil && true)");

PARSE(BinaryOp, 397, R"(nil && nil)");




PARSE(BinaryOp, 398, R"(42 || 42)");

PARSE(BinaryOp, 399, R"(42 || " test string")");

PARSE(BinaryOp, 400, R"(42 || nil)");

PARSE(BinaryOp, 401, R"(42 || 3.1415)");

PARSE(BinaryOp, 402, R"(42 || true)");

PARSE(BinaryOp, 403, R"(42 || false)");


PARSE(BinaryOp, 404, R"(2.72 || 42)");

PARSE(BinaryOp, 405, R"(2.72 || " test string")");

PARSE(BinaryOp, 406, R"(2.72 || nil)");

PARSE(BinaryOp, 407, R"(2.72 || 3.1415)");

PARSE(BinaryOp, 408, R"(2.72 || true)");

PARSE(BinaryOp, 409, R"(2.72 || false)");


PARSE(BinaryOp, 410, R"("Fun " || 42)");

PARSE(BinaryOp, 411, R"("Fun " || " test string")");

PARSE(BinaryOp, 412, R"("Fun " || nil)");

PARSE(BinaryOp, 413, R"("Fun " || 3.1415)");

PARSE(BinaryOp, 414, R"("Fun " || true)");

PARSE(BinaryOp, 415, R"("Fun " || false)");


PARSE(BinaryOp, 416, R"(true || true)");

PARSE(BinaryOp, 417, R"(true || " test string")");

PARSE(BinaryOp, 418, R"(true || nil)");

PARSE(BinaryOp, 419, R"(true || 3.1415)");

PARSE(BinaryOp, 420, R"(true || true)");

PARSE(BinaryOp, 421, R"(true || false)");


PARSE(BinaryOp, 422, R"(false || false)");

PARSE(BinaryOp, 423, R"(false || " test string")");

PARSE(BinaryOp, 424, R"(false || nil)");

PARSE(BinaryOp, 425, R"(false || 3.1415)");

PARSE(BinaryOp, 426, R"(false || true)");

PARSE(BinaryOp, 427, R"(false || false)");


PARSE(BinaryOp, 428, R"(nil || nil)");

PARSE(BinaryOp, 429, R"(nil || " test string")");

PARSE(BinaryOp, 430, R"(nil || nil)");

PARSE(BinaryOp, 431, R"(nil || 3.1415)");

PARSE(BinaryOp, 432, R"(nil || true)");

PARSE(BinaryOp, 433, R"(nil || nil)");




PARSE(BinaryOp, 434, R"(42 < 42)");

PARSE(BinaryOp, 435, R"(42 < " test string")");

PARSE(BinaryOp, 436, R"(42 < nil)");

PARSE(BinaryOp, 437, R"(42 < 3.1415)");

PARSE(BinaryOp, 438, R"(42 < true)");

PARSE(BinaryOp, 439, R"(42 < false)");


PARSE(BinaryOp, 440, R"(2.72 < 42)");

PARSE(BinaryOp, 441, R"(2.72 < " test string")");

PARSE(BinaryOp, 442, R"(2.72 < nil)");

PARSE(BinaryOp, 443, R"(2.72 < 3.1415)");

PARSE(BinaryOp, 444, R"(2.72 < true)");

PARSE(BinaryOp, 445, R"(2.72 < false)");


PARSE(BinaryOp, 446, R"("Fun " < 42)");

PARSE(BinaryOp, 447, R"("Fun " < " test string")");

PARSE(BinaryOp, 448, R"("Fun " < nil)");

PARSE(BinaryOp, 449, R"("Fun " < 3.1415)");

PARSE(BinaryOp, 450, R"("Fun " < true)");

PARSE(BinaryOp, 451, R"("Fun " < false)");


PARSE(BinaryOp, 452, R"(true < true)");

PARSE(BinaryOp, 453, R"(true < " test string")");

PARSE(BinaryOp, 454, R"(true < nil)");

PARSE(BinaryOp, 455, R"(true < 3.1415)");

PARSE(BinaryOp, 456, R"(true < true)");

PARSE(BinaryOp, 457, R"(true < false)");


PARSE(BinaryOp, 458, R"(false < false)");

PARSE(BinaryOp, 459, R"(false < " test string")");

PARSE(BinaryOp, 460, R"(false < nil)");

PARSE(BinaryOp, 461, R"(false < 3.1415)");

PARSE(BinaryOp, 462, R"(false < true)");

PARSE(BinaryOp, 463, R"(false < false)");


PARSE(BinaryOp, 464, R"(nil < nil)");

PARSE(BinaryOp, 465, R"(nil < " test string")");

PARSE(BinaryOp, 466, R"(nil < nil)");

PARSE(BinaryOp, 467, R"(nil < 3.1415)");

PARSE(BinaryOp, 468, R"(nil < true)");

PARSE(BinaryOp, 469, R"(nil < nil)");




PARSE(BinaryOp, 470, R"(42 > 42)");

PARSE(BinaryOp, 471, R"(42 > " test string")");

PARSE(BinaryOp, 472, R"(42 > nil)");

PARSE(BinaryOp, 473, R"(42 > 3.1415)");

PARSE(BinaryOp, 474, R"(42 > true)");

PARSE(BinaryOp, 475, R"(42 > false)");


PARSE(BinaryOp, 476, R"(2.72 > 42)");

PARSE(BinaryOp, 477, R"(2.72 > " test string")");

PARSE(BinaryOp, 478, R"(2.72 > nil)");

PARSE(BinaryOp, 479, R"(2.72 > 3.1415)");

PARSE(BinaryOp, 480, R"(2.72 > true)");

PARSE(BinaryOp, 481, R"(2.72 > false)");


PARSE(BinaryOp, 482, R"("Fun " > 42)");

PARSE(BinaryOp, 483, R"("Fun " > " test string")");

PARSE(BinaryOp, 484, R"("Fun " > nil)");

PARSE(BinaryOp, 485, R"("Fun " > 3.1415)");

PARSE(BinaryOp, 486, R"("Fun " > true)");

PARSE(BinaryOp, 487, R"("Fun " > false)");


PARSE(BinaryOp, 488, R"(true > true)");

PARSE(BinaryOp, 489, R"(true > " test string")");

PARSE(BinaryOp, 490, R"(true > nil)");

PARSE(BinaryOp, 491, R"(true > 3.1415)");

PARSE(BinaryOp, 492, R"(true > true)");

PARSE(BinaryOp, 493, R"(true > false)");


PARSE(BinaryOp, 494, R"(false > false)");

PARSE(BinaryOp, 495, R"(false > " test string")");

PARSE(BinaryOp, 496, R"(false > nil)");

PARSE(BinaryOp, 497, R"(false > 3.1415)");

PARSE(BinaryOp, 498, R"(false > true)");

PARSE(BinaryOp, 499, R"(false > false)");


PARSE(BinaryOp, 500, R"(nil > nil)");

PARSE(BinaryOp, 501, R"(nil > " test string")");

PARSE(BinaryOp, 502, R"(nil > nil)");

PARSE(BinaryOp, 503, R"(nil > 3.1415)");

PARSE(BinaryOp, 504, R"(nil > true)");

PARSE(BinaryOp, 505, R"(nil > nil)");




PARSE(BinaryOp, 506, R"(42 >= 42)");

PARSE(BinaryOp, 507, R"(42 >= " test string")");

PARSE(BinaryOp, 508, R"(42 >= nil)");

PARSE(BinaryOp, 509, R"(42 >= 3.1415)");

PARSE(BinaryOp, 510, R"(42 >= true)");

PARSE(BinaryOp, 511, R"(42 >= false)");


PARSE(BinaryOp, 512, R"(2.72 >= 42)");

PARSE(BinaryOp, 513, R"(2.72 >= " test string")");

PARSE(BinaryOp, 514, R"(2.72 >= nil)");

PARSE(BinaryOp, 515, R"(2.72 >= 3.1415)");

PARSE(BinaryOp, 516, R"(2.72 >= true)");

PARSE(BinaryOp, 517, R"(2.72 >= false)");


PARSE(BinaryOp, 518, R"("Fun " >= 42)");

PARSE(BinaryOp, 519, R"("Fun " >= " test string")");

PARSE(BinaryOp, 520, R"("Fun " >= nil)");

PARSE(BinaryOp, 521, R"("Fun " >= 3.1415)");

PARSE(BinaryOp, 522, R"("Fun " >= true)");

PARSE(BinaryOp, 523, R"("Fun " >= false)");


PARSE(BinaryOp, 524, R"(true >= true)");

PARSE(BinaryOp, 525, R"(true >= " test string")");

PARSE(BinaryOp, 526, R"(true >= nil)");

PARSE(BinaryOp, 527, R"(true >= 3.1415)");

PARSE(BinaryOp, 528, R"(true >= true)");

PARSE(BinaryOp, 529, R"(true >= false)");


PARSE(BinaryOp, 530, R"(false >= false)");

PARSE(BinaryOp, 531, R"(false >= " test string")");

PARSE(BinaryOp, 532, R"(false >= nil)");

PARSE(BinaryOp, 533, R"(false >= 3.1415)");

PARSE(BinaryOp, 534, R"(false >= true)");

PARSE(BinaryOp, 535, R"(false >= false)");


PARSE(BinaryOp, 536, R"(nil >= nil)");

PARSE(BinaryOp, 537, R"(nil >= " test string")");

PARSE(BinaryOp, 538, R"(nil >= nil)");

PARSE(BinaryOp, 539, R"(nil >= 3.1415)");

PARSE(BinaryOp, 540, R"(nil >= true)");

PARSE(BinaryOp, 541, R"(nil >= nil)");




PARSE(BinaryOp, 542, R"(42 <= 42)");

PARSE(BinaryOp, 543, R"(42 <= " test string")");

PARSE(BinaryOp, 544, R"(42 <= nil)");

PARSE(BinaryOp, 545, R"(42 <= 3.1415)");

PARSE(BinaryOp, 546, R"(42 <= true)");

PARSE(BinaryOp, 547, R"(42 <= false)");


PARSE(BinaryOp, 548, R"(2.72 <= 42)");

PARSE(BinaryOp, 549, R"(2.72 <= " test string")");

PARSE(BinaryOp, 550, R"(2.72 <= nil)");

PARSE(BinaryOp, 551, R"(2.72 <= 3.1415)");

PARSE(BinaryOp, 552, R"(2.72 <= true)");

PARSE(BinaryOp, 553, R"(2.72 <= false)");


PARSE(BinaryOp, 554, R"("Fun " <= 42)");

PARSE(BinaryOp, 555, R"("Fun " <= " test string")");

PARSE(BinaryOp, 556, R"("Fun " <= nil)");

PARSE(BinaryOp, 557, R"("Fun " <= 3.1415)");

PARSE(BinaryOp, 558, R"("Fun " <= true)");

PARSE(BinaryOp, 559, R"("Fun " <= false)");


PARSE(BinaryOp, 560, R"(true <= true)");

PARSE(BinaryOp, 561, R"(true <= " test string")");

PARSE(BinaryOp, 562, R"(true <= nil)");

PARSE(BinaryOp, 563, R"(true <= 3.1415)");

PARSE(BinaryOp, 564, R"(true <= true)");

PARSE(BinaryOp, 565, R"(true <= false)");


PARSE(BinaryOp, 566, R"(false <= false)");

PARSE(BinaryOp, 567, R"(false <= " test string")");

PARSE(BinaryOp, 568, R"(false <= nil)");

PARSE(BinaryOp, 569, R"(false <= 3.1415)");

PARSE(BinaryOp, 570, R"(false <= true)");

PARSE(BinaryOp, 571, R"(false <= false)");


PARSE(BinaryOp, 572, R"(nil <= nil)");

PARSE(BinaryOp, 573, R"(nil <= " test string")");

PARSE(BinaryOp, 574, R"(nil <= nil)");

PARSE(BinaryOp, 575, R"(nil <= 3.1415)");

PARSE(BinaryOp, 576, R"(nil <= true)");

PARSE(BinaryOp, 577, R"(nil <= nil)");




PARSE(BinaryOp, 578, R"(42 == 42)");

PARSE(BinaryOp, 579, R"(42 == " test string")");

PARSE(BinaryOp, 580, R"(42 == nil)");

PARSE(BinaryOp, 581, R"(42 == 3.1415)");

PARSE(BinaryOp, 582, R"(42 == true)");

PARSE(BinaryOp, 583, R"(42 == false)");


PARSE(BinaryOp, 584, R"(2.72 == 42)");

PARSE(BinaryOp, 585, R"(2.72 == " test string")");

PARSE(BinaryOp, 586, R"(2.72 == nil)");

PARSE(BinaryOp, 587, R"(2.72 == 3.1415)");

PARSE(BinaryOp, 588, R"(2.72 == true)");

PARSE(BinaryOp, 589, R"(2.72 == false)");


PARSE(BinaryOp, 590, R"("Fun " == 42)");

PARSE(BinaryOp, 591, R"("Fun " == " test string")");

PARSE(BinaryOp, 592, R"("Fun " == nil)");

PARSE(BinaryOp, 593, R"("Fun " == 3.1415)");

PARSE(BinaryOp, 594, R"("Fun " == true)");

PARSE(BinaryOp, 595, R"("Fun " == false)");


PARSE(BinaryOp, 596, R"(true == true)");

PARSE(BinaryOp, 597, R"(true == " test string")");

PARSE(BinaryOp, 598, R"(true == nil)");

PARSE(BinaryOp, 599, R"(true == 3.1415)");

PARSE(BinaryOp, 600, R"(true == true)");

PARSE(BinaryOp, 601, R"(true == false)");


PARSE(BinaryOp, 602, R"(false == false)");

PARSE(BinaryOp, 603, R"(false == " test string")");

PARSE(BinaryOp, 604, R"(false == nil)");

PARSE(BinaryOp, 605, R"(false == 3.1415)");

PARSE(BinaryOp, 606, R"(false == true)");

PARSE(BinaryOp, 607, R"(false == false)");


PARSE(BinaryOp, 608, R"(nil == nil)");

PARSE(BinaryOp, 609, R"(nil == " test string")");

PARSE(BinaryOp, 610, R"(nil == nil)");

PARSE(BinaryOp, 611, R"(nil == 3.1415)");

PARSE(BinaryOp, 612, R"(nil == true)");

PARSE(BinaryOp, 613, R"(nil == nil)");




PARSE(BinaryOp, 614, R"(42 != 42)");

PARSE(BinaryOp, 615, R"(42 != " test string")");

PARSE(BinaryOp, 616, R"(42 != nil)");

PARSE(BinaryOp, 617, R"(42 != 3.1415)");

PARSE(BinaryOp, 618, R"(42 != true)");

PARSE(BinaryOp, 619, R"(42 != false)");


PARSE(BinaryOp, 620, R"(2.72 != 42)");

PARSE(BinaryOp, 621, R"(2.72 != " test string")");

PARSE(BinaryOp, 622, R"(2.72 != nil)");

PARSE(BinaryOp, 623, R"(2.72 != 3.1415)");

PARSE(BinaryOp, 624, R"(2.72 != true)");

PARSE(BinaryOp, 625, R"(2.72 != false)");


PARSE(BinaryOp, 626, R"("Fun " != 42)");

PARSE(BinaryOp, 627, R"("Fun " != " test string")");

PARSE(BinaryOp, 628, R"("Fun " != nil)");

PARSE(BinaryOp, 629, R"("Fun " != 3.1415)");

PARSE(BinaryOp, 630, R"("Fun " != true)");

PARSE(BinaryOp, 631, R"("Fun " != false)");


PARSE(BinaryOp, 632, R"(true != true)");

PARSE(BinaryOp, 633, R"(true != " test string")");

PARSE(BinaryOp, 634, R"(true != nil)");

PARSE(BinaryOp, 635, R"(true != 3.1415)");

PARSE(BinaryOp, 636, R"(true != true)");

PARSE(BinaryOp, 637, R"(true != false)");


PARSE(BinaryOp, 638, R"(false != false)");

PARSE(BinaryOp, 639, R"(false != " test string")");

PARSE(BinaryOp, 640, R"(false != nil)");

PARSE(BinaryOp, 641, R"(false != 3.1415)");

PARSE(BinaryOp, 642, R"(false != true)");

PARSE(BinaryOp, 643, R"(false != false)");


PARSE(BinaryOp, 644, R"(nil != nil)");

PARSE(BinaryOp, 645, R"(nil != " test string")");

PARSE(BinaryOp, 646, R"(nil != nil)");

PARSE(BinaryOp, 647, R"(nil != 3.1415)");

PARSE(BinaryOp, 648, R"(nil != true)");

PARSE(BinaryOp, 649, R"(nil != nil)");




EVAL(BinaryOp, 650, R"(42 + 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 + 42)
);

EVAL(BinaryOp, 651, R"(42 + " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "42 test string");
);

EVAL(BinaryOp, 652, R"(42 + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 + 0);
);

EVAL(BinaryOp, 653, R"(42 + 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 42 + 3.1415);
);

EVAL(BinaryOp, 654, R"(42 + true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 + true);
);

EVAL(BinaryOp, 655, R"(42 + false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 + false);
);


EVAL(BinaryOp, 656, R"(2.72 + 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 + 42);
);

EVAL(BinaryOp, 657, R"(2.72 + " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "2.72 test string")
);

EVAL(BinaryOp, 658, R"(2.72 + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72)
);

EVAL(BinaryOp, 659, R"(2.72 + 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 + 3.1415)
);

EVAL(BinaryOp, 660, R"(2.72 + true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 + true)
);

EVAL(BinaryOp, 661, R"(2.72 + false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 + false)
);


EVAL(BinaryOp, 662, R"("Fun " + 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

   	CHECK_STRING_OPERAND(0, "Fun 42")
);

EVAL(BinaryOp, 663, R"("Fun " + " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "Fun  test string")
);

EVAL(BinaryOp, 664, R"("Fun " + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "Fun nil")
);

EVAL(BinaryOp, 665, R"("Fun " + 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "Fun 3.1415")
);

EVAL(BinaryOp, 666, R"("Fun " + true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "Fun true")
);

EVAL(BinaryOp, 667, R"("Fun " + false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "Fun false")
);


EVAL_ERR(BinaryOp, 668, R"(true + true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 669, R"(true + " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "true test string")
);

EVAL_ERR(BinaryOp, 670, R"(true + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 671, R"(true + 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, true + 3.1415)
);

EVAL_ERR(BinaryOp, 672, R"(true + true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 673, R"(true + false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 674, R"(false + false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 675, R"(false + " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "false test string")
);

EVAL_ERR(BinaryOp, 676, R"(false + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 677, R"(false + 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, false + 3.1415)
);

EVAL_ERR(BinaryOp, 678, R"(false + true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 679, R"(false + false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 680, R"(nil + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 681, R"(nil + " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_STRING_OPERAND(0, "nil test string")
);

EVAL_ERR(BinaryOp, 682, R"(nil + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 683, R"(nil + 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, 3.1415)
);

EVAL_ERR(BinaryOp, 684, R"(nil + true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 685, R"(nil + nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);







EVAL(BinaryOp, 686, R"(42 - 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 - 42)
);

EVAL_ERR(BinaryOp, 687, R"(42 - " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3); 
);

EVAL(BinaryOp, 688, R"(42 - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 - 0);
);

EVAL(BinaryOp, 689, R"(42 - 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 42 - 3.1415);
);

EVAL(BinaryOp, 690, R"(42 - true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 - true);
);

EVAL(BinaryOp, 691, R"(42 - false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 - false);
);


EVAL(BinaryOp, 692, R"(2.72 - 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 - 42);
);

EVAL_ERR(BinaryOp, 693, R"(2.72 - " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 694, R"(2.72 - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72)
);

EVAL(BinaryOp, 695, R"(2.72 - 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 - 3.1415)
);

EVAL(BinaryOp, 696, R"(2.72 - true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 - true)
);

EVAL(BinaryOp, 697, R"(2.72 - false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 - false)
);


EVAL_ERR(BinaryOp, 698, R"("Fun " - 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 699, R"("Fun " - " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 700, R"("Fun " - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 701, R"("Fun " - 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 702, R"("Fun " - true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 703, R"("Fun " - false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 704, R"(true - true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 705, R"(true - " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 706, R"(true - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 707, R"(true - 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, true - 3.1415)
);

EVAL_ERR(BinaryOp, 708, R"(true - true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 709, R"(true - false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 710, R"(false - false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 711, R"(false - " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 712, R"(false - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 713, R"(false - 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, false - 3.1415)
);

EVAL_ERR(BinaryOp, 714, R"(false - true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 715, R"(false - false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 716, R"(nil - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 717, R"(nil - " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 718, R"(nil - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 719, R"(nil - 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, 0 - 3.1415)
);

EVAL_ERR(BinaryOp, 720, R"(nil - true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 721, R"(nil - nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);




EVAL(BinaryOp, 722, R"(42 * 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 * 42)
);

EVAL_ERR(BinaryOp, 723, R"(42 * " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3); 
);

EVAL(BinaryOp, 724, R"(42 * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 * 0);
);

EVAL(BinaryOp, 725, R"(42 * 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 42 * 3.1415);
);

EVAL(BinaryOp, 726, R"(42 * true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 * true);
);

EVAL(BinaryOp, 727, R"(42 * false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 * false);
);


EVAL(BinaryOp, 728, R"(2.72 * 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 * 42);
);

EVAL_ERR(BinaryOp, 729, R"(2.72 * " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 730, R"(2.72 * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 * 0)
);

EVAL(BinaryOp, 731, R"(2.72 * 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 * 3.1415)
);

EVAL(BinaryOp, 732, R"(2.72 * true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 * true)
);

EVAL(BinaryOp, 733, R"(2.72 * false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 * false)
);


EVAL_ERR(BinaryOp, 734, R"("Fun " * 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 735, R"("Fun " * " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 736, R"("Fun " * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 737, R"("Fun " * 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 738, R"("Fun " * true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 739, R"("Fun " * false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 740, R"(true * true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 741, R"(true * " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 742, R"(true * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 743, R"(true * 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, true * 3.1415)
);

EVAL_ERR(BinaryOp, 744, R"(true * true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 745, R"(true * false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 746, R"(false * false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 747, R"(false * " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 748, R"(false * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 749, R"(false * 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, false * 3.1415)
);

EVAL_ERR(BinaryOp, 750, R"(false * true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 751, R"(false * false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 752, R"(nil * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 753, R"(nil * " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 754, R"(nil * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 755, R"(nil * 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, 0 * 3.1415)
);

EVAL_ERR(BinaryOp, 756, R"(nil * true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 757, R"(nil * nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);





EVAL(BinaryOp, 758, R"(42 / 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 / 42)
);

EVAL_ERR(BinaryOp, 759, R"(42 / " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3); 
);

EVAL_ERR(BinaryOp, 760, R"(42 / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 761, R"(42 / 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 42 / 3.1415);
);

EVAL(BinaryOp, 762, R"(42 / true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 / true);
);

EVAL_ERR(BinaryOp, 763, R"(42 / false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL(BinaryOp, 764, R"(2.72 / 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 / 42);
);

EVAL_ERR(BinaryOp, 765, R"(2.72 / " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 766, R"(2.72 / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 767, R"(2.72 / 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 / 3.1415)
);

EVAL(BinaryOp, 768, R"(2.72 / true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_REAL_OPERAND(0, 2.72 / true)
);

EVAL_ERR(BinaryOp, 769, R"(2.72 / false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 770, R"("Fun " / 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 771, R"("Fun " / " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 772, R"("Fun " / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 773, R"("Fun " / 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 774, R"("Fun " / true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 775, R"("Fun " / false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 776, R"(true / true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 777, R"(true / " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 778, R"(true / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 779, R"(true / 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, true / 3.1415)
);

EVAL_ERR(BinaryOp, 780, R"(true / true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 781, R"(true / false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 782, R"(false / false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 783, R"(false / " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 784, R"(false / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 785, R"(false / 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, false / 3.1415)
);

EVAL_ERR(BinaryOp, 786, R"(false / true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 787, R"(false / false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 788, R"(nil / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 789, R"(nil / " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 790, R"(nil / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 791, R"(nil / 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1); 

    CHECK_REAL_OPERAND(0, 0 / 3.1415)
);

EVAL_ERR(BinaryOp, 792, R"(nil / true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 793, R"(nil / nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);






EVAL(BinaryOp, 794, R"(42 % 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 % 42)
);

EVAL_ERR(BinaryOp, 795, R"(42 % " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3); 
);

EVAL_ERR(BinaryOp, 796, R"(42 % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 797, R"(42 % 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 798, R"(42 % true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 % true);
);

EVAL_ERR(BinaryOp, 799, R"(42 % false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 800, R"(2.72 % 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 801, R"(2.72 % " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 802, R"(2.72 % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 803, R"(2.72 % 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 804, R"(2.72 % true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 805, R"(2.72 % false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 806, R"("Fun " % 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 807, R"("Fun " % " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 808, R"("Fun " % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 809, R"("Fun " % 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 810, R"("Fun " % true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 811, R"("Fun " % false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 812, R"(true % true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 813, R"(true % " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 814, R"(true % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 815, R"(true % 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 816, R"(true % true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 817, R"(true % false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 818, R"(false % false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 819, R"(false % " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 820, R"(false % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 821, R"(false % 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 822, R"(false % true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 823, R"(false % false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 824, R"(nil % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 825, R"(nil % " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 826, R"(nil % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 827, R"(nil % 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 828, R"(nil % true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 829, R"(nil % nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);








EVAL(BinaryOp, 830, R"(42 << 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42LL << 42)
);

EVAL(BinaryOp, 831, R"(42 << " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "42 test string")
);

EVAL(BinaryOp, 832, R"(42 << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 << 0)
);

EVAL_ERR(BinaryOp, 833, R"(42 << 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 834, R"(42 << true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 << true);
);

EVAL(BinaryOp, 835, R"(42 << false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 << false)
);


EVAL_ERR(BinaryOp, 836, R"(2.72 << 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 837, R"(2.72 << " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "2.72 test string")
);

EVAL_ERR(BinaryOp, 838, R"(2.72 << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 839, R"(2.72 << 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 840, R"(2.72 << true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 841, R"(2.72 << false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 842, R"("Fun " << 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun 42")
);

EVAL(BinaryOp, 843, R"("Fun " << " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun  test string")
);

EVAL(BinaryOp, 844, R"("Fun " << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun nil")
);

EVAL(BinaryOp, 845, R"("Fun " << 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun 3.1415")
);

EVAL(BinaryOp, 846, R"("Fun " << true)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun true")
);

EVAL(BinaryOp, 847, R"("Fun " << false)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun false")
);


EVAL_ERR(BinaryOp, 848, R"(true << true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 849, R"(true << " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "true test string")
);

EVAL_ERR(BinaryOp, 850, R"(true << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 851, R"(true << 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 852, R"(true << true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 853, R"(true << false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 854, R"(false << false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 855, R"(false << " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "false test string")
);

EVAL_ERR(BinaryOp, 856, R"(false << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 857, R"(false << 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 858, R"(false << true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 859, R"(false << false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 860, R"(nil << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 861, R"(nil << " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "nil test string")
);

EVAL_ERR(BinaryOp, 862, R"(nil << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 863, R"(nil << 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 864, R"(nil << true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 865, R"(nil << nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);









EVAL(BinaryOp, 866, R"(42 >> 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42LL >> 42)
);

EVAL(BinaryOp, 867, R"(42 >> " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "42 test string")
);

EVAL(BinaryOp, 868, R"(42 >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 >> 0)
);

EVAL_ERR(BinaryOp, 869, R"(42 >> 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 870, R"(42 >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 >> true);
);

EVAL(BinaryOp, 871, R"(42 >> false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 >> false)
);


EVAL_ERR(BinaryOp, 872, R"(2.72 >> 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 873, R"(2.72 >> " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "2.72 test string")
);

EVAL_ERR(BinaryOp, 874, R"(2.72 >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 875, R"(2.72 >> 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 876, R"(2.72 >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 877, R"(2.72 >> false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 878, R"("Fun " >> 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun 42")
);

EVAL(BinaryOp, 879, R"("Fun " >> " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun  test string")
);

EVAL(BinaryOp, 880, R"("Fun " >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun nil")
);

EVAL(BinaryOp, 881, R"("Fun " >> 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun 3.1415")
);

EVAL(BinaryOp, 882, R"("Fun " >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun true")
);

EVAL(BinaryOp, 883, R"("Fun " >> false)",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "Fun false")
);


EVAL_ERR(BinaryOp, 884, R"(true >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 885, R"(true >> " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "true test string")
);

EVAL_ERR(BinaryOp, 886, R"(true >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 887, R"(true >> 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 888, R"(true >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 889, R"(true >> false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 890, R"(false >> false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 891, R"(false >> " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "false test string")
);

EVAL_ERR(BinaryOp, 892, R"(false >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 893, R"(false >> 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 894, R"(false >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 895, R"(false >> false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 896, R"(nil >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 897, R"(nil >> " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4); 
    ASSERT_EQ(operands->count(), 1);

    CHECK_STRING_OPERAND(0, "nil test string")
);

EVAL_ERR(BinaryOp, 898, R"(nil >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 899, R"(nil >> 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 900, R"(nil >> true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 901, R"(nil >> nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);










EVAL(BinaryOp, 902, R"(42 & 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42LL & 42)
);

EVAL_ERR(BinaryOp, 903, R"(42 & " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 904, R"(42 & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 & 0)
);

EVAL_ERR(BinaryOp, 905, R"(42 & 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 906, R"(42 & true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 & true);
);

EVAL(BinaryOp, 907, R"(42 & false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 & false)
);


EVAL_ERR(BinaryOp, 908, R"(2.72 & 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 909, R"(2.72 & " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 910, R"(2.72 & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 911, R"(2.72 & 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 912, R"(2.72 & true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 913, R"(2.72 & false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 914, R"("Fun " & 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 915, R"("Fun " & " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 916, R"("Fun " & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 917, R"("Fun " & 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 918, R"("Fun " & true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 919, R"("Fun " & false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 920, R"(true & true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 921, R"(true & " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 922, R"(true & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 923, R"(true & 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 924, R"(true & true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 925, R"(true & false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 926, R"(false & false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 927, R"(false & " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 928, R"(false & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 929, R"(false & 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 930, R"(false & true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 931, R"(false & false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 932, R"(nil & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 933, R"(nil & " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 934, R"(nil & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 935, R"(nil & 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 936, R"(nil & true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 937, R"(nil & nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);









EVAL(BinaryOp, 938, R"(42 ^ 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42LL ^ 42)
);

EVAL_ERR(BinaryOp, 939, R"(42 ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 940, R"(42 ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 ^ 0)
);

EVAL_ERR(BinaryOp, 941, R"(42 ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 942, R"(42 ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 ^ true);
);

EVAL(BinaryOp, 943, R"(42 ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 ^ false)
);


EVAL_ERR(BinaryOp, 944, R"(2.72 ^ 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 945, R"(2.72 ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 946, R"(2.72 ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 947, R"(2.72 ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 948, R"(2.72 ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 949, R"(2.72 ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 950, R"("Fun " ^ 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 951, R"("Fun " ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 952, R"("Fun " ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 953, R"("Fun " ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 954, R"("Fun " ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 955, R"("Fun " ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 956, R"(true ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 957, R"(true ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 958, R"(true ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 959, R"(true ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 960, R"(true ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 961, R"(true ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 962, R"(false ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 963, R"(false ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 964, R"(false ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 965, R"(false ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 966, R"(false ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 967, R"(false ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 968, R"(nil ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 969, R"(nil ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 970, R"(nil ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 971, R"(nil ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 972, R"(nil ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 973, R"(nil ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);









EVAL(BinaryOp, 974, R"(42 ^ 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42LL ^ 42)
);

EVAL_ERR(BinaryOp, 975, R"(42 ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 976, R"(42 ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 ^ 0)
);

EVAL_ERR(BinaryOp, 977, R"(42 ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 978, R"(42 ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 ^ true);
);

EVAL(BinaryOp, 979, R"(42 ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_INTEGER_OPERAND(0, 42 ^ false)
);


EVAL_ERR(BinaryOp, 980, R"(2.72 ^ 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 981, R"(2.72 ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 982, R"(2.72 ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 983, R"(2.72 ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 984, R"(2.72 ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 985, R"(2.72 ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 986, R"("Fun " ^ 42)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 987, R"("Fun " ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 988, R"("Fun " ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 989, R"("Fun " ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 990, R"("Fun " ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 991, R"("Fun " ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 992, R"(true ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 993, R"(true ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 994, R"(true ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 995, R"(true ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 996, R"(true ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 997, R"(true ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 998, R"(false ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 999, R"(false ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1000, R"(false ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1001, R"(false ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1002, R"(false ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1003, R"(false ^ false)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);


EVAL_ERR(BinaryOp, 1004, R"(nil ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1005, R"(nil ^ " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1006, R"(nil ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1007, R"(nil ^ 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1008, R"(nil ^ true)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL_ERR(BinaryOp, 1009, R"(nil ^ nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);









EVAL(BinaryOp, 1010, R"(42 && 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1011, R"(42 && " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1012, R"(42 && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1013, R"(42 && 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1014, R"(42 && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1015, R"(42 && false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1016, R"(2.72 && 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1017, R"(2.72 && " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1018, R"(2.72 && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1019, R"(2.72 && 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1020, R"(2.72 && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1021, R"(2.72 && false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1022, R"("Fun " && 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1023, R"("Fun " && " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1024, R"("Fun " && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1025, R"("Fun " && 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1026, R"("Fun " && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1027, R"("Fun " && false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1028, R"(true && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1029, R"(true && " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1030, R"(true && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1031, R"(true && 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1032, R"(true && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1033, R"(true && false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1034, R"(false && false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1035, R"(false && " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1036, R"(false && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1037, R"(false && 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1038, R"(false && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1039, R"(false && false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1040, R"(nil && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1041, R"(nil && " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1042, R"(nil && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1043, R"(nil && 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1044, R"(nil && true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1045, R"(nil && nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);









EVAL(BinaryOp, 1046, R"(42 || 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1047, R"(42 || " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1048, R"(42 || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1049, R"(42 || 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1050, R"(42 || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1051, R"(42 || false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1052, R"(2.72 || 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1053, R"(2.72 || " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1054, R"(2.72 || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1055, R"(2.72 || 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1056, R"(2.72 || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1057, R"(2.72 || false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1058, R"("Fun " || 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1059, R"("Fun " || " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1060, R"("Fun " || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1061, R"("Fun " || 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1062, R"("Fun " || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1063, R"("Fun " || false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1064, R"(true || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1065, R"(true || " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1066, R"(true || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1067, R"(true || 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1068, R"(true || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1069, R"(true || false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1070, R"(false || false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1071, R"(false || " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1072, R"(false || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1073, R"(false || 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1074, R"(false || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1075, R"(false || false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1076, R"(nil || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1077, R"(nil || " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1078, R"(nil || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1079, R"(nil || 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1080, R"(nil || true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1081, R"(nil || nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);









EVAL(BinaryOp, 1082, R"(42 < 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1083, R"(42 < " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1084, R"(42 < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1085, R"(42 < 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1086, R"(42 < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1087, R"(42 < false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1088, R"(2.72 < 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1089, R"(2.72 < " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1090, R"(2.72 < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1091, R"(2.72 < 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1092, R"(2.72 < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1093, R"(2.72 < false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1094, R"("Fun " < 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1095, R"("Fun " < " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1096, R"("Fun " < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1097, R"("Fun " < 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1098, R"("Fun " < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1099, R"("Fun " < false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1100, R"(true < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1101, R"(true < " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1102, R"(true < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1103, R"(true < 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1104, R"(true < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1105, R"(true < false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1106, R"(false < false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1107, R"(false < " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1108, R"(false < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1109, R"(false < 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1110, R"(false < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1111, R"(false < false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL_ERR(BinaryOp, 1112, R"(nil < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1113, R"(nil < " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL_ERR(BinaryOp, 1114, R"(nil < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1115, R"(nil < 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1116, R"(nil < true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL_ERR(BinaryOp, 1117, R"(nil < nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);









EVAL(BinaryOp, 1118, R"(42 > 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1119, R"(42 > " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1120, R"(42 > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1121, R"(42 > 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1122, R"(42 > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1123, R"(42 > false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1124, R"(2.72 > 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1125, R"(2.72 > " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1126, R"(2.72 > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1127, R"(2.72 > 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1128, R"(2.72 > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1129, R"(2.72 > false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1130, R"("Fun " > 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1131, R"("Fun " > " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1132, R"("Fun " > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1133, R"("Fun " > 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1134, R"("Fun " > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1135, R"("Fun " > false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1136, R"(true > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1137, R"(true > " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1138, R"(true > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1139, R"(true > 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1140, R"(true > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1141, R"(true > false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1142, R"(false > false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1143, R"(false > " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1144, R"(false > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1145, R"(false > 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1146, R"(false > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1147, R"(false > false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL_ERR(BinaryOp, 1148, R"(nil > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1149, R"(nil > " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL_ERR(BinaryOp, 1150, R"(nil > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1151, R"(nil > 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1152, R"(nil > true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL_ERR(BinaryOp, 1153, R"(nil > nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);









EVAL(BinaryOp, 1154, R"(42 >= 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1155, R"(42 >= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1156, R"(42 >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1157, R"(42 >= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1158, R"(42 >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1159, R"(42 >= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1160, R"(2.72 >= 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1161, R"(2.72 >= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1162, R"(2.72 >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1163, R"(2.72 >= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1164, R"(2.72 >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1165, R"(2.72 >= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1166, R"("Fun " >= 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1167, R"("Fun " >= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1168, R"("Fun " >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1169, R"("Fun " >= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1170, R"("Fun " >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1171, R"("Fun " >= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1172, R"(true >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1173, R"(true >= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1174, R"(true >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1175, R"(true >= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1176, R"(true >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1177, R"(true >= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1178, R"(false >= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1179, R"(false >= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1180, R"(false >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1181, R"(false >= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1182, R"(false >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1183, R"(false >= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL_ERR(BinaryOp, 1184, R"(nil >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1185, R"(nil >= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL_ERR(BinaryOp, 1186, R"(nil >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1187, R"(nil >= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1188, R"(nil >= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL_ERR(BinaryOp, 1189, R"(nil >= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);










EVAL(BinaryOp, 1190, R"(42 <= 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1191, R"(42 <= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1192, R"(42 <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1193, R"(42 <= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1194, R"(42 <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1195, R"(42 <= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1196, R"(2.72 <= 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1197, R"(2.72 <= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1198, R"(2.72 <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1199, R"(2.72 <= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1200, R"(2.72 <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1201, R"(2.72 <= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1202, R"("Fun " <= 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1203, R"("Fun " <= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1204, R"("Fun " <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1205, R"("Fun " <= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1206, R"("Fun " <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1207, R"("Fun " <= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1208, R"(true <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1209, R"(true <= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1210, R"(true <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1211, R"(true <= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1212, R"(true <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1213, R"(true <= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1214, R"(false <= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1215, R"(false <= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1216, R"(false <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1217, R"(false <= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1218, R"(false <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1219, R"(false <= false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL_ERR(BinaryOp, 1220, R"(nil <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1221, R"(nil <= " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL_ERR(BinaryOp, 1222, R"(nil <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);

EVAL(BinaryOp, 1223, R"(nil <= 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1224, R"(nil <= true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL_ERR(BinaryOp, 1225, R"(nil <= nil)",,
    ASSERT_EQ(fun::Statement::counter(), 3);
);








EVAL(BinaryOp, 1226, R"(42 == 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1227, R"(42 == " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1228, R"(42 == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1229, R"(42 == 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1230, R"(42 == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1231, R"(42 == false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1232, R"(2.72 == 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1233, R"(2.72 == " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1234, R"(2.72 == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1235, R"(2.72 == 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1236, R"(2.72 == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1237, R"(2.72 == false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1238, R"("Fun " == 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1239, R"("Fun " == " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1240, R"("Fun " == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1241, R"("Fun " == 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1242, R"("Fun " == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1243, R"("Fun " == false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1244, R"(true == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1245, R"(true == " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1246, R"(true == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1247, R"(true == 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1248, R"(true == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1249, R"(true == false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1250, R"(false == false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1251, R"(false == " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1252, R"(false == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1253, R"(false == 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1254, R"(false == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1255, R"(false == false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1256, R"(nil == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1257, R"(nil == " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1258, R"(nil == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1259, R"(nil == 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1260, R"(nil == true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1261, R"(nil == nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);








EVAL(BinaryOp, 1262, R"(42 != 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1263, R"(42 != " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1264, R"(42 != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1265, R"(42 != 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1266, R"(42 != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1267, R"(42 != false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1268, R"(2.72 != 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1269, R"(2.72 != " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1270, R"(2.72 != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1271, R"(2.72 != 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1272, R"(2.72 != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1273, R"(2.72 != false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1274, R"("Fun " != 42)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1275, R"("Fun " != " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1276, R"("Fun " != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1277, R"("Fun " != 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1278, R"("Fun " != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1279, R"("Fun " != false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1280, R"(true != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1281, R"(true != " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1282, R"(true != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1283, R"(true != 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1284, R"(true != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1285, R"(true != false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);


EVAL(BinaryOp, 1286, R"(false != false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1287, R"(false != " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1288, R"(false != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1289, R"(false != 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1290, R"(false != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1291, R"(false != false)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);


EVAL(BinaryOp, 1292, R"(nil != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1293, R"(nil != " test string")",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1294, R"(nil != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);

EVAL(BinaryOp, 1295, R"(nil != 3.1415)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1296, R"(nil != true)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, true)
);

EVAL(BinaryOp, 1297, R"(nil != nil)",,
    ASSERT_EQ(fun::Statement::counter(), 4);
    ASSERT_EQ(operands->count(), 1);

    CHECK_BOOLEAN_OPERAND(0, false)
);



