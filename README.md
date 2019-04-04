# MiniSQL
A custom compiler for implementing few database functionalities.

## Compilation:
yacc -d tokens.y

lex tokens.l

gcc y.tab.c lex.yy.c -ly -ll -lm

./a.out

