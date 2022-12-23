#pragma once

#include "common.h"

struct rule_t {
    char service[MAX_STRING];
    char resource[MAX_STRING];
    char message[MAX_STRING];

    struct rule_t *next;
};

struct stats_t {
    char service[MAX_STRING];
    char resource[MAX_STRING];
    char content[MAX_STRING];

    int count;

    struct stats_t *next;
};

struct context_t {
    char interface[MAX_STRING];
    char rule_file[MAX_STRING];

    int debug;

    struct rule_t *rules;
    struct stats_t **stats;
};

int init_context(struct context_t *ctx, int argc, char **argv);

int init_rules(struct context_t *ctx);
int destroy_rules(struct context_t *ctx);
int load_rules(struct context_t *ctx);

int start_to_capture(struct context_t *ctx);
int stop_capturing();

int decode_packet(struct context_t *ctx, const u_char *pkt, int len);

struct rule_t *match_rules(struct context_t *ctx, struct stats_t *stats, char *payload, int payload_len);

int init_stats(struct context_t *ctx);
int destroy_stats(struct context_t *ctx);
