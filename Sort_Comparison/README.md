#### This sort program aims to sort an array of integers, via two sort methods: bitonic sort and bubble sort.

- Use `make` to build code, use `./sort` to run code, use `make clean` to clean directory after using `make` many times, you might see some error like `make: Nothing to be done for 'all'.`

- No input needed for this program.

- Sample output in the end of the page.

- The files in this directory
	- Makefile: build and compile code
	- clint.py: check code style
	- sort.h: header file for sort program
	- sort.c: sort program script
	- main.c: main program to run sort script
	- writeup.md: an analysis of two sort methods
	- README.md: an intro about this program and directory

- header files for sort script include:
	- `stdio.h`
	- `stdlib.h`
	- `math.h`
	- `string.h`
	- `time.h`

- header files for main script include:
	- `stdio.h`
	- `time.h`
	- `sort.h`

- Output example:

```
Do simple sorting:
Small: 8 elements, 35 comparisons in bitonic sort in 0.000014 seconds, 28 comparions in bubble sort in 0.000000 seconds.

 - bitonic sort
Original array:      [10, 9, 8, 3, 6, 2, 4, 1]
Sorted array:        [1, 2, 3, 4, 6, 8, 9, 10]
 - bubble sort
Original array:      [10, 9, 8, 3, 6, 2, 4, 1]
Sorted array:        [1, 2, 3, 4, 6, 8, 9, 10]

Do some experiments:
---------------
SORTING:
---------------
This is the No.1 experiment.
Large: 1024 elements, 48116 comparisons in bitonic sort in 0.000319 seconds, 523776 comparions in bubble sort in 0.002218 seconds.
Median: 1024 elements, 48116 comparisons in bitonic sort in 0.000260 seconds, 523776 comparions in bubble sort in 0.002179 seconds.
Small: 2 elements, 1 comparisons in bitonic sort in 0.000001 seconds, 1 comparions in bubble sort in 0.000000 seconds.

 - bitonic sort
Original array:      [840, 953]
Sorted array:        [840, 953]
 - bubble sort
Original array:      [840, 953]
Sorted array:        [840, 953]

This is the No.2 experiment.
Large: 4096 elements, 278514 comparisons in bitonic sort in 0.001494 seconds, 8386560 comparions in bubble sort in 0.043848 seconds.
Median: 1024 elements, 48116 comparisons in bitonic sort in 0.000261 seconds, 523776 comparions in bubble sort in 0.002424 seconds.
Small: 2 elements, 1 comparisons in bitonic sort in 0.000000 seconds, 1 comparions in bubble sort in 0.000000 seconds.

 - bitonic sort
Original array:      [768, 91]
Sorted array:        [91, 768]
 - bubble sort
Original array:      [768, 91]
Sorted array:        [91, 768]

This is the No.3 experiment.
Large: 4096 elements, 278514 comparisons in bitonic sort in 0.001599 seconds, 8386560 comparions in bubble sort in 0.042175 seconds.
Median: 256 elements, 7670 comparisons in bitonic sort in 0.000048 seconds, 32640 comparions in bubble sort in 0.000195 seconds.
Small: 2 elements, 1 comparisons in bitonic sort in 0.000000 seconds, 1 comparions in bubble sort in 0.000000 seconds.

 - bitonic sort
Original array:      [629, 478]
Sorted array:        [478, 629]
 - bubble sort
Original array:      [629, 478]
Sorted array:        [478, 629]
```
