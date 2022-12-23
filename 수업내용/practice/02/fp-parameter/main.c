#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

void execute(int (*fp)(int, int), int num1, int num2, int *res)
{
    *res = fp(num1, num2);
}

int main()
{
    int res = 0;

    execute(add, 10, 20, &res);

    printf("%d\n", res);

    return 0;
}
