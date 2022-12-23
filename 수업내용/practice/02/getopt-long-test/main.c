#include <stdio.h>
#include <string.h> // used by strcmp(), strcpy()
#include <getopt.h> // used by getopt_long()

#define MAX_STRING 1024

static int brief_flag;

int main(int argc, char **argv)
{
    char interface[MAX_STRING] = {0};
    char match[MAX_STRING] = {0};
    int verbose = 0;

    // == //

    static struct option long_options[] = {
        {"interface", required_argument, 0, 'i'}, // --interface를 만나면 -i로 변환
        {"match", required_argument, 0, 'm'},
        {"verbose", no_argument, 0, 'v'},
        {"brief", no_argument, &brief_flag, 1}, // --brief를 만나면 brief_flag에 1을 세팅, brief_flag는 전역변수
        {"level", required_argument, 0, 0}, // 짧은 옵션 없이 긴 옵션 (--level)만 존재
        {0, 0, 0, 0}
    };
    int option_index = 0;

    int opt;
    while ( (opt = getopt_long(argc, argv, "i:m:v", long_options, &option_index)) != -1) {
        switch (opt) {
        // 긴 옵션만 존재하는 경우
        case 0:
            if (strcmp(long_options[option_index].name, "level") == 0) {
                printf("Level: %s\n", optarg);
            }
            break;
        // 짧은 옵션만 또는 둘 다 존재하는 경우
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
    printf("Brief: %s\n", (brief_flag == 0) ? "False" : "True");

    return 0;
}
