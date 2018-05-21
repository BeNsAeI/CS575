#!/bin/bash
#echo "Compiling..."

echo ""
echo ""
make clean
clear
for thread in `seq 0 3`; do
	echo "Using $[2**$thread] threads: "
	for num in `seq 0 14`; do
		echo "Using $[2**$num*4000] array size: "
		icpc -DNUMS=$[2**$num*4000] -o out-$[2**$thread]-$[2**$num*4000] OMPUtil.cpp main.cpp -lm -openmp -align -qopt-report=3 -qopt-report-phase=vec -no-vec
		./out-$[2**$thread]-$[2**$num*4000] $[2**$thread] >> Output.log
		echo "" >> Output.log
		echo "____________________" >> Output.log
		echo "" >> Output.log
	done
	echo "" >> Output.log
	echo "___________________________________________" >> Output.log
	echo "" >> Output.log
done
