#include "match_string1.h"

int skip[MAX_STRING];

static void make_skip_table(char *str, int len)
{
    memset(skip, 0, sizeof(int) * MAX_STRING);

    int i, j = 0;
    for (i=1; i<len; i++) {
        while (j>0 && str[i] != str[j]) {
            j = skip[j - 1];
        }
        if (str[i] == str[j])
            skip[i] = j++;
    }
}

static int do_kmp(char *str, int slen, char *pattern, int plen)
{
    int i, j = 0;

    make_skip_table(pattern, plen);

    for (i=0; i<slen; i++) {
        while (j>0 && str[i] != pattern[j]) {
            j = skip[j - 1];
        }

        if (str[i] == pattern[j]) {
            if (j == plen - 1) {
                return 1;
            } else {
                j++;
            }
        }
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
            if (packet->payload_len > 0 && do_kmp(packet->payload, packet->payload_len, rule->content, strlen(rule->content)) > 0) {
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

            if (rule->src_ip || rule->src_port || rule->dst_ip || rule->dst_port) {
                return rule;
            }
        }

        rule = rule->next;
    }

    return NULL;
}

struct rule_t * match_string1(struct context_t *ctx, struct packet_t *packet)
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
