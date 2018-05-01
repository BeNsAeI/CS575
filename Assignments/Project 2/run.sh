#!/bin/bash
#echo "Compiling..."
for i in `seq 0 3`; do
	echo ""
	echo "Static, Course grain:"
	echo ""
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=static -DCG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 100 200 > tmp$[2**$i]
	./out $[2**$i] 100 200
	
	echo "___Done___"
done
for i in `seq 0 3`; do
	echo ""
	echo "Static, Fine grain:"
	echo ""
	echo number of Threads: $[2**$i]
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=static -DfG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 100 200 > tmp$[2**$i]
	./out $[2**$i] 100 200
	
	echo "___Done___"
done
for i in `seq 0 3`; do
	echo ""
	echo "Dynamic, Course grain:"
	echo ""
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=dynamic -DCG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 100 200 > tmp$[2**$i]
	./out $[2**$i] 100 200
	
	echo "___Done___"
done
for i in `seq 0 3`; do
	echo ""
	echo "Dynamic, Fine grain:"
	echo ""
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=dynamic -DFG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 100 200 > tmp$[2**$i]
	./out $[2**$i] 100 200
	
	echo "___Done___"
done
	echo "extracting times..."
	echo "extracting times..." >> $[2**$i].log
#	TS=`cat tmp1`
#	TD=`cat tmp2`
#	TQ=`cat tmp3`

#	SA=$(echo "$TS/$TD" | bc -l)
#	SB=$(echo "$TS/$TQ" | bc -l)
#	SC=$(echo "$TD/$TQ" | bc -l)

#	echo "Speedup is 1 vs 2 threads: $SA">>$[10**$i].log
#	echo "Speedup is 1 vs 4 threads: $SB">>$[10**$i].log
#	echo "Speedup is 2 vs 4 threads: $SA">>$[10**$i].log

#	AF=$(echo "4/3" | bc -l)
#	BF=$(echo "1/$SA" | bc -l)
#	CF=$(echo "1-$BF" | bc -l)
#	PF=$(echo "$AF*$CF" | bc -l)
#	echo "parallel fraction 1 vs 2 returned $PF.">>$[10**$i].log

#	AF=$(echo "4/3" | bc -l)
#	BF=$(echo "1/$SB" | bc -l)
#	CF=$(echo "1-$BF" | bc -l)
#	PF=$(echo "$AF*$CF" | bc -l)
#	echo "parallel fraction 1 vs 4 returned $PF.">>$[10**$i].log

#	AF=$(echo "4/3" | bc -l)
#	BF=$(echo "1/$SC" | bc -l)
#	CF=$(echo "1-$BF" | bc -l)
#	PF=$(echo "$AF*$CF" | bc -l)
#	echo "parallel fraction 2 vs 4 returned $PF.">>$[10**$i].log

#	echo "cleaning up ...">>$[10**$i].log
#	rm tmp1
#	rm tmp2
#	rm tmp3
done
echo "Done!"
