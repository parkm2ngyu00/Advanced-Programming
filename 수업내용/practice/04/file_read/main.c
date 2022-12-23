#include <stdio.h>

int main()
{
    int number;
    char data[100];

    FILE *fp = fopen("data.txt", "r");

    fscanf(fp, "%d %s", &number, data);
    printf("%d %s\n", number, data);

    fscanf(fp, "%d %s", &number, data);
    printf("%d %s\n", number, data);

    fclose(fp);

    return 0;
}
