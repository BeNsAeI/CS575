all:
	clear
	./run.sh
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
