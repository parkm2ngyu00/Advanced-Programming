#include <stdio.h>

int main()
{
    char s1[10];
    int n1 = 2022;

    char s2[10];
    float f2 = 3.1415;

    sprintf(s1, "%d", n1);
    sprintf(s2, "%f", f2);

    printf("%s\n", s1);
    printf("%s\n", s2);

    return 0;
}
