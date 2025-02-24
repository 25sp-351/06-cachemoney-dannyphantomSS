CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic

all: main test

main: main.o money_to_words.o
	$(CC) $(CFLAGS) -o main main.o money_to_words.o

test: test_money_to_words.o money_to_words.o
	$(CC) $(CFLAGS) -o test test_money_to_words.o money_to_words.o

main.o: main.c money_to_words.h
	$(CC) $(CFLAGS) -c main.c

money_to_words.o: money_to_words.c money_to_words.h
	$(CC) $(CFLAGS) -c money_to_words.c

test_money_to_words.o: test_money_to_words.c money_to_words.h
	$(CC) $(CFLAGS) -c test_money_to_words.c

clean:
	rm -f main test *.o

