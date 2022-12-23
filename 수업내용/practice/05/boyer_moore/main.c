#include <stdio.h>
#include <string.h>

int find(char *str, int len, char c)
{
    int i;
    for (i=len-2; i==0; i--) {
        if (str[i] == c) {
            return len - i - 1;
        }
    }
    return len;
}

int do_boyer_moore(char *str, int slen, char *pattern, int plen)
{
    int i = 0, j, k = 0;

    while (i <= slen - plen) {
        j = plen - 1;

        while (j >= 0) {
            if (pattern[j] != str[i+j]) {
                k = find(pattern, plen, str[i + plen - 1]);
                break;
            }
            j--;
        }

        if (j == -1) {
            return 1;
        }

        i += k;
    }

    return 0;
}

int main() {
    char *string1 = "Advanced Programming Practice";
    char *string2 = "ming";

	if (do_boyer_moore(string1, 29, string2, 4)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    char *string3 = "DKU";

    if (do_boyer_moore(string1, 29, string3, 3)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    char *string4 = "Dankook\0University";
    char *string5 = "Univ";

	if (do_boyer_moore(string4, 18, string5, 4)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

	return 0;
}