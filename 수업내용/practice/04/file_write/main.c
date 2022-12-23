#include <stdio.h>

int main()
{
    FILE *fp = fopen("hello.txt", "w");

    fprintf(fp, "%s\n", "Hello, World!");
    fprintf(fp, "%s\n", "See you again!");

    fclose(fp);

    return 0;
}
