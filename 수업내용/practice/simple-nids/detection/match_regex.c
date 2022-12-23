#include "match_regex.h"
#include <regex.h>

int match_regex(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet)
{
    regex_t rx;

    if (regcomp(&rx, rule->regex, REG_EXTENDED) != 0) {
        printf("Failed to compile %s\n", rule->regex);
        return 0;
    }

    if (regexec(&rx, packet->payload, 0, NULL, 0) == 0) {
        regfree(&rx);
        return 1;
    }

    regfree(&rx);

    return 0;
}
