#include <stdio.h>
#include <string.h>

int main()
{
    char *msg = "Hello, World!";

    FILE *fp = fopen("hello.txt", "w");

    fwrite(msg, strlen(msg), 1, fp);
    fwrite(msg, strlen(msg), 1, fp);

    fclose(fp);

    return 0;
}
