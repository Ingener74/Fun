#include "test.h"

using namespace std;
using namespace fun;

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




