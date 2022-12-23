#include <stdio.h>
#include <string.h>

int main()
{
    char s1[10] = "world";
    char s2[20] = "Hello";

    strcat(s2, s1);

    printf("%s\n", s2);

    return 0;
}
