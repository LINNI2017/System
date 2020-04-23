#include <stdio.h>
#include <time.h>
#include "sort.h"

int main() {
    seed = time(0);

    printf("\nDo simple sorting:\n");
    const int kSize = 8;
    int arr[kSize] = {10, 9, 8, 3, 6, 2, 4, 1};
    SortArray(arr, kSize, "Small");

    printf("\nDo some experiments:\n");
    DoExperiments(3);

    return -1;
}
