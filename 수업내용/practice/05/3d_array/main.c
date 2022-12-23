#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 3, y = 4, z = 5;

    int ***p = (int ***)malloc(sizeof(int **) * x);

    int i;
    for (i=0; i<x; i++) {
        p[i] = (int **)malloc(sizeof(int *) * y);

        int j;
        for (j=0; j<y; j++) {
            p[i][j] = (int *)malloc(sizeof(int) * z);
        }
    }

    for (i=0; i<x; i++) {
        int j;
        for (j=0; j<y; j++) {
            int k;
            for (k=0; k<z; k++) {
                printf("%d, %d, %d: %d\n", i, j, k, p[i][j][k]);
            }
        }
    }

    for (i=0; i<x; i++) {
        int j;
        for (j=0; j<y; j++) {
            free(p[i][j]);
        }

        free(p[i]);
    }

    free(p);

    return 0;
}
