IDIR = .
CC = gcc
CFLAGS = -I$(IDIR) -g -Wall
_DEPS = hw7.h
DEPS = $(pathsubst %, $(IDIR)/%, $(_DEPS))

OBJ = hw7.o util.o maurer.o millerrabin.o rndsearch.o primes.o trialdiv.c

hw7: $(OBJ)
	$(CC) $^ -o $@ -L/usr/lib/x86_64-linux-gnu/ -lcrypto

./%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o hw7
