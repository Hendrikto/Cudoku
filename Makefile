seed = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4"

all: cudoku test

cudoku: src/Main.c
	gcc -Wall -O3 src/Main.c -o bin/cudoku

test: bin/cudoku
	valgrind bin/cudoku $(seed)
	valgrind --tool=cachegrind --branch-sim=yes bin/cudoku $(seed)

clean:
	rm bin/*
