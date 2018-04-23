#!/bin/bash
#echo "Compiling..."
for i in `seq 0 4`; do
	echo number of Nodes: $[10**$i]

	echo "Running the code with 1 thread..." >$[10**$i].log
	./out 1 $[10**$i] s > tmp1
	./out 1 $[10**$i] >>$[10**$i].log
	echo "Running the code with 2 thread..." >>$[10**$i].log
	./out 2 $[10**$i] s > tmp2
	./out 2 $[10**$i] >>$[10**$i].log
	echo "Running the code with 4 thread..." >>$[10**$i].log
	./out 4 $[10**$i] s > tmp3
	./out 4 $[10**$i] >>$[10**$i].log

	echo "extracting times..." >>$[10**$i].log
	TS=`cat tmp1`
	TD=`cat tmp2`
	TQ=`cat tmp3`

	SA=$(echo "$TS/$TD" | bc -l)
	SB=$(echo "$TS/$TQ" | bc -l)
	SC=$(echo "$TD/$TQ" | bc -l)

	echo "Speedup is 1 vs 2 threads: $SA">>$[10**$i].log
	echo "Speedup is 1 vs 4 threads: $SB">>$[10**$i].log
	echo "Speedup is 2 vs 4 threads: $SA">>$[10**$i].log

	AF=$(echo "4/3" | bc -l)
	BF=$(echo "1/$SA" | bc -l)
	CF=$(echo "1-$BF" | bc -l)
	PF=$(echo "$AF*$CF" | bc -l)
	echo "parallel fraction 1 vs 2 returned $PF.">>$[10**$i].log

	AF=$(echo "4/3" | bc -l)
	BF=$(echo "1/$SB" | bc -l)
	CF=$(echo "1-$BF" | bc -l)
	PF=$(echo "$AF*$CF" | bc -l)
	echo "parallel fraction 1 vs 4 returned $PF.">>$[10**$i].log

	AF=$(echo "4/3" | bc -l)
	BF=$(echo "1/$SC" | bc -l)
	CF=$(echo "1-$BF" | bc -l)
	PF=$(echo "$AF*$CF" | bc -l)
	echo "parallel fraction 2 vs 4 returned $PF.">>$[10**$i].log

	echo "cleaning up ...">>$[10**$i].log
	rm tmp1
	rm tmp2
	rm tmp3
done
echo "Done!"
