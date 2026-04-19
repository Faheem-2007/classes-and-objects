#include <stdio.h>

// Binary Search - efficiently searches through sorted array
int binarySearch(int arr[], int l, int r, int key)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        // If element is present at the middle
        if (arr[mid] == key)
            return mid;

        // If element is smaller, search in left subarray
        if (arr[mid] > key)
            return binarySearch(arr, l, mid - 1, key);

        // If element is larger, search in right subarray
        return binarySearch(arr, mid + 1, r, key);
    }

    return -1; // Element not found
}

int main()
{
    // Binary search requires sorted array
    int arr[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key;

    printf("Array (must be sorted): ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Enter element to search: ");
    scanf("%d", &key);

    int result = binarySearch(arr, 0, n - 1, key);

    if (result != -1)
        printf("Element found at index: %d\n", result);
    else
        printf("Element not found in array\n");

    return 0;
}