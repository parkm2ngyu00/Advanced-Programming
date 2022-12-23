#include <stdio.h>
#include <pcap.h>

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

    // == START == //

    pcap_t *handle;

    // handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
    // if (handle == NULL) {
    //    ...
    // }

    handle = pcap_open_offline(argv[1], ebuf);
    if (handle == NULL) {
        printf("[ERROR] %s\n", ebuf);
        return -1;
    }

    // == END == //

    pcap_loop(handle, 10, callback_func, 0);

    pcap_close(handle);

    return 0;
}
