CC=gcc
DEFS=-D_XOPEN_SOURCE=500 -D_BSD_SOURCE -DENDEBUG
CFLAGS=-Wall -g -lcrypt -std=c99 -pedantic $(DEFS)
LIBS=-lm -lcrypt

all: encr

encr: encr.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o.: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f encr
