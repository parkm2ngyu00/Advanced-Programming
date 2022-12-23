#include "context.h"
#include <getopt.h>

int init_context(struct context_t *ctx, int argc, char **argv)
{
    // 구현

    // command-line arguments

    char string_match[MAX_STRING] = {0};
    int  regex_match = 0;

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
            memset(ctx->interface, 0, MAX_STRING);
            strcpy(ctx->interface, optarg);
            break;
        case 'r':
            memset(ctx->rule_file, 0, MAX_STRING);
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
    return 0;
}
