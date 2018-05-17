#!/bin/bash
#echo "Compiling..."

echo ""
echo ""
clear
for thread in `seq 0 2`; do
	echo "Using $[2**$thread] threads: "
done
