#include "decode.h"
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

static char *remove_quotes(char *str)
{
    str[strlen(str)-1] = '\0';
    return str + 1;
}

int decode_packet(struct context_t *ctx, const u_char *pkt, int len)
{
    struct ethhdr *eth = (struct ethhdr *)pkt;

    if (eth->h_proto == ntohs(ETH_P_IP)) {
        struct iphdr *iph = (struct iphdr *)(pkt + sizeof(struct ethhdr));

        char src_ip_addr[16] = {0}, dst_ip_addr[16] = {0};
        struct in_addr ip_addr;

        ip_addr.s_addr = iph->saddr;
        strcpy(src_ip_addr, inet_ntoa(ip_addr));

        ip_addr.s_addr = iph->daddr;
        strcpy(dst_ip_addr, inet_ntoa(ip_addr));

        if (iph->protocol == IPPROTO_TCP) {
            struct tcphdr *tcph = (struct tcphdr *)(pkt + sizeof(struct ethhdr) + (iph->ihl*4));

            int src_port = ntohs(tcph->source);
            int dst_port = ntohs(tcph->dest);

            if (!(src_port == 8001 || src_port == 8002 || src_port == 8003 || src_port == 8004) &&
                !(dst_port == 8001 || dst_port == 8002 || dst_port == 8003 || dst_port == 8004))
                return 0;

            char *payload = (char *)(pkt + sizeof(struct ethhdr) + (iph->ihl*4) + (tcph->doff*4));
            int payload_len = len - sizeof(struct ethhdr) - (iph->ihl*4) - (tcph->doff*4);

            if (ctx->debug) {
                printf("%s:%d -> %s:%d\n", src_ip_addr, src_port, dst_ip_addr, dst_port);
                if (payload_len > 0) {
                    int pi;
                    for (pi=0; pi<payload_len; pi++) {
                        if (payload[pi] >= 32 && payload[pi] < 127) {
                            printf("%c", payload[pi]);
                        } else {
                            printf(".");
                        }
                    }
                    printf("\n");
                }
            }

            if (dst_port == 8001 || dst_port == 8002 || dst_port == 8003 || dst_port == 8004)
                return 0;

            struct stats_t *stats = (struct stats_t *)malloc(sizeof(struct stats_t));
            if (stats == NULL) {
                printf("Failed to allocate memory\n");
                return -1;
            }
            memset(stats, 0, sizeof(struct stats_t));

            int service_index = 0;

            switch(src_port) {
            case 8001:
                sprintf(stats->service, "md5");
                service_index = 0;
                break;
            case 8002:
                sprintf(stats->service, "sha1");
                service_index = 1;
                break;
            case 8003:
                sprintf(stats->service, "sha256");
                service_index = 2;
                break;
            case 8004:
                sprintf(stats->service, "sha512");
                service_index = 3;
                break;
            }

            char buf[2][MAX_STRING] = {{0}};

            char *ptr = strtok(payload, ";");
            if (ptr == NULL) {
                free(stats);
                return 0;
            }
            strcpy(buf[0], ptr);

            ptr = strtok(NULL, ";");
            if (ptr == NULL) {
                free(stats);
                return 0;
            }
            strcpy(buf[1], ptr);

            ptr = strtok(buf[0], ":");
            if (ptr == NULL) {
                free(stats);
                return 0;
            }
            if (strcmp(remove_quotes(ptr), "resource") == 0) {
                ptr = strtok(NULL, ":");
                if (ptr == NULL) {
                    free(stats);
                    return 0;
                }
                strcpy(stats->resource, remove_quotes(ptr));
            } else {
                free(stats);
                return 0;
            }

            ptr = strtok(buf[1], ":");
            if (ptr == NULL) {
                free(stats);
                return 0;
            }
            if (strcmp(remove_quotes(ptr), "content") == 0) {
                ptr = strtok(NULL, ":");
                if (ptr == NULL) {
                    free(stats);
                    return 0;
                }
                strcpy(stats->content, remove_quotes(ptr));
            } else {
                free(stats);
                return 0;
            }

            stats->count = 1;

            struct rule_t *rule = match_rules(ctx, stats, payload, payload_len);
            if (rule != NULL) {
                printf("%s:%d -> %s:%d (message: %s, service: %s, resource: %s, content: %s)\n", 
                        dst_ip_addr, dst_port, src_ip_addr, src_port, rule->message, stats->service, stats->resource, stats->content);
            }

            struct stats_t *temp = ctx->stats[service_index];
            while (temp != NULL) {
                if (strcmp(stats->resource, temp->resource) == 0) {
                    temp->count++;
                    return 0;
                }
                temp = temp->next;
            }

            stats->next = ctx->stats[service_index];
            ctx->stats[service_index] = stats;
        }
    }

    return 0;
}
