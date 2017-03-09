#!/bin/bash
for i in {1..10};
do
	echo "Test case $i";
	./ac_circuit_solver ./examples/Testcases/Testcase$i/top.cir $i.svg results$i.txt 
	echo "---------------";
done;
