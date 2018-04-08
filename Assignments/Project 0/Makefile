all:
	g++ -fopenmp OMPUtil.cpp main.cpp -o out
#	./out 1
#	./out 4
#	./out 1 s > tmp1
#	./out 4 s > tmp2
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
