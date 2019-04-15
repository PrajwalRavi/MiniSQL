# MiniSQL
A custom compiler for implementing few database functionalities.

## General:
1. The pdf is probably useful.
2. Commit only to **dev** branch.
3. Use runner.sh to simplify following compilation process.

## Compilation:
yacc -d tokens.y

lex tokens.l

gcc y.tab.c lex.yy.c -ly -ll -lm

./a.out

