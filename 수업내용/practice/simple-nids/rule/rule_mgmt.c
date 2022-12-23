#include "rule_mgmt.h"

void print_rule(struct rule_t *rule)
{
    if (rule != NULL) {
        if (rule->proto & PROTO_HTTP) {
            printf("  Protocol: %d, SrcIP: %d, DstIP: %d, SrcPort: %d, DstPort: %d, Msg: %s\n", 
                    rule->proto, rule->src_ip, rule->dst_ip, rule->src_port, rule->dst_port, rule->message);

            if (rule->content[0]) {
                printf("    Content: %s\n", rule->content);
            }

            if (rule->regex[0]) {
                printf("    Regex: %s\n", rule->regex);
            }

            if (rule->method[0]) {
                printf("    Method: %s\n", rule->method);
            }

        } else if (rule->proto & PROTO_ICMP) {
            printf("  Protocol: %d, SrcIP: %d, DstIP: %d, Type: %d, Code: %d, Msg: %s\n",
                    rule->proto, rule->src_ip, rule->dst_ip, rule->icmp_type, rule->icmp_code, rule->message);

            if (rule->content[0]) {
                printf("    Content: %s\n", rule->content);
            }

            if (rule->regex[0]) {
                printf("    Regex: %s\n", rule->regex);
            }

        } else { // PROTO_TCP | PROTO_UDP | PROTO_IPV4
            printf("  Protocol: %d, SrcIP: %d, DstIP: %d, SrcPort: %d, DstPort: %d, Msg: %s\n",
                    rule->proto, rule->src_ip, rule->dst_ip, rule->src_port, rule->dst_port, rule->message);

            if (rule->content[0]) {
                printf("    Content: %s\n", rule->content);
            }

            if (rule->regex[0]) {
                printf("    Regex: %s\n", rule->regex);
            }

        }
    }
}

char * trim_left_space(char *str)
{
    char *begin = str;
    while (*begin != '\0') {
        if (isspace(*begin)) {
            begin++;
        } else {
            str = begin;
            break;
        }
    }
    return str;
}

char * remove_quotes(char *str)
{
    str[strlen(str)-1] = '\0'; // remove " at the end
    return str + 1; // remove " at the front
}

