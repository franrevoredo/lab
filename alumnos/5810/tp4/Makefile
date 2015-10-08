CC=gcc
CFLAGS=-g -Wall
TARGETS=tp4

all: $(TARGETS)

tp4: main.c http_worker.c checkget.c checkext.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) *~ core*

