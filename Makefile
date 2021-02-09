FLAGS = -ansi -pedantic -O0 -Wall
DFLAGS = -g
PROGS = psucrypt

all: psucrypt

psucrypt: psucrypt.c
	gcc psucrypt.c $(CFLAGS) $(DFLAGS) -o psucrypt

clean:
	rm -f $(PROGS) *.o psucrypt

zip:
	zip rename_me.zip Makefile psucrypt.c typescript
