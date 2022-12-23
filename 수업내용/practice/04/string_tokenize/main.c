#include <stdio.h>
#include <string.h>

int main()
{
    char s1[30] = "Advanced Programming Practice";

    char *ptr = strtok(s1, " ");
    while (ptr != NULL) {
        printf("%s\n", ptr);
        ptr = strtok(NULL, " ");
    }

    return 0;
}
