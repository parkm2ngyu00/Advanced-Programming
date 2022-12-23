#include <stdio.h>
#include <string.h>

int main()
{
    char s1[30] = "dankook university";

    char *ptr = strrchr(s1, 'n');

    printf("%s\n", ptr);

    return 0;
}
