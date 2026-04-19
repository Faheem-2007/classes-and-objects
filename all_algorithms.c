#include <stdio.h>

// ============= SELECTION SORT =============
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// ============= BUBBLE SORT =============
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

// ============= LINEAR SEARCH =============
int linearSearch(int arr[], int n, int key)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// ============= BINARY SEARCH =============
int binarySearch(int arr[], int l, int r, int key)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] > key)
            return binarySearch(arr, l, mid - 1, key);

        return binarySearch(arr, mid + 1, r, key);
    }

    return -1;
}

// ============= UTILITY FUNCTION =============
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// ============= MAIN =============
int main()
{
    int n, i, choice, key;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\n========== MENU ==========\n");
    printf("1. Selection Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Linear Search\n");
    printf("4. Binary Search (requires sorted array)\n");
    printf("5. Exit\n");
    printf("=========================\n");

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int temp[n];
            copyArray(arr, temp, n);
            selectionSort(temp, n);
            printf("Array after Selection Sort: ");
            printArray(temp, n);
            break;
        }
        case 2:
        {
            int temp[n];
            copyArray(arr, temp, n);
            bubbleSort(temp, n);
            printf("Array after Bubble Sort: ");
            printArray(temp, n);
            break;
        }
        case 3:
        {
            printf("Enter the element to search: ");
            scanf("%d", &key);
            int result = linearSearch(arr, n, key);
            if (result != -1)
                printf("Element found at index %d\n", result);
            else
                printf("Element not found\n");
            break;
        }
        case 4:
        {
            int temp[n];
            copyArray(arr, temp, n);
            bubbleSort(temp, n); // Sort first
            printf("Array after sorting: ");
            printArray(temp, n);
            printf("Enter the element to search: ");
            scanf("%d", &key);
            int result = binarySearch(temp, 0, n - 1, key);
            if (result != -1)
                printf("Element found at index %d\n", result);
            else
                printf("Element not found\n");
            break;
        }
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}