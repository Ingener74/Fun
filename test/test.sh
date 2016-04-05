#!/bin/bash

# flex test.l && bison test.y && gcc lex.yy.c && cat test.foo | ./a.out
flex test.l && gcc lex.yy.c && cat test.foo | ./a.out
