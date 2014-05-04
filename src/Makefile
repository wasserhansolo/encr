CC=gcc
DEFS=-D_XOPEN_SOURCE=500 -D_BSD_SOURCE -DENDEBUG
CFLAGS=-Wall -g -std=c99 -pedantic $(DEFS)

all: encr

encr: encr.c
	$(CC) $(LDFLAGS) -o $@ $^

%.o.: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f encr
