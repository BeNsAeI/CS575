#!/bin/bash
#echo "Compiling..."

echo ""
echo ""
clear
for thread in `seq 0 2`; do
	echo "Using $[2**$thread] threads: "
	for padding in `seq 0 16`; do
		echo "Using $padding paddings: "
		g++ -DPADDING=$[$padding] -DFIX1 -fopenmp OMPUtil.cpp main.cpp -o out -g -O0
		./out $[2**$thread] s >> tmp$[2**$thread]
		echo "">> tmp$[2**$thread]
		./out $[2**$thread]
	done
	echo "Using FIX 2: "
	g++ -DPADDING=0 -DFIX2 -fopenmp OMPUtil.cpp main.cpp -o out -g -O0
	./out $[2**$thread] s >> tmp$[2**$thread]
	./out $[2**$thread]
done
