#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *s1 = "3.14159265";
    float f1;

    f1 = atof(s1);

    printf("%f\n", f1);

    return 0;
}
