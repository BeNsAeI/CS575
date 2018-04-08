#!/bin/bash
#echo "Compiling..."
#make
echo "Running the code with 1 thread..."
./out 1 s > tmp1
./out 1
echo "Running the code with 4 thread..."
./out 4 s > tmp2
./out 4
echo "extracting times..."
TS=`cat tmp1`
TM=`cat tmp2`
echo $TS
echo $TM
SU=$(echo "$TS/$TM" | bc -l)
echo "Speedup is $SU"
echo "cleaning up ..."
rm tmp1
rm tmp2
