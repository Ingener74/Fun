#!/bin/bash

# flex test.l && bison test.y && gcc lex.yy.c && cat test.foo | ./a.out

flex --c++ test.l && g++ lex.yy.cc && cat test.foo | ./a.out
