#include "capture.h"
#include <pcap.h>

struct context_t *local_ctx;
pcap_t *handler;

int stop_capturing()
{
    // 구현
    // break the pcap loop
    // pcap_breakloop(handler);

    // // release the handler
    // pcap_close(handler);
    return 0;
}

void per_packet_callback(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
{
    decode_packet(local_ctx, pkt, header->len);
}

int start_to_capture(struct context_t *ctx)
{
    local_ctx = ctx;

    // 구현
    // error message
    // char ebuf[PCAP_ERRBUF_SIZE] = {0};
    // // device list
    // pcap_if_t *devices;

    // // find all network interfaces
    // if (pcap_findalldevs(&devices, ebuf) == -1) {
    //     printf("[ERROR] %s\n", ebuf);
    //     return -1;
    // }

    // // if no source, set default interface
    // if (ctx->interface[0] == 0) {
    //     strcpy(ctx->interface, devices->name);
    //     printf("[INFO] Use Default Interface (%s)\n", ctx->interface);
    // }

    // int found = 0;
    // pcap_if_t *temp;

    // // check the existence of the given interface
    // for (temp=devices; temp; temp=temp->next) {
    //     if (strcmp(ctx->interface, temp->name) == 0) {
    //         found = 1;
    //         break;
    //     }
    // }

    // if (!found) {
    //     printf("[ERROR] Failed to find %s\n", ctx->interface);
    //     return -1;
    // }

    // // get the pcap handler
    // handler = pcap_open_live(ctx->interface, PCAP_SNAPSHOT, 1, PCAP_TIMEOUT, ebuf);
    // if (handler == NULL) {
    //     printf("[ERROR] %s\n", ebuf);
    //     return -1;
    // }

    // char filter[PCAP_FILTER_SIZE] = "! tcp port 22";
    // struct bpf_program filter_code;

    // // make a filter to ignore ssh traffic
    // if (pcap_compile(handler, &filter_code, filter, 0, 0) < 0) {
    //     printf("[ERROR] Failed to compile filter\n");
    //     return -1;
    // }

    // // set the filter
    // if (pcap_setfilter(handler, &filter_code) < 0) {
    //     printf("[ERROR] Failed to set filter\n");
    //     return -1;
    // }

    // printf("[INFO] Started to capture packets from %s\n", ctx->interface);

    // // capture live packets
    // pcap_loop(handler, 0, per_packet_callback, 0);
    return 0;
}
