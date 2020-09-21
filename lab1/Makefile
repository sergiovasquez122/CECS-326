CC=gcc

threads:
	$(CC) -pthread -o part1.o part1.c
	$(CC) -pthread -DPTHREAD_SYNC -o part2.o part2.c

clean:
	rm part1.o part2.o
