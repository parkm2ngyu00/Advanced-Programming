#include "context.h"
#include <getopt.h>

int init_context(struct context_t *ctx, int argc, char **argv)
{
    int interface_flag = -1;

    // command-line arguments

    char string_match[MAX_STRING] = {0};
    int  regex_match = 0;

    static struct option long_options[] = {
        {"interface", required_argument, 0, 'i'},
        {"file", required_argument, 0, 'f'},
        {"match", required_argument, 0, 'm'},
        {"regex", no_argument, 0, 'r'},
        {"log", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };
    int option_index = 0;

    int opt;
    while ((opt = getopt_long(argc, argv, "i:f:m:rl:", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'i':
            interface_flag = 1;
            memset(ctx->source, 0, MAX_STRING);
            strcpy(ctx->source, optarg);
            break;
        case 'f':
            if (ctx->source[0] == 0) {
                interface_flag = 0;
                strcpy(ctx->source, optarg);
            }
            break;
        case 'm':
            strcpy(string_match, optarg);
            break;
        case 'r':
            regex_match = 1;
            break;
        case 'l':
            strcpy(ctx->log, optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            return -1;
        }
    }

    printf("[INFO] Parsed command-line arguments\n");

    printf("  - Source: %s\n", (strlen(ctx->source) == 0) ? "Default" : ctx->source);
    printf("  - String Match: %s\n", string_match);
    printf("  - Regex Match: %s\n", (regex_match == 0) ? "False" : "True");
    printf("  - Log: %s\n", (strlen(ctx->log) == 0) ? "Stdout" : ctx->log);

    // function pointer configuration

    if (interface_flag) {
        ctx->reception_func = pkt_live;
        ctx->reception_destroy_func = destroy_pkt_live;
    } else {
        ctx->reception_func = pkt_file;
        ctx->reception_destroy_func = destroy_pkt_file;
    }

    ctx->decoder_func = decoder;

    if (strcmp(string_match, "string1") == 0) {
        ctx->string_match_func = match_string1;
    } else if (strcmp(string_match, "string2") == 0) {
        ctx->string_match_func = match_string2;
    } else {
        ctx->string_match_func = match_string1;
    }

    if (regex_match) {
        ctx->regex_match_func = match_regex;
    }

    if (strcmp(ctx->log, "stdout") != 0) {
        ctx->log_func = log_file;
    } else {
        ctx->log_func = log_stdout;
    }

    return 0;
}
