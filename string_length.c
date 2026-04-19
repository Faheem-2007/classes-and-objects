#include <stdio.h>
#include <string.h>

int getStringLength(char *str)
{
    return strlen(str);
}

int main()
{
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character if present
    if (str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }

    int length = getStringLength(str);
    printf("Length of string: %d\n", length);

    return 0;
}
