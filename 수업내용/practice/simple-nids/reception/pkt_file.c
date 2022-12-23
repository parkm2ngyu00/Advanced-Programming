#include "pkt_file.h"

// context
struct context_t *local_ctx;

// pcap handler
pcap_t *handler;

// function to destroy pcap handler
int destroy_pkt_file()
{
    // break the pcap loop
    pcap_breakloop(handler);

    // release the handler
    pcap_close(handler);

    return 0;
}

// function to process each packet
void packet_file_callback(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
{
    // get a packet structure from a pool
    struct packet_t *packet = pop_packet();

    // copy the length of an incoming packet to packet->len
    packet->pkt_len = header->len;

    // copy the incoming packet to packet->pkt
    memcpy(packet->pkt, pkt, header->len);

    // call a decoder
    if (local_ctx->decoder_func(local_ctx, packet) < 0) {
        // skip if non-ipv4 packet
        push_packet(packet);
        return;
    };

    // call a string matching engine (including a regex engine)
    struct rule_t *rule = local_ctx->string_match_func(local_ctx, packet);

    // call a logging engine
    if (rule != NULL) {
        local_ctx->log_func(local_ctx, rule, packet);
    }

    // release the used packet structure
    push_packet(packet);
}

// function to read pcap file
int pkt_file(struct context_t *ctx)
{
    // copy the pointer of ctx to use in the callback
    local_ctx = ctx;

    // error message
    char ebuf[PCAP_ERRBUF_SIZE] = {0};

    // get the pcap handler
    handler = pcap_open_offline(ctx->source, ebuf);
    if (handler == NULL) {
        printf("[ERROR] %s\n", ebuf);
        return -1;
    }

    printf("[INFO] Started to read packets from %s\n\n", ctx->source);

    // read the given pcap file
    pcap_loop(handler, 0, packet_file_callback, 0);

    return 0;
}
