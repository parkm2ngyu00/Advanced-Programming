#include "stats.h"

int init_stats(struct context_t *ctx)
{
    ctx->stats = (struct stats_t **)malloc(sizeof(struct stats_t *) * NUM_OF_SERVICES);
    memset(ctx->stats, 0, sizeof(struct stats_t *) * NUM_OF_SERVICES);

    printf("Initialized stats\n");

    return 0;
}

int destroy_stats(struct context_t *ctx)
{
    int idx;
    for (idx=0; idx<NUM_OF_SERVICES; idx++) {
        int cnt = 1;

        switch(idx) {
        case 0:
            printf("Service: md5\n");
            break;
        case 1:
            printf("Service: sha1\n");
            break;
        case 2:
            printf("Service: sha256\n");
            break;
        case 3:
            printf("Service: sha512\n");
            break;
        }

        struct stats_t *stat = ctx->stats[idx];
        while (stat != NULL) {
            struct stats_t *temp = stat;
            stat = stat->next;

            printf("  [#%d]\n", cnt++);
            printf("  Resource: %s\n", temp->resource);
            printf("  Content: %s\n", temp->content);
            printf("  Count: %d\n", temp->count);

            free(temp);
        }
    }

    free(ctx->stats);

    printf("Destroyed stats\n");

    return 0;
}
