CC=gcc
CFLAGS=-g -Wall 
TARGETS=tp2

all: $(TARGETS)

tp2: main.c hijo.c rot13.c nieto.c comparar.c
	$(CC) $(CFLAGS) -o $@ $^
testrot:
	./tp2 -r < ejemplo.txt	
testfiltrar:
	./tp2 -p la < ejemplo2.txt
clean:
	rm -f $(TARGETS) *~ core*

