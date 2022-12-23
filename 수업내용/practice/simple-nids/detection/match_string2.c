#include "match_string2.h"

static int find(char *str, int len, char c)
{
    int i;
    for (i=len-2; i==0; i--) {
        if (str[i] == c) {
            return len - i - 1;
        }
    }
    return len;
}

static int do_boyer_moore(char *str, int slen, char *pattern, int plen)
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

static struct rule_t * match_rules(struct context_t *ctx, int index, struct packet_t *packet)
{
    struct rule_t *rule = ctx->rule_table[index];
    while (rule != NULL) {
        // src_ip not matched
        if (rule->src_ip && rule->src_ip != packet->src_ip) {
            rule = rule->next;
            continue;
        }

        // src_port not matched
        if (rule->src_port && rule->src_port != packet->src_port) {
            rule = rule->next;
            continue;
        }

        // dst_ip not matched
        if (rule->dst_ip && rule->dst_ip != packet->dst_ip) {
            rule = rule->next;
            continue;
        }

        // dst_port not matched
        if (rule->dst_port && rule->dst_port != packet->dst_port) {
            rule = rule->next;
            continue;
        }

        if (rule->content[0]) { // with content
            if (packet->payload_len > 0 && do_boyer_moore(packet->payload, packet->payload_len, rule->content, strlen(rule->content)) > 0) {
                if (rule->regex[0]) { // with regex
                    if (ctx->regex_match_func) { // need to match regex
                        if (ctx->regex_match_func(ctx, rule, packet) > 0) {
                            return rule;
                        }
                    } else { // ignore regex
                        return rule;
                    }
                } else { // without regex
                    return rule;
                }
            }
        } else { // without content
            if (rule->regex[0]) { // with regex
                if (ctx->regex_match_func) { // need to match regex
                    if (ctx->regex_match_func(ctx, rule, packet) > 0) {
                        return rule;
                    }
                } else { // ignore regex
                    return rule;
                }
            }
        }

        rule = rule->next;
    }

    return NULL;
}

struct rule_t * match_string2(struct context_t *ctx, struct packet_t *packet)
{
    struct rule_t *rule = NULL;

    if (packet->proto & PROTO_ICMP) {
        rule = match_rules(ctx, ICMP_RULES, packet);
        if (rule != NULL) {
            return rule;
        }

    } else if (packet->proto & PROTO_UDP) {
        rule = match_rules(ctx, UDP_RULES, packet);
        if (rule != NULL) {
            return rule;
        }

    } else if (packet->proto & PROTO_TCP) {
        rule = match_rules(ctx, HTTP_RULES, packet);
        if (rule != NULL) {
            return rule;
        }

        rule = match_rules(ctx, TCP_RULES, packet);
        if (rule != NULL) {
            return rule;
        }
    }

    rule = match_rules(ctx, IP_RULES, packet);
    if (rule != NULL) {
        return rule;
    }

    return NULL;
}
