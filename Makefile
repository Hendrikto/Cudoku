all: cudoku test

cudoku: src/Main.c
	gcc -Wall -O3 src/Main.c -o bin/cudoku

test: bin/cudoku
	valgrind bin/cudoku

clean:
	rm bin/*
