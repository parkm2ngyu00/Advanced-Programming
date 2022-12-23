#include "context.h"
#include <getopt.h>

int init_context(struct context_t *ctx, int argc, char **argv)
{
    static struct option long_options[] = {
        {"interface", required_argument, 0, 'i'},
        {"rule", required_argument, 0, 'r'},
        {"debug", no_argument, 0, 'd'},
        {0, 0, 0, 0}
    };
    int option_index = 0;

    int opt;
    while ((opt = getopt_long(argc, argv, "i:r:d", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'i':
            strcpy(ctx->interface, optarg);
            break;
        case 'r':
            strcpy(ctx->rule_file, optarg);
            break;
        case 'd':
            ctx->debug = 1;
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            return -1;
        }
    }

    if (ctx->interface[0] == 0) {
        printf("Missing option: -i\n");
        return -1;
    }

    if (ctx->rule_file[0] == 0) {
        printf("Missing option: -r\n");
        return -1;
    }

    return 0;
}
