#include <stdio.h>
#include <pcap.h>

int main()
{
    char ebuf[PCAP_ERRBUF_SIZE] = {0};

    // == START == //

    pcap_if_t *devices, *temp;

    if (pcap_findalldevs(&devices, ebuf) == -1) {
        printf("[ERROR] failed to find devices: %s\n", ebuf);
        return -1;
    }

    int num = 0;

    for (temp=devices; temp; temp=temp->next) {
        printf("%d: %s\n", num++, temp->name);
    }

    // == END == //

    return 0;
}
