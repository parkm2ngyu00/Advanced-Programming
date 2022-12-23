#include <stdio.h>

void hello()
{
    printf("Hello World\n");
}

int main()
{
    // memory address of the 'hello' function
    printf("%p\n", hello);

    // function pointer
    void (*hello_ptr)();

    // assign hello to hello_ptr
    hello_ptr = hello;

    // possible to run hello through hello_ptr
    hello_ptr(); // "Hello World"

    return 0;
}
