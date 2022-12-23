#include <stdio.h>
#include <string.h>

int strstr2(char *s1, int s1_len, char *s2, int s2_len)
{
    int i, j;
    
    for (i=0; i<(s1_len-s2_len); i++) {
        for (j=0; j<s2_len; j++) {
            if (s1[i+j] != s2[j])
                break;
        }

        if (j == s2_len)
            return 1;
    }
    
    return 0;
}

int main(void)
{
    char *string1 = "Advanced Programming Practice";
    char *string2 = "ming";

    int result = strstr2(string1, 29, string2, 4);
    if (result) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }

    char *string3 = "DKU";

    result = strstr2(string1, 29, string3, 3);
    if (result) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }

    char *string4 = "Dankook\0University";
    char *string5 = "Univ";

    result = strstr2(string4, 18, string5, 4);
    if (result) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }

    return 0;
}