int load_rules(struct context_t *ctx)
{
    int cnt = 1;
    char buf[MAX_STRING] = {0};

    FILE *fp = fopen(RULE_FILE, "r");
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // comment
        if (buf[0] == '#')
            continue;

        // empty line
        if (strlen(buf) < 5)
            continue;

        // allocate a space
        struct rule_t *rule = (struct rule_t *)malloc(sizeof(struct rule_t));
        if (rule == NULL) {
            printf("[ERROR] Failed to allocate memory\n");
            continue;
        }

        // initialize the space
        memset(rule, 0, sizeof(struct rule_t));
        
        char base[MAX_STRING] = {0};
        char options[MAX_STRING] = {0};

        char *ptr = strtok(buf, "(");
        if (ptr == NULL) {
            printf("[ERROR] Failed to tokenize buffer (base / %s)\n", buf);
            free(rule);
            continue;
        }

        // copy the base part
        strcpy(base, ptr);

        ptr = strtok(NULL, "\n");
        if (ptr == NULL) {
            printf("[ERROR] Failed to tokenize buffer (options / %s)\n", buf);
            free(rule);
            continue;
        }

        // copy the option part
        strcpy(options, ptr);

        int idx = 0;
        for (ptr = strtok(base, " "), idx = 0; ptr != NULL; ptr = strtok(NULL, " "), idx = idx + 1) {
            switch (idx) {
            case 1: // protocol
                if (strcmp(ptr, "ip") == 0) {
                    rule->proto = PROTO_IPV4;
                } else if (strcmp(ptr, "tcp") == 0) {
                    rule->proto = PROTO_IPV4 | PROTO_TCP;
                } else if (strcmp(ptr, "udp") == 0) {
                    rule->proto = PROTO_IPV4 | PROTO_UDP;
                } else if (strcmp(ptr, "icmp") == 0) {
                    rule->proto = PROTO_IPV4 | PROTO_ICMP;
                } else if (strcmp(ptr, "http") == 0) {
                    rule->proto = PROTO_IPV4 | PROTO_TCP | PROTO_HTTP;
                }
                break;
            case 2: // src ip
                if (strcmp(ptr, "any") != 0) {
                    struct in_addr ip_addr;
                    if (inet_aton(ptr, &ip_addr)) {
                        rule->src_ip = ip_addr.s_addr;
                    }
                }
                break;
            case 3: // src port
                if (strcmp(ptr, "any") != 0) {
                    rule->src_port = atoi(ptr);
                }
                break;
            case 5: // dst ip
                if (strcmp(ptr, "any") != 0) {
                    struct in_addr ip_addr;
                    if (inet_aton(ptr, &ip_addr)) {
                        rule->dst_ip = ip_addr.s_addr;
                    }
                }
                break;
            case 6: // dst port
                if (strcmp(ptr, "any") != 0) {
                    rule->dst_port = atoi(ptr);
                }
                break;
            }
        }

        char option[OPTION_LIMIT][MAX_STRING] = {{0}};

        for (ptr = strtok(options, ";"), idx = 0; ptr != NULL; ptr = strtok(NULL, ";"), idx = idx + 1) {
            if (ptr[0] == ')')
                continue;
            strcpy(option[idx], trim_left_space(ptr));
            printf("%s\n", option[idx]);
        }

        for (idx = 0; idx < OPTION_LIMIT; idx++) {
            if (option[idx][0] == 0)
                break;

            ptr = strtok(option[idx], ":");

            if (strcmp(ptr, "msg") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->message, remove_quotes(ptr));
            } else if (strcmp(ptr, "content") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->content, remove_quotes(ptr));
            } else if (strcmp(ptr, "regex") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->regex, remove_quotes(ptr));
            } else if ((rule->proto & PROTO_HTTP) && (strcmp(ptr, "method") == 0)) {
                ptr = strtok(NULL, ":");
                strcpy(rule->method, remove_quotes(ptr));
            }
        }

        if (rule->proto & PROTO_HTTP) {
            rule->next = ctx->rule_table[HTTP_RULES];
            ctx->rule_table[HTTP_RULES] = rule;
        } else if (rule->proto & PROTO_ICMP) {
            rule->next = ctx->rule_table[ICMP_RULES];
            ctx->rule_table[ICMP_RULES] = rule;
        } else if (rule->proto & PROTO_UDP) {
            rule->next = ctx->rule_table[UDP_RULES];
            ctx->rule_table[UDP_RULES] = rule;
        } else if (rule->proto & PROTO_TCP) {
            rule->next = ctx->rule_table[TCP_RULES];
            ctx->rule_table[TCP_RULES] = rule;
        } else { // PROTO_IPV4
            rule->next = ctx->rule_table[IP_RULES];
            ctx->rule_table[IP_RULES] = rule;
        }

        cnt++;
    }

    fclose(fp);

    int i;
    for (i=0; i<NUM_OF_PROTO; i++) {
        printf("Proto ID: %d\n", i);

        struct rule_t *rule = ctx->rule_table[i];
        while (rule != NULL) {
            print_rule(rule);
            rule = rule->next;
        }
    }

    printf("[INFO] %d rules are loaded\n", cnt);

    return 0;
}

int initialize_rule_table(struct context_t *ctx)
{
    ctx->rule_table = (struct rule_t **)malloc(sizeof(struct rule *) * NUM_OF_PROTO);
    memset(ctx->rule_table, 0, sizeof(struct rule_t *) * NUM_OF_PROTO);

    printf("[INFO] Initialized rule tables\n");

    return 0;
}

int destroy_rule_table(struct context_t *ctx)
{
    int i;
    for (i=0; i<NUM_OF_PROTO; i++) {
        struct rule_t *rule = ctx->rule_table[i];

        while (rule != NULL) {
            struct rule_t *temp = rule;
            rule = rule->next;
            free(temp);
        }
    }

    free(ctx->rule_table);

    printf("[INFO] Destroyed the rule tables\n");

    return 0;
}
