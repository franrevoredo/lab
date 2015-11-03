CC=gcc
CFLAGS=-g -Wall -pthread
TARGETS=tp5

all: $(TARGETS)

tp5: main.c http_worker.c checkget.c checkext.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) *~ core*

