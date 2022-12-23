#include <stdio.h>
#include <string.h>
#include <pcap.h>

#define DATA_SIZE 4096
#define FILTER_SIZE 1024

void packet_dump(const u_char *pkt, int len)
{
    int i;

    for (i=0; i<len; i++) {
        printf("%02x ", *pkt);
        pkt++;

        if (i % 16 == 15) {
            printf("\n");
        }
    }

    printf("\n");
}

void callback_func(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
{
    packet_dump(pkt, header->len);
}

int main(int argc, char *argv[])
{
    char ebuf[PCAP_ERRBUF_SIZE] = {0};

    pcap_t *handle;

    handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
    if (handle == NULL) {
        printf("[ERROR] %s\n", ebuf);
        return -1;
    }

    // == START == //

    char filter[FILTER_SIZE] = "";
    struct bpf_program filter_code;

    int i;
    for (i=2; i<argc; i++) {
        sprintf(filter+strlen(filter), " %s", argv[i]);
    }

    if (pcap_compile(handle, &filter_code, filter, 0, 0) < 0) {
        printf("[ERROR] Failed to compile filter\n");
        return -1;
    }

    if (pcap_setfilter(handle, &filter_code) < 0) {
        printf("[ERROR] Failed to set filter\n");
        return -1;
    }

    // == END == //

    pcap_loop(handle, 10, callback_func, 0);

    pcap_close(handle);

    return 0;
}
