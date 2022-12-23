#include "rule.h"

static char *trim_left_space(char *str)
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

static char *remove_quotes(char *str)
{
    str[strlen(str)-1] = '\0';
    return str + 1;
}

int load_rules(struct context_t *ctx)
{
    char buf[MAX_STRING] = {0};

    FILE *fp = fopen(ctx->rule_file, "r");
    if (fp == NULL) {
        printf("Failed to open '%s'\n", ctx->rule_file);
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (buf[0] == '#')
            continue;
        
        if (strlen(buf) < 15)
            continue;
        
        struct rule_t *rule = (struct rule_t *)malloc(sizeof(struct rule_t));
        if (rule == NULL) {
            printf("Failed to allocate memory\n");
            return -1;
        }
        memset(rule, 0, sizeof(struct rule_t));

        char kv[NUM_OF_RULE_OPTIONS][MAX_STRING] = {{0}};

        int idx;
        char *ptr;

        for (ptr = strtok(buf, ";"), idx = 0; ptr != NULL; ptr = strtok(NULL, ";"), idx = idx + 1) {
            strcpy(kv[idx], ptr);
        }

        for (idx=0; idx<NUM_OF_RULE_OPTIONS; idx++) {
            if (kv[idx][0] == 0)
                break;

            ptr = strtok(kv[idx], ":");

            if (strcmp(trim_left_space(ptr), "service") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->service, remove_quotes(ptr));

                if (strcmp(rule->service, "md5") != 0 && 
                    strcmp(rule->service, "sha1") != 0 && 
                    strcmp(rule->service, "sha256") != 0 && 
                    strcmp(rule->service, "sha512") != 0) {
                    printf("Failed to parse a value (%s)\n", rule->service);
                    return -1;
                }
            } else if (strcmp(trim_left_space(ptr), "resource") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->resource, remove_quotes(ptr));
            } else if (strcmp(trim_left_space(ptr), "message") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->message, remove_quotes(ptr));
            } else {
                printf("Failed to load a rule (%s)\n", buf);
                return -1;
            }
        }

        rule->next = ctx->rules;
        ctx->rules = rule;
    }

    fclose(fp);

    int cnt;
    struct rule_t *rule;

    for (rule = ctx->rules, cnt = 0; rule != NULL; rule = rule->next, cnt = cnt + 1) {
        printf("Rule #%02d\n", cnt + 1);
        printf("  service: %s\n", rule->service);
        printf("  resource: %s\n", rule->resource);
        printf("  message: %s\n", rule->message);
    }

    printf("%d rules are loaded\n", cnt-1);

    return 0;
}

int init_rules(struct context_t *ctx)
{
    ctx->rules = NULL;

    printf("Initialized rules\n");

    return 0;
}

int destroy_rules(struct context_t *ctx)
{
    struct rule_t *rule = ctx->rules;
    while (rule != NULL) {
        struct rule_t *temp = rule;
        rule = rule->next;
        free(temp);
    }

    printf("Destroyed the rules\n");

    return 0;
}
