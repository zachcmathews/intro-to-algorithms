CC=gcc
C_OPTS=-std=c99 -Wpedantic -Wall -Wextra -g 

.PHONY: clean all

all: bin \
     bin/max-subarray-brute \
     bin/max-subarray \
     bin/matrix-multiplication \
     bin/recursive-matrix-multiplication \
     bin/strassen-matrix-multiplication

bin/max-subarray-brute: max-subarray-brute.c
	$(CC) $(C_OPTS) $< -o $@

bin/max-subarray: max-subarray.c
	$(CC) $(C_OPTS) $< -o $@

bin/matrix-multiplication: matrix-multiplication.c
	$(CC) $(C_OPTS) $< -o $@

bin/recursive-matrix-multiplication: recursive-matrix-multiplication.c
	$(CC) $(C_OPTS) $< -o $@

bin/strassen-matrix-multiplication: strassen-matrix-multiplication.c
	$(CC) $(C_OPTS) $< -o $@

bin:
	mkdir bin

clean:
	rm -rfv bin/
