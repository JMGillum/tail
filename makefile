all: a.out
clean:
	rm -f a.out main.o tail.o functions.o

$CC=gcc
$CFLAGS=-WALL

%.o: %.c
	$(CC) $(CFLAGS) -c $<

a.out: main.o tail.o functions.o
	$(CC) $(CFLAGS) $< tail.o functions.o

main.o: functions.c tail.h
tail.o: functions.c tail.h
functions.o: functions.h


a.out: