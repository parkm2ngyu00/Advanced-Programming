#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 10;

    int **p = (int **)malloc(sizeof(int *) * n);

    int i;
    for (i=0; i<n; i++) {
        p[i] = (int *)malloc(sizeof(int));
    }

    for (i=0; i<n; i++) {
        printf("%d: %p, %d\n", i, p[i], *p[i]);
    }

    for (i=0; i<n; i++) {
        free(p[i]);
    }

    free(p);

    return 0;
}
