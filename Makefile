all: cudoku

cudoku: src/Main.c
	gcc -Wall -O3 src/Main.c -o bin/cudoku

clean:
	rm bin/*
