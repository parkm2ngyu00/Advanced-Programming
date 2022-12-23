#include <stdio.h>

struct calc {
    int (*fp)(int, int);
};

int add(int a, int b)
{
    return a + b;
}

int main()
{
    struct calc c;
    c.fp = add;

    printf("%d\n", c.fp(10, 20)); // 30

    return 0;
}
