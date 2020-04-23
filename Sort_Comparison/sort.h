#ifndef SORT_H
#define SORT_H

#define BOUND_MIN 10
#define BOUND_MAX 1000
#define LARGE_SIZE 15
#define MEDIAN_SIZE 10
#define SMALL_SIZE 5
#define ONE_SIZE 1
#define MAX_PRINT_ARRAY_SIZE 16

unsigned int seed;

int BitonicSort(int* array, int size);

int BubbleSort(int* arr, int size);

void GetRandomArray(int size, int* arr);

int GetRandomDefaultBound();

int GetRandomCustomBound(int lower, int upper);

void PrintArray(int* arr, int size);

void CopyArray(int* arr, int* arr_copy, int size);

void RandomArraySort(int lower, int upper, char* type);

void PrintSortArrayChange(int* pre_arr, int* post_arr, int size, char* type);

double GetPeriodSec(clock_t start, clock_t end);

void SortArray(int* arr, int size, char* type);

void DoExperiments();

#endif
