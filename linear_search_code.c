#include <stdio.h>

// Linear Search Algorithm
// Time Complexity: O(n)
// Space Complexity: O(1)

int linearSearch(int arr[], int n, int key)
{
    int i;

    // Traverse through all elements
    for (i = 0; i < n; i++)
    {
        // If element found, return its index
        if (arr[i] == key)
            return i;
    }

    // If element not found, return -1
    return -1;
}

int main()
{
    int arr[] = {2, 3, 4, 10, 40};
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