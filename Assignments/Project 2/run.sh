#!/bin/bash
#echo "Compiling..."

echo ""
echo "Static, Course grain:" > generalLog.log
echo ""
for i in `seq 0 3`; do
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=static -DCG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 200 400 s > tmp$[2**$i]
	./out $[2**$i] 200 400
done
echo "extracting times..."
echo "extracting times..." >> generalLog.log
TS=`cat tmp1`
TD=`cat tmp2`
TQ=`cat tmp4`
TH=`cat tmp8`
echo "Time for 4 experiments are: $TS, $TD, $TQ and $TH." >> generalLog.log

CS=$(echo "200*200*400/($TS)/1000000" | bc -l)
CD=$(echo "200*200*400/($TD)/1000000" | bc -l)
CQ=$(echo "200*200*400/($TQ)/1000000" | bc -l)
CH=$(echo "200*200*400/($TH)/1000000" | bc -l)
echo "Performance for 4 experiments are: $CS, $CD, $CQ and $CH Megabodies/second." >> generalLog.log

SA=$(echo "$TS/$TD" | bc -l)
SB=$(echo "$TS/$TQ" | bc -l)
SC=$(echo "$TS/$TH" | bc -l)

echo "Speedup is 1 vs 2 threads: $SA">>generalLog.log
echo "Speedup is 1 vs 4 threads: $SB">>generalLog.log
echo "Speedup is 1 vs 8 threads: $SC">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SA" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 2 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SB" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 4 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SC" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 8 returned $PF.">>generalLog.log
echo "___Done___"
echo "==================================================================================" >> generalLog.log
echo ""
echo "Static, Fine grain:" >> generalLog.log
echo ""
for i in `seq 0 3`; do
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=static -DFG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 200 400 s > tmp$[2**$i]
	./out $[2**$i] 200 400
done
echo "extracting times..."
echo "extracting times..." >> generalLog.log
TS=`cat tmp1`
TD=`cat tmp2`
TQ=`cat tmp4`
TH=`cat tmp8`
echo "Time for 4 experiments are: $TS, $TD, $TQ and $TH." >> generalLog.log

CS=$(echo "200*200*400/($TS)/1000000" | bc -l)
CD=$(echo "200*200*400/($TD)/1000000" | bc -l)
CQ=$(echo "200*200*400/($TQ)/1000000" | bc -l)
CH=$(echo "200*200*400/($TH)/1000000" | bc -l)
echo "Performance for 4 experiments are: $CS, $CD, $CQ and $CH Megabodies/second." >> generalLog.log

SA=$(echo "$TS/$TD" | bc -l)
SB=$(echo "$TS/$TQ" | bc -l)
SC=$(echo "$TS/$TH" | bc -l)

echo "Speedup is 1 vs 2 threads: $SA">>generalLog.log
echo "Speedup is 1 vs 4 threads: $SB">>generalLog.log
echo "Speedup is 1 vs 8 threads: $SC">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SA" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 2 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SB" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 4 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SC" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 8 returned $PF.">>generalLog.log
echo "___Done___"
echo "==================================================================================" >> generalLog.log
echo ""
echo "Dynamic, Course grain:">> generalLog.log
echo ""
for i in `seq 0 3`; do
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=dynamic -DCG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 200 400 s > tmp$[2**$i]
	./out $[2**$i] 200 400
done
echo "extracting times..."
echo "extracting times..." >> generalLog.log
TS=`cat tmp1`
TD=`cat tmp2`
TQ=`cat tmp4`
TH=`cat tmp8`
echo "Time for 4 experiments are: $TS, $TD, $TQ and $TH." >> generalLog.log

CS=$(echo "200*200*400/($TS)/1000000" | bc -l)
CD=$(echo "200*200*400/($TD)/1000000" | bc -l)
CQ=$(echo "200*200*400/($TQ)/1000000" | bc -l)
CH=$(echo "200*200*400/($TH)/1000000" | bc -l)
echo "Performance for 4 experiments are: $CS, $CD, $CQ and $CH Megabodies/second." >> generalLog.log

SA=$(echo "$TS/$TD" | bc -l)
SB=$(echo "$TS/$TQ" | bc -l)
SC=$(echo "$TS/$TH" | bc -l)

echo "Speedup is 1 vs 2 threads: $SA">>generalLog.log
echo "Speedup is 1 vs 4 threads: $SB">>generalLog.log
echo "Speedup is 1 vs 8 threads: $SC">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SA" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 2 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SB" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 4 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SC" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 8 returned $PF.">>generalLog.log
echo "___Done___"
echo "==================================================================================" >> generalLog.log
echo ""
echo "Dynamic, Fine grain:">> generalLog.log
echo ""
for i in `seq 0 3`; do
	echo number of Threads: $[2**$i]
	g++ -DPTYPE=dynamic -DFG -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out $[2**$i] 200 400 s > tmp$[2**$i]
	./out $[2**$i] 200 400
done
echo "extracting times..."
echo "extracting times..." >> generalLog.log
TS=`cat tmp1`
TD=`cat tmp2`
TQ=`cat tmp4`
TH=`cat tmp8`
echo "Time for 4 experiments are: $TS, $TD, $TQ and $TH." >> generalLog.log

CS=$(echo "200*200*400/($TS)/1000000" | bc -l)
CD=$(echo "200*200*400/($TD)/1000000" | bc -l)
CQ=$(echo "200*200*400/($TQ)/1000000" | bc -l)
CH=$(echo "200*200*400/($TH)/1000000" | bc -l)
echo "Performance for 4 experiments are: $CS, $CD, $CQ and $CH Megabodies/second." >> generalLog.log


SA=$(echo "$TS/$TD" | bc -l)
SB=$(echo "$TS/$TQ" | bc -l)
SC=$(echo "$TS/$TH" | bc -l)

echo "Speedup is 1 vs 2 threads: $SA">>generalLog.log
echo "Speedup is 1 vs 4 threads: $SB">>generalLog.log
echo "Speedup is 1 vs 8 threads: $SC">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SA" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 2 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SB" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 4 returned $PF.">>generalLog.log

AF=$(echo "4/3" | bc -l)
BF=$(echo "1/$SC" | bc -l)
CF=$(echo "1-$BF" | bc -l)
PF=$(echo "$AF*$CF" | bc -l)
echo "parallel fraction 1 vs 8 returned $PF.">>generalLog.log
echo "___Done___"
echo "==================================================================================" >> generalLog.log

echo "cleaning up ...">>generalLog.log
for i in `seq 0 3`; do
	rm tmp$[2**$i]
done
echo "Done"
echo "Done" >> generalLog.log
