#include <stdio.h>

int main()
{
    int x;
    int *p = &x; // p now points to valid memory

    scanf("%d", &x);
    printf("%d\n", *p); // value
    printf("%p\n", p);  // address

    return 0;
}