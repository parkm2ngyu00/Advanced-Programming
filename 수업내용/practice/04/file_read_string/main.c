#include <stdio.h>

int main()
{
    char buffer[100] = {0};

    FILE *fp = fopen("hello.txt", "r");

    fread(buffer, sizeof(buffer), 1, fp);
    printf("%s\n", buffer);

    fclose(fp);

    return 0;
}
