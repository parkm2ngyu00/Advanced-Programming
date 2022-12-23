#include <stdio.h>

int main()
{
    FILE *fp = fopen("hello.txt", "r");
    if (fp != NULL) {
        char buffer[20];
        char *line;

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        fclose(fp);
    }

    return 0;
}
