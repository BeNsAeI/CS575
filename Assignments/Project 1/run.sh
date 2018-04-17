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
SU=$(echo "$TS/$TM" | bc -l)
#(4./3.)*( 1. - (1./S) )
AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SU" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "Speedup is $SU"
echo "parallel fraction returned $PF."
echo "cleaning up ..."
rm tmp1
rm tmp2
echo "Done!"
