# AC-Circuit-Solver
Given the netlist, outputs an svg drawing of the AC circuit and also gives the steady state analysis of the circuit

##Compile Instructions
Use "make" to generate executable.

Executable will be named "ac_circuit_solver"

Run that using-> "./ac_circuit_solver <input_file> <output_SVG_file> <output_results_file>"

##Assumptions
Name of passives can't start with I or V.
Only voltage and current source can have name starting with V or I.
