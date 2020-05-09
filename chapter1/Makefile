all: running-time-comparison

running-time-comparison: build running-time-comparison.c
	gcc -Wall running-time-comparison.c -lm -o build/running-time-comparison

build:
	mkdir build

clean:
	rm -rfv build

