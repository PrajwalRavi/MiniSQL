# MiniSQL
A custom compiler for implementing few database functionalities.

## General:
1. The pdf is probably useful.
2. Commit only to **dev** branch.

## Compilation:
yacc -d tokens.y

lex tokens.l

gcc y.tab.c lex.yy.c -ly -ll -lm

./a.out

