#include "rule.h"

int load_rules(struct context_t *ctx)
{
    // 구현
    int cnt = 1;
    char buf[MAX_STRING] = {0};

    FILE *fp = fopen(ctx->rule_file, "r");

    printf("Initialized rules\n");

    if (fp == NULL) {
        printf("Failed to open %s\n", ctx->rule_file);
        printf("Failed to load rules\n");
        return 0;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (buf[0] == '#')
            continue;
        
        if(strlen(buf) < 5)
            continue;
        
        struct rule_t *rule = (struct rule_t *)malloc(sizeof(struct rule_t));
        if (rule == NULL) {
            printf("[ERROR] Failed to allocate memory\n");
            continue;
        }
        memset(rule, 0, sizeof(struct rule_t));

        char option[NUM_OF_RULE_OPTIONS][MAX_STRING] = {{0}};
        char *ptr;
        int idx;
        for (ptr = strtok(buf, ";"), idx = 0; ptr != NULL; ptr = strtok(NULL, ";"), idx = idx + 1) {
            strcpy(option[idx], ptr);
        }
        for (idx = 0; idx < NUM_OF_RULE_OPTIONS; idx++) {
            if (option[idx][0] == 0)
                break;
            ptr = strtok(option[idx], ":");
            if (strcmp(ptr, "sevice") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->service, ptr);
            } else if (strcmp(ptr, "resource") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->resource, ptr);
            } else if (strcmp(ptr, "message") == 0) {
                ptr = strtok(NULL, ":");
                strcpy(rule->message, ptr);
            }
        }
        
    }

    fclose(fp);

    struct rule_t *rule = ctx->rules;
    while (rule != NULL) {
        printf("service : %s, resource : %s, message : %s", rule->service, rule->resource, rule->message);
        rule = rule->next;
    }

    return 0;
}

int init_rules(struct context_t *ctx)
{
    // 구현
    ctx->rules = (struct rule_t *)malloc(sizeof(struct rule_t));
    memset(ctx->rules, 0, sizeof(struct rule_t));

    printf("[INFO] Initialized rule tables\n");
    return 0;
}

int destroy_rules(struct context_t *ctx)
{
    // 구현
    int i;
    struct rule_t *rule = ctx->rules;

    while (rule != NULL) {
        struct rule_t *temp = rule;
        rule = rule -> next;
        free(temp);
    }
    return 0;
}
