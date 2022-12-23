#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 2, m = 5;

    int **p = (int **)malloc(sizeof(int *) * n);

    int i;
    for (i=0; i<n; i++) {
        p[i] = (int *)malloc(sizeof(int) * m);
    }

    for (i=0; i<n; i++) {
        int j;
        for (j=0; j<m; j++) {
            printf("%d, %d: %d\n", i, j, p[i][j]);
        }
    }

    for (i=0; i<n; i++) {
        free(p[i]);
    }

    free(p);

    return 0;
}
