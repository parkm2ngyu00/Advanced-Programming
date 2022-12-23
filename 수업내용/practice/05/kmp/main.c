#include <stdio.h>
#include <string.h>

#define MAX_STRING 1024

int skip[MAX_STRING];

void make_skip_table(char *str, int len)
{
    memset(skip, 0, sizeof(int) * MAX_STRING);

    int i, j = 0;
    for (i=1; i<len; i++) {
        while (j>0 && str[i] != str[j]) {
            j = skip[j - 1];
        }
        if (str[i] == str[j])
            skip[i] = j++;
    }
}

int do_kmp(char *str, int slen, char *pattern, int plen)
{
    int i, j = 0, cnt = 0;

    make_skip_table(pattern, plen);

    for (i=0; i<slen; i++) {
        while (j>0 && str[i] != pattern[j]) {
            j = skip[j - 1];
        }

        if (str[i] == pattern[j]) {
            if (j == plen - 1) {
                return 1;
            } else {
                j++;
            }
        }
    }

    return 0;
}

int main() {
    char *string1 = "Advanced Programming Practice";
    char *string2 = "ming";

	if (do_kmp(string1, 29, string2, 4)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    char *string3 = "DKU";

    if (do_kmp(string1, 29, string3, 3)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    char *string4 = "Dankook\0University";
    char *string5 = "Univ";

	if (do_kmp(string4, 18, string5, 4)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

	return 0;
}