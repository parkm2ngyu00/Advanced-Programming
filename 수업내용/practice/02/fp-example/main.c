#define _CRT_SECURE_NO_WARNINGS    // scanf 보안 경고로 인한 컴파일 에러 방지

#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int div(int a, int b)
{
    return a / b;
}

int main()
{
    int op, num1, num2;
    int (*fp)(int, int) = NULL;

    printf("사칙연산 (num1 {+|-|*|/} num2): ");
    scanf("%d %lc %d", &num1, &op, &num2);

    switch (op) {
    case '+':
        fp = add;
        break;
    case '-':
        fp = sub;
        break;
    case '*':
        fp = mul;
        break;
    case '/':
        fp = div;
        break;
    }
    
    printf("%d %lc %d = %d\n", num1, op, num2, fp(num1, num2));

    return 0;
}
