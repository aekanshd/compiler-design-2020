lex phase4.l
yacc -d int_code2.y
gcc int_code2.tab.c
a .cpp