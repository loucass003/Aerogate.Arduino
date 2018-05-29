#include <stdio.h>
#include <stdlib.h>

void printBinary(int* n)
{
    int i = 0;
    while (i < 31 && !n[i])
        ++i;
    printf("0b");
    while (i < 32)
        printf("%d", n[i++]);
    printf("\n");
}

int* toBinary(int n)
{
    int *out = (int*)malloc(32 * sizeof(int));
    for (int i = 0; i < 32; ++i)
        out[31 - i] = (n >> i) & 1;
    return out;
}

int main(int ac, char** av)
{
    if (ac > 1)
    {
        int* i = toBinary(atoi(av[1]));
        printBinary(i);
        free(i);
    }
    return 0;
}
