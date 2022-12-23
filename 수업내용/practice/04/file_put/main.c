#include <stdio.h>

int main()
{
    FILE *fp = fopen("hello.txt", "w");

    fputs("Hello, World!", fp);
    fputs("Hello, World!", fp);

    fclose(fp);

    return 0;
}
