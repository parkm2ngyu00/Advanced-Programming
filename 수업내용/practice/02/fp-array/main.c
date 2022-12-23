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
    int (*fp[4])(int, int);

    fp[0] = add;
    fp[1] = sub;
    fp[2] = mul;
    fp[3] = div;

    printf("사칙연산 ({0:add, 1: sub, 2: mul, 3: div} num1 num2): ");
    scanf("%d %d %d", &op, &num1, &num2);

    printf("%d\n", fp[op](num1, num2));

    return 0;
}
