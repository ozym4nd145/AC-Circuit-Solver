all: cir.l cir.y draw.c matrixsolving.c solve.c stack.c helper_functions.c
	lex cir.l
	yacc -d cir.y
	gcc -O3 -std=gnu99 -o ac_circuit_solver y.tab.c lex.yy.c draw.c matrixsolving.c solve.c stack.c helper_functions.c -lm
	rm *.tab.*
	rm *.yy.*
clean:
	rm ac_circuit_solver a.out *.svg results*.txt
	
		
		

