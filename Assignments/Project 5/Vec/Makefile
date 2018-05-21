all:
	clear
	g++  -DNUMS=100000 -fopenmp OMPUtil.cpp main.cpp -o out -g
	./out 4
	icpc -DNUMS=100000 -o out main.cpp OMPUtil.cpp -lm -openmp -align -qopt-report=3 -qopt-report-phase=vec -no-vec
	./out 4
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
	rm -rf out-*
	rm -rf main-*
	rm -f OMPUtil.optrpt
	rm -f main.optrpt
	rm *.log
	clear
