#include <stdio.h>
#include <stdlib.h>

struct sample_t {
    int value;
};

int main()
{
    int n = 10;

    struct sample_t **p = (struct sample_t **)malloc(sizeof(struct sample_t *) * n);

    int i;
    for (i=0; i<n; i++) {
        p[i] = (struct sample_t *)malloc(sizeof(struct sample_t));
    }

    for (i=0; i<n; i++) {
        printf("%d: %p, %d\n", i, p[i], p[i]->value);
    }

    for (i=0; i<n; i++) {
        free(p[i]);
    }

    free(p);

    return 0;
}
