#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 5, m = 3;

    int ***p = (int ***)malloc(sizeof(int **) * n);

    int i;
    for (i=0; i<n; i++) {
        p[i] = (int **)malloc(sizeof(int *) * m);

        int j;
        for (j=0; j<m; j++) {
            p[i][j] = (int *)malloc(sizeof(int));
        }
    }

    for (i=0; i<n; i++) {
        int j;
        for (j=0; j<m; j++) {
            printf("%d, %d: %p, %d\n", i, j, p[i][j], *p[i][j]);
        }
    }

    for (i=0; i<n; i++) {
        int j;
        for (j=0; j<m; j++) {
            free(p[i][j]);
        }

        free(p[i]);
    }

    free(p);

    return 0;
}
