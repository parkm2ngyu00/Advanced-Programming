#include <stdio.h>
#include <string.h>

int main()
{
    char s1[30] = "dankook university";

    char *ptr = strchr(s1, 'n');

    while (ptr != NULL) {
        printf("%s\n", ptr);
        ptr = strchr(ptr + 1, 'n');
    }

    return 0;
}
