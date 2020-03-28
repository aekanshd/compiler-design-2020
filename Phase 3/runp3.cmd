lex phase3.l
yacc -d syntax_tree.y
gcc syntax_tree.tab.c
a .cpp