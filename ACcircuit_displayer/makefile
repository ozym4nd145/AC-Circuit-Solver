cir: lex.yy.c y.tab.c
	gcc -g y.tab.c lex.yy.c

lex.yy.c: y.tab.c cir.l
	lex cir.l

y.tab.c: cir.y
	yacc -d cir.y


