#include <stdio.h>
#include <string.h>

#define MAX_STRING 1024

int main(int argc, char **argv)
{
    int i;

    char interface[MAX_STRING] = {0};
    char match[MAX_STRING] = {0};
    int verbose = 0;

    // == //

    for (i=0; i<argc; i++) {
        printf("[%d]: %s\n", i, argv[i]);

        if (strcmp(argv[i], "-i") == 0) {
            if (i+1 < argc) {
                strcpy(interface, argv[i+1]);
                i++;
            } else {
                printf("out-of-boundary\n");
            }
        } else if (strcmp(argv[i], "--interface") == 0) {
            if (i+1 < argc) {
                strcpy(interface, argv[i+1]);
                i++;
            } else {
                printf("out-of-boundary\n");
            }
        } else if (strcmp(argv[i], "-m") == 0) {
            if (i+1 < argc) {
                strcpy(match, argv[i+1]);
                i++;
            } else {
                printf("out-of-boundary\n");
            }
        } else if (strcmp(argv[i], "--match") == 0) {
            if (i+1 < argc) {
                strcpy(match, argv[i+1]);
                i++;
            } else {
                printf("out-of-boundary\n");
            }
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        }
    }

    // == //

    printf("Interface: %s\n", interface);
    printf("Match: %s\n", match);
    printf("Verbose: %s\n", (verbose == 0) ? "False" : "True");

    return 0;
}
