#include "decoder.h"

void mask_payload_printable(struct packet_t *packet)
{
    int pi;
    for (pi=0; pi<packet->payload_len; pi++) {
        if (packet->payload[pi] < 32 || packet->payload[pi] > 127) {
            packet->payload[pi] = '.';
        }
    }
}

int decoder(struct context_t *ctx, struct packet_t *packet) {
    // ethernet header
    struct ethhdr *eth = (struct ethhdr *)packet->pkt;

    if (eth->h_proto == ntohs(ETH_P_IP)) {
        // IP
        struct iphdr *iph = (struct iphdr *)(packet->pkt + sizeof(struct ethhdr));

        packet->proto = PROTO_IPV4;
        packet->src_ip = iph->saddr;
        packet->dst_ip = iph->daddr;

#ifdef DEBUG
    u_int8_t *src_mac = eth->h_source;
    u_int8_t *dst_mac = eth->h_dest;

    printf("[DEBUG] src MAC: %02x:%02x:%02x:%02x:%02x:%02x / dst MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        src_mac[0],src_mac[1], src_mac[2], src_mac[3], src_mac[4], src_mac[5],
        dst_mac[0],dst_mac[1], dst_mac[2], dst_mac[3], dst_mac[4], dst_mac[5]);
#endif /* DEBUG */

#ifdef DEBUG
        char src_ip_addr[16] = {0}, dst_ip_addr[16] = {0};
        struct in_addr ip_addr;

        ip_addr.s_addr = iph->saddr;
        strcpy(src_ip_addr, inet_ntoa(ip_addr));

        ip_addr.s_addr = iph->daddr;
        strcpy(dst_ip_addr, inet_ntoa(ip_addr));

        printf("[DEBUG] src IP : %s (%d) / dst IP : %s (%d)\n", src_ip_addr, packet->src_ip, dst_ip_addr, packet->dst_ip);
#endif /* DEBUG */

        if (iph->protocol == IPPROTO_TCP) {
            // TCP
            struct tcphdr *tcph = (struct tcphdr *)(packet->pkt + sizeof(struct ethhdr) + (iph->ihl*4));

            packet->proto |= PROTO_TCP;
            packet->src_port = ntohs(tcph->source);
            packet->dst_port = ntohs(tcph->dest);

#ifdef DEBUG
            printf("[DEBUG] protocol: TCP / source Port: %d / destination Port: %d\n", packet->src_port, packet->dst_port);
#endif /* DEBUG */

			packet->payload = (char *)(packet->pkt + sizeof(struct ethhdr) + (iph->ihl*4) + (tcph->doff*4));
			packet->payload_len = packet->pkt_len - sizeof(struct ethhdr) - (iph->ihl*4) - (tcph->doff*4);

            if (packet->payload_len > 4) {
                if (packet->payload[0] == 'H' && packet->payload[1] == 'T' && packet->payload[2] == 'T' && packet->payload[3] == 'P') {
                    packet->proto |= PROTO_HTTP;
                }
            }

        } else if (iph->protocol == IPPROTO_UDP) {
            // UDP
            struct udphdr *udph = (struct udphdr *)(packet->pkt + sizeof(struct ethhdr) + iph->ihl*4);

            packet->proto |= PROTO_UDP;
            packet->src_port = ntohs(udph->source);
            packet->dst_port = ntohs(udph->dest);

#ifdef DEBUG
            printf("[DEBUG] protocol: UDP / source port: %d / destination port: %d\n", packet->src_port, packet->dst_port);
#endif /* DEBUG */

            packet->payload = (char *)(packet->pkt + sizeof(struct ethhdr) + (iph->ihl*4) + sizeof(struct udphdr));
			packet->payload_len = packet->pkt_len - sizeof(struct ethhdr) - (iph->ihl*4) - sizeof(struct udphdr);

        } else if (iph->protocol == IPPROTO_ICMP) {
            // ICMP
            struct icmphdr *icmph = (struct icmphdr *)(packet->pkt + sizeof(struct ethhdr) + iph->ihl*4);

            packet->proto |= PROTO_ICMP;
            packet->icmp_type = icmph->type;
            packet->icmp_code = icmph->code;

#ifdef DEBUG
            printf("[DEBUG] protocol: ICMP / type: %d / code: %d\n", packet->icmp_type, packet->icmp_code);
#endif /* DEBUG */

            packet->payload = (char *)(packet->pkt + sizeof(struct ethhdr) + (iph->ihl*4) + sizeof(struct icmphdr));
			packet->payload_len = packet->pkt_len - sizeof(struct ethhdr) - (iph->ihl*4) - sizeof(struct icmphdr);

        } else {
            // IPv4

#ifdef DEBUG
            printf("[DEBUG] protocol: IPv4\n");
#endif /* DEBUG */

            packet->payload = (char *)(packet->pkt + sizeof(struct ethhdr) + (iph->ihl*4));
			packet->payload_len = packet->pkt_len - sizeof(struct ethhdr) - (iph->ihl*4);
        }

        mask_payload_printable(packet);

#ifdef DEBUG
        if (packet->payload_len) {
            printf("[DEBUG] payload (%d): %s\n", packet->payload_len, packet->payload);
        } else {
            printf("[DEBUG] no payload\n");
        }
#endif /* DEBUG */

        return 0;
    }

    return -1;
}
