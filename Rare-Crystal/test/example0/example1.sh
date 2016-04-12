#!/bin/bash

bison++ -d example1.y && flex++ example1.l && g++ lex.yy.cc y.tab.c -o foo1 && ./foo1 example1.foo

