#include "log_file.h"

int log_file(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet)
{
    char src_ip_addr[16] = {0}, dst_ip_addr[16] = {0};
    struct in_addr ip_addr;

    ip_addr.s_addr = rule->src_ip;
    strcpy(src_ip_addr, inet_ntoa(ip_addr));

    ip_addr.s_addr = rule->dst_ip;
    strcpy(dst_ip_addr, inet_ntoa(ip_addr));

    char msg[4096] = {0};

    char proto[SHORT_STRING];

    if (rule->proto & PROTO_HTTP) {
        strcpy(proto, "HTTP");
    } else if (rule->proto & PROTO_TCP) {
        strcpy(proto, "TCP");
    } else if (rule->proto & PROTO_UDP) {
        strcpy(proto, "UDP");
    } else if (rule->proto & PROTO_ICMP) {
        strcpy(proto, "ICMP");
    } else {
        strcpy(proto, "IP");
    }

    if (rule->content[0] && rule->regex[0]) {
        sprintf(msg, "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; content:\"%s\"; regex:\"%s\";)\n",
                proto, src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, 
                rule->message, rule->content, rule->regex);
    } else if (rule->content[0] && !rule->regex[0]) {
        sprintf(msg, "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; content:\"%s\";)\n", 
                proto, src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port,
                rule->message, rule->content);
    } else if (!rule->content[0] && rule->regex[0]) {
        sprintf(msg, "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; regex:\"%s\";)\n", 
                proto, src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port,
                rule->message, rule->regex);
    } else {
        sprintf(msg, "[ALERT] %s %s %d -> %s %d (msg:\"%s\";)\n", 
                proto, src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, 
                rule->message);
    }

    FILE *fp = fopen(ctx->log, "a");
    if (fp == NULL) {
        printf("%s", msg);
        return -1;
    }

    fputs(msg, fp);

    fclose(fp);

    return 0;
}
