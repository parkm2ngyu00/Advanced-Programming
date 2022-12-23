#include <stdio.h>
#include <string.h>

int main(void)
{
    char *string1 = "Advanced Programming Practice";
    char *string2 = "ming";

    char *result = strstr(string1, string2);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("Not found\n");
    }

    char *string3 = "DKU";

    result = strstr(string1, string3);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("Not found\n");
    }

    char *string4 = "Dankook\0University";
    char *string5 = "Univ";

    result = strstr(string4, string5);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("Not found\n");
    }

    return 0;
}
