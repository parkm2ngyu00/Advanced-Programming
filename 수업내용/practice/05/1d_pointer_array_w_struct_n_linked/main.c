#include <stdio.h>
#include <stdlib.h>

struct sample_t {
    int value;
    struct sample_t *next;
};

int main()
{
    int n = 10, m = 5;

    struct sample_t **p = (struct sample_t **)malloc(sizeof(struct sample_t *) * n);

    int i;
    for (i=0; i<n; i++) {
        p[i] = (struct sample_t *)malloc(sizeof(struct sample_t));

        // just in case
        p[i]->next = NULL;

        int j;
        for (j=0; j<m; j++) {
            struct sample_t *sample = (struct sample_t *)malloc(sizeof(struct sample_t));
            sample->next = p[i];
            p[i] = sample;
        }
    }

    for (i=0; i<n; i++) {
        struct sample_t *sample = p[i];
        while (sample != NULL) {
            printf("%d: %p, %d\n", i, sample, sample->value);
            sample = sample->next;
        }
    }

    for (i=0; i<n; i++) {
        struct sample_t *sample = p[i];

        while (sample != NULL) {
            struct sample_t *temp = sample;
            sample = sample->next;
            free(temp);
        }
    }

    free(p);

    return 0;
}
