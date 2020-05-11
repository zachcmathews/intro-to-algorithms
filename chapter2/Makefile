all: build insertion-sort linear-search binary-addition selection-sort merge-sort

insertion-sort: insertion-sort.c
	gcc -Wall insertion-sort.c -o build/insertion-sort

linear-search: linear-search.c
	gcc -Wall linear-search.c -o build/linear-search

binary-addition: binary-addition.c
	gcc -Wall binary-addition.c -o build/binary-addition

selection-sort: selection-sort.c
	gcc -Wall selection-sort.c -o build/selection-sort

merge-sort: merge-sort.c
	gcc -Wall merge-sort.c -lm -o build/merge-sort

build:
	mkdir build

clean:
	rm -rfv build
