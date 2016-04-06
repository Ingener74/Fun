#!/bin/bash

flex --c++ example1.l && bison example1.y && g++ lex.yy.cc && cat example1.foo | ./a.out

