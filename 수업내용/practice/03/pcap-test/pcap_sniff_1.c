#include <stdio.h>
#include <pcap.h>

#define DATA_SIZE 4096

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

int main(int argc, char *argv[])
{
    char ebuf[PCAP_ERRBUF_SIZE] = {0};

    // == START == //

    pcap_t *handle;

    handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
    if (handle == NULL) {
        printf("[ERROR] %s\n", ebuf);
        return -1;
    }

    int i;
    const u_char *pkt;
    struct pcap_pkthdr header;

    for (i=0; i<10; i++) {
        pkt = pcap_next(handle, &header);
        packet_dump(pkt, header.len);
    }

    pcap_close(handle);

    // == END == //

    return 0;
}
