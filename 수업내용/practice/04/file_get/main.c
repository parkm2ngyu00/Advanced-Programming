#include <stdio.h>

int main()
{
    char buffer[100];

    FILE *fp = fopen("hello.txt", "r");

    fgets(buffer, sizeof(buffer), fp);
    printf("%s\n", buffer);

    fgets(buffer, sizeof(buffer), fp);
    printf("%s\n", buffer);

    fclose(fp);

    return 0;
}
