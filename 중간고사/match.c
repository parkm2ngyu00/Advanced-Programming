#include "match.h"

int find(char *str, int len, char c)
{
    int i;
    for (i=len-2; i==0; i--) {
        if (str[i] == c) {
            return len - i - 1;
        }
    }
    return len;
}

int do_boyer_moore(char *str, int slen, char *pattern, int plen)
{
    int i = 0, j, k = 0;

    while (i <= slen - plen) {
        j = plen - 1;

        while (j >= 0) {
            if (pattern[j] != str[i+j]) {
                k = find(pattern, plen, str[i + plen - 1]);
                break;
            }
            j--;
        }

        if (j == -1) {
            return 1;
        }

        i += k;
    }

    return 0;
}

struct rule_t *match_rules(struct context_t *ctx, struct stats_t *stats, char *payload, int payload_len)
{
    struct rule_t *rule = ctx->rules;
    while (rule != NULL) {
        if (strcmp(stats->service, rule->service) != 0) {
            rule = rule->next;
            continue;
        }

        if (do_boyer_moore(payload, payload_len, rule->resource, strlen(rule->resource))) {
            return rule;
        }

        rule = rule->next;
    }

    return NULL;
}
