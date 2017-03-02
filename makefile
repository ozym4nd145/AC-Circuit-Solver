all: cir.l cir.y draw.c matrixsolving.c
	lex cir.l
	yacc -d cir.y
	gcc -g -std=gnu99 -o ac_circuit_solver ac.h y.tab.c lex.yy.c draw.c matrixsolving.c solve.c stack.c helper_functions.c -lm
	rm *.tab.*
	rm *.yy.*
clean:
	rm ac_circuit_solver a.out *.svg
	
		
		

