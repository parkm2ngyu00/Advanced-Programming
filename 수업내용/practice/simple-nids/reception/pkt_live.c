#include "pkt_live.h"

// context
struct context_t *local_ctx;

// pcap handler
pcap_t *handler;

// function to destroy pcap handler
int destroy_pkt_live()
{
    // break the pcap loop
    pcap_breakloop(handler);

    // release the handler
    pcap_close(handler);

    return 0;
}

// function to process each packet
void packet_live_callback(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
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

// function to capture live-stream packets
int pkt_live(struct context_t *ctx)
{
    // copy the pointer of ctx to use in the callback
    local_ctx = ctx;

    // error message
    char ebuf[PCAP_ERRBUF_SIZE] = {0};

    // device list
    pcap_if_t *devices;

    // find all network interfaces
    if (pcap_findalldevs(&devices, ebuf) == -1) {
        printf("[ERROR] %s\n", ebuf);
        return -1;
    }

    // if no source, set default interface
    if (ctx->source[0] == 0) {
        strcpy(ctx->source, devices->name);
        printf("[INFO] Use Default Interface (%s)\n", ctx->source);
    }

    int found = 0;
    pcap_if_t *temp;

    // check the existence of the given interface
    for (temp=devices; temp; temp=temp->next) {
        if (strcmp(ctx->source, temp->name) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[ERROR] Failed to find %s\n", ctx->source);
        return -1;
    }

    // get the pcap handler
    handler = pcap_open_live(ctx->source, PCAP_SNAPSHOT, 1, PCAP_TIMEOUT, ebuf);
    if (handler == NULL) {
        printf("[ERROR] %s\n", ebuf);
        return -1;
    }

    char filter[PCAP_FILTER_SIZE] = "! tcp port 22";
    struct bpf_program filter_code;

    // make a filter to ignore ssh traffic
    if (pcap_compile(handler, &filter_code, filter, 0, 0) < 0) {
        printf("[ERROR] Failed to compile filter\n");
        return -1;
    }

    // set the filter
    if (pcap_setfilter(handler, &filter_code) < 0) {
        printf("[ERROR] Failed to set filter\n");
        return -1;
    }

    printf("[INFO] Started to capture packets from %s\n", ctx->source);

    // capture live packets
    pcap_loop(handler, 0, packet_live_callback, 0);

    return 0;
}
