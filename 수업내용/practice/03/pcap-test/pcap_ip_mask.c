#include <stdio.h>
#include <pcap.h>

int main(int argc, char *argv[])
{
    char ebuf[PCAP_ERRBUF_SIZE] = {0};

    // == START == //

    bpf_u_int32 ip, mask;
    struct in_addr net_addr, mask_addr;

    if (pcap_lookupnet(argv[1], &ip, &mask, ebuf) < 0)
    {
        printf("[ERROR] %s\n", ebuf);
    }

    net_addr.s_addr = ip;
    mask_addr.s_addr = mask;

    printf("IP: %s\n", inet_ntoa(net_addr));
    printf("Mask: %s\n", inet_ntoa(mask_addr));

    // == END == //

    return 0;
}
