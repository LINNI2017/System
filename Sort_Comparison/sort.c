#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "sort.h"

/*
 * Returns the number of comparisons in the bitonic sort
 * of the given array of the given size, sorts the given
 * array ascendingly via bitonic sort.
 * @param array - an array of integers
 * @param int - the size of the array
 * @return the number of comparisons in the bitonic sort
 */
int BitonicSort(int* array, int size) {
    int cnt = 0;
    int left = floor(size / 2);
    while (left > 0) {
        int q = floor(size / 2);
        int r = 0;
        int gap = left;
        while (q >= left) {
            for (int i = 0; i < size - gap; i++) {
                if ((i & left) == r) {
                    if (array[i] > array[i + gap]) {
                        int temp = array[i];
                        array[i] = array[i + gap];
                        array[i + gap] = temp;
                    }  
                }
                cnt++;
            }
            gap = q - left;
            q = floor(q / 2);
            r = left;
        }
        left = floor(left / 2);
    }
    return cnt;
}

/*
 * Returns the number of comparisons in the bubble sort
 * of the given array of the given size, sorts the given
 * array ascendingly via bubble sort.
 * @param array - an array of integers
 * @param size - the size of the array
 * @return the number of comparisons in the bubble sort
 */
int BubbleSort(int* arr, int size) {
    int cnt = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            cnt++;
        }
    }
    return cnt;
}


/*
 * Returns a random number in the default range.
 * @return a random number in the default range
 */
int GetRandomDefaultBound() {
    return GetRandomCustomBound(BOUND_MIN, BOUND_MAX);
}

/*
 * Returns a random number in the customized range
 * between the given lower and upper bounds.
 * @param lower - an integer represents lower bound of the size of the array
 * @param upper - an integer represents upper bound of the size of the array
 * @return a random number in the customized range
 */
int GetRandomCustomBound(int lower, int upper) {
    seed++;
    return (rand_r(&seed) % (upper - lower + 1)) + lower;
}

/*
 * Builds up an array of random integers of the given size,
 * the random integer is in the default range.
 * @param size - the size of the array
 * @param arr -  an empty array of integers
 */
void GetRandomArray(int size, int* arr) {
    for (int i = 0; i < size; i++) {
        arr[i] = GetRandomDefaultBound();
    }
}

/*
 * Prints the given array of the given size.
 * @param arr - an array of integers
 * @param size - the size of the array
 */
void PrintArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}

/*
 * Copy the given array in the given array copy, both in the given size.
 * @param arr - an array of integers as copy source
 * @param arr_copy - an empty array of integers as copy destination
 * @param size - the size of the array
 */
void CopyArray(int* arr, int* arr_copy, int size) {
    for (int i = 0; i < size; i++) {
        arr_copy[i] = arr[i];
    }
}

/*
 * Builds up and sorts a random array ascendingly,
 * composed of random integers of a random size in the given range,
 * prints out the number of comparisons in bitonic and bubble sort of the array,
 * prints out the small size array.
 * @param lower - an integer represents lower bound of the size of the array
 * @param upper - an integer represents upper bound of the size of the array
 * @param type - a String of the type of the experiment
 */
void RandomArraySort(int lower, int upper, char* type) {
    const int kSize = pow(2, GetRandomCustomBound(lower, upper));
    int arr[kSize];
    GetRandomArray(kSize, arr);
    SortArray(arr, kSize, type);
}

/*
 * Prints out original array and ascending-sorted array of the given size
 * via the given type of sort.
 * @param pre_arr - the original array of integers
 * @param post_arr - the ascending-sorted array of integers
 * @param size - the array size
 * @param type - the sort type
 */
void PrintSortArrayChange(int* pre_arr, int* post_arr, int size, char* type) {
    printf(" - %s sort\n", type);
    printf("Original array:      ");
    PrintArray(pre_arr, size);
    printf("Sorted array:        ");
    PrintArray(post_arr, size);
}

/*
 * Return the given time difference as period in seconds.
 * @param start - a clock time of start
 * @param end - a clock time of end
 * @return a time difference between end and start in seconds
 */
double GetPeriodSec(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/*
 * Prints out sorted array and the number of comparisons in sorting.
 * @param arr - an array of integers
 * @param size - the array size
 * @param type - the array size type, i.e. small, median, large
 */
void SortArray(int* arr, int size, char* type) {
    const int kSize = size;
    int arr_bitonic[kSize];
    int arr_bubble[kSize];
    CopyArray(arr, arr_bitonic, kSize);
    CopyArray(arr, arr_bubble, kSize);

    clock_t bitonic_start = clock();
    int bitonic_cnt = BitonicSort(arr_bitonic, size);
    clock_t bitonic_end = clock();
    double bitonic_time = GetPeriodSec(bitonic_start, bitonic_end);

    clock_t bubble_start = clock();
    int bubble_cnt = BubbleSort(arr_bubble, size);
    clock_t bubble_end = clock();
    double bubble_time = GetPeriodSec(bubble_start, bubble_end);

    printf("%s: %d elements, ", type, size);
    printf("%d comparisons in bitonic sort in %f seconds, ",
        bitonic_cnt, bitonic_time);
    printf("%d comparions in bubble sort in %f seconds.\n",
        bubble_cnt, bubble_time);

    if (size <= MAX_PRINT_ARRAY_SIZE) {
        printf("\n");
        PrintSortArrayChange(arr, arr_bitonic, size, "bitonic");
        PrintSortArrayChange(arr, arr_bubble, size, "bubble");
    }
}

/*
 * Does the given times of experiments, includes small, median and large
 * sizes of random size random integers filled arrays, sorts them ascendingly
 * via bitonic and bubble sorts, prints out the number of comparisons in both
 * sort methods separately.
 * @param times - the times of experiments
 */
void DoExperiments(int times) {
    printf("---------------\nSORTING:\n---------------\n");
    for (int i = 1; i < times + 1; i++) {
        printf("This is the No.%d experiment.\n", i);
        RandomArraySort(MEDIAN_SIZE, LARGE_SIZE, "Large");
        RandomArraySort(SMALL_SIZE, MEDIAN_SIZE, "Median");
        RandomArraySort(ONE_SIZE, SMALL_SIZE, "Small");
        printf("\n");
    }
}
