#!/bin/sh

yacc -d tokens.y
lex tokens.l
gcc y.tab.c lex.yy.c -ly -ll -lm
