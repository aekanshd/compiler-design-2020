lex phase4.l
yacc -d int_code.y
gcc int_code.tab.c
a .cpp