#!/bin/bash
for i in {1..10};
do
	echo "Test case $i";
	./a.out ./examples/Testcases/Testcase$i/top.cir $i.svg
	echo "---------------";
done;