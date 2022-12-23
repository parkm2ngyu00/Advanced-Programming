#include <stdio.h>
#include <string.h>

int main()
{
    char s1[30] = "dankook university";

    char *ptr = strstr(s1, "kook");

    printf("%s\n", ptr);

    return 0;
}
