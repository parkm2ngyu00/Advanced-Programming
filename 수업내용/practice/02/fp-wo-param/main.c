#include <stdio.h>

void hello()
{
    printf("Hello World\n");
}

int main()
{
    void (*hello_ptr)();

    hello_ptr = hello;
    hello_ptr(); // "Hello World"

    return 0;
}
