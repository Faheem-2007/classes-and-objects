#include <stdio.h>

// Linear Search - searches through unsorted array sequentially
int linearSearch(int arr[], int n, int key)
{
    int i;

    // Search for key from start to end
    for (i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return i; // Return index if found
    }

    return -1; // Return -1 if not found
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key;

    printf("Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Enter element to search: ");
    scanf("%d", &key);

    int result = linearSearch(arr, n, key);

    if (result != -1)
        printf("Element found at index: %d\n", result);
    else
        printf("Element not found in array\n");

    return 0;
}