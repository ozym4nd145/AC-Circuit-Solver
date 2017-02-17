all: cir.l cir.y draw.c 
	lex cir.l
	yacc -d cir.y
	gcc ac.h y.tab.c lex.yy.c draw.c

clean:
	rm *.gch
	rm *.tab.*
	rm *.yy.*
