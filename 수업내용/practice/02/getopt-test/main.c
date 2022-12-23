#include <stdio.h>
#include <string.h> // used by strcpy()
#include <unistd.h> // used by getopt()

#define MAX_STRING 1024

int main(int argc, char **argv)
{
    char interface[MAX_STRING] = {0};
    char match[MAX_STRING] = {0};
    int verbose = 0;

    // == //

    int opt;
    while ( (opt = getopt(argc, argv, "i:m:v")) != -1) {
        switch (opt) {
        case 'i':
            strcpy(interface, optarg);
            break;
        case 'm':
            strcpy(match, optarg);
            break;
        case 'v':
            verbose = 1;
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        }
    }

    // == //

    printf("Interface: %s\n", interface);
    printf("Match: %s\n", match);
    printf("Verbose: %s\n", (verbose == 0) ? "False" : "True");

    return 0;
}
