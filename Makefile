CFLAGS = -pedantic -O0 -Wall
CFLAGS_ISO90 = -ansi -pedantic -O0 -Wall
DFLAGS = -g
PROGS = psucrypt

all: psucrypt

psucrypt: psucrypt.c
	gcc *.c $(CFLAGS_ISO90) $(DFLAGS) -o psucrypt

clean:
	rm -f $(PROGS) *.o

zip:
	zip rename_me.zip Makefile psucrypt.c typescript
