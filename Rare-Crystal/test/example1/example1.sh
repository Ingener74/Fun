#!/bin/bash

# flex example1.l && bison example1.y && gcc lex.yy.c && cat example1.foo | ./a.out

cat .gitignore | tr -d '/' | xargs rm -rf
flex++ example1.l && g++ lex.yy.cc -o foo && cat example1.foo | ./foo
