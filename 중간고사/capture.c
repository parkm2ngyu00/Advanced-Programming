#include "capture.h"
#include <pcap.h>

struct context_t *local_ctx;
pcap_t *handler;

int stop_capturing()
{
    pcap_breakloop(handler);

    pcap_close(handler);

    return 0;
}

void per_packet_callback(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
{
    decode_packet(local_ctx, pkt, header->len);
}

int start_to_capture(struct context_t *ctx)
{
    char ebuf[PCAP_ERRBUF_SIZE] = {0};
    pcap_if_t *devices, *temp;
    int found = 0;

    local_ctx = ctx;

    if (pcap_findalldevs(&devices, ebuf) == -1) {
        printf("Failed to find devices (%s)\n", ebuf);
        return -1;
    }

    for (temp=devices; temp; temp=temp->next) {
        if (strcmp(ctx->interface, temp->name) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Failed to find '%s'\n", ctx->interface);
        return -1;
    }

    handler = pcap_open_live(ctx->interface, PCAP_SNAPSHOT, 1, PCAP_TIMEOUT, ebuf);
    if (handler == NULL) {
        printf("Failed to open pcap handler (%s)\n", ebuf);
        return -1;
    }

    printf("Start to capture packets\n");

    pcap_loop(handler, 0, per_packet_callback, 0);

    return 0;
}
