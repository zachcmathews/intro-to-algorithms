all: running-time-comparison

running-time-comparison: build running-time-comparison.c
	gcc -Wall -lm running-time-comparison.c -o build/running-time-comparison

build:
	mkdir build

clean:
	rm -rfv build

