CC=gcc
CFLAGS=-g -Wall -pthread
TARGETS=server

all: $(TARGETS)

server: main.c http_worker.c http_response.c checkget.c thread.c checkext.c parse.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) *~ core*

