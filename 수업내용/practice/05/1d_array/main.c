#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 10;

    int *p = (int *)malloc(sizeof(int) * n);

    int i;
    for (i=0; i<n; i++) {
        printf("%d: %d\n", i, p[i]);
    }

    free(p);

    return 0;
}
