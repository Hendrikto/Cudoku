CFLAGS += -Wall -Wextra

seed = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4"

all: cudoku

%: %.c
	$(CC) $(CFLAGS) $< -o $@

test: cudoku
	valgrind bin/cudoku $(seed)
	valgrind --tool=cachegrind --branch-sim=yes bin/cudoku $(seed)

clean:
	rm -f cudoku
