CC=gcc

threads:
	$(CC) -pthread -o part1.o part1.c -std=c99
	$(CC) -pthread -D PTHREAD_SYNC -o part2.o part2.c -std=c99

clean:
	rm part1.o part2.o
