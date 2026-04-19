#include <stdio.h>

// Function receives pointer â€” it CAN modify the original array
void doubleAll(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;          // same as *(arr + i) *= 2
    }
}

// 2D array with pointer â€” must specify column count
void print2D(int (*matrix)[3], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5};
    int size = sizeof(nums)/sizeof(nums[0]);

    // Array name = pointer to first element (decays)
    int *p = nums;   // valid â€” no & needed
    printf("First element via pointer: %d\n", *p);   // 1

    doubleAll(nums, size);   // nums is passed as pointer
    for (int i=0; i<size; i++) printf("%d ", nums[i]);
    printf("\n");  // 2 4 6 8 10 â€” original array modified!

    // String is a char array â€” same rules
    char str[] = "Hello";
    char *sp = str;
    while (*sp != '\0') {
        printf("%c", *sp);
        sp++;
    }
    printf("\n");  // Hello

    // Array of pointers â€” useful for strings
    char *names[] = {"Alice", "Bob", "Charlie"};
    for (int i=0; i<3; i++) printf("%s\n", names[i]);

    // 2D matrix
    int grid[2][3] = {{1,2,3},{4,5,6}};
    print2D(grid, 2);
    return 0;
}