all:
	clear
	g++ -fopenmp OMPUtil.cpp first.cpp -o out -lOpenCL -g
#	./out 4
#	./out 4 > log.txt
#	./out 4 s
#	./run.sh
bench:
	./out &
	nice -5 ./out &
	nice -10 ./out &
	nice -15 ./out &
	nice -19 ./out &
kill:
	make bench
	make bench
	make bench
clean:
	rm -rf out
	rm *.log
