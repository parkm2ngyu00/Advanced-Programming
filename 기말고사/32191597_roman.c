#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 30
#define TRUE 1
#define FALSE 0
 
typedef struct stack_t {
    char arr[MAX_LEN];
    int top;
} Stack;

void StackInit(Stack *sp) {
    sp->top = -1;
}
 
int isEmpty(Stack *sp) {
    if(sp->top == -1) return TRUE;
    return FALSE;
}
 
void push(Stack *sp, char data) {
    //check full.
    if((sp->top)+1 >= MAX_LEN) return;
    sp->arr[++(sp->top)] = data;
}
 
char pop(Stack *sp) {
    if(isEmpty(sp)) return ' ';
    return sp->arr[(sp->top)--];
}
 
char peek(Stack *sp) {
    if(isEmpty(sp)) return ' ';
    return sp->arr[(sp->top)];
}
 
int isOpen(char data) {
    if(data == 'V' || data == 'L' || data == 'D') return TRUE;
    return FALSE;
}
 
int isEqual(Stack *stack, char data) {
    if(data == 'V' && peek(stack) == 'V') return TRUE;
    if(data == 'L' && peek(stack) == 'L') return TRUE;
    if(data == 'D' && peek(stack) == 'D') return TRUE;
    return FALSE;
}

int main(void) {
    int test_case;
    Stack stack;
    scanf("%d", &test_case);
    int i;
    for (i=0; i<test_case+1; i++) {
        int break_flag = 0;
        if (i == 0) {
            break_flag = 1;
        }
        StackInit(&stack);
        int result = 0;
        int flag_num = 0;
        char buf[20] = {0};
        // scanf("%s", buf);
        gets(buf);
        int len = strlen(buf);
        int j;
        for (j=0; j<len; j++) {
            if (buf[j] >= 97 && buf[j] <= 122) {
                    buf[j] = buf[j] - 32;
            }
            if (buf[j] != 'I' && buf[j] != 'V' && buf[j] != 'X' && buf[j] != 'L' && buf[j] != 'C' && buf[j] != 'D' && buf[j] != 'M') {
                break_flag = 1;
                printf("Error!\n");
                break;
            }
            if (isEqual(&stack, buf[j]) || buf[j] == ' ') {
                printf("Error!\n");
                break_flag = 1;
                break;
            }
            if (peek(&stack) == buf[j]) {
                flag_num++;
            }
            if (flag_num >= 3) {
                printf("Error!\n");
                break_flag = 1;
                break;
            }
            push(&stack, buf[j]);
            switch (buf[j])
            {
            case 'I':
                result += 1;
                break;
            case 'V':
                if (buf[j-1] == 'I')
                    result += 4;
                else
                    result += 5;
                break;
            case 'X':
                if (buf[j-1] == 'I')
                    result += 8;
                else
                    result += 10;
                break;
            case 'L':
                if (buf[j-1] == 'I')
                    result += 48;
                else if (buf[j-1] == 'V')
                    result += 40;
                else if (buf[j-1] == 'X')
                    result += 30;
                else
                    result += 50;
                break;
            case 'C':
                if (buf[j-1] == 'I')
                    result += 98;
                else if (buf[j-1] == 'V')
                    result += 90;
                else if (buf[j-1] == 'X')
                    result += 80;
                result += 100;
                break;
            case 'D':
                if (buf[j-1] == 'I')
                    result += 498;
                else if (buf[j-1] == 'V')
                    result += 490;
                else if (buf[j-1] == 'X')
                    result += 480;
                else if (buf[j-1] == 'L')
                    result += 400;
                else if (buf[j-1] == 'C')
                    result += 300;
                result += 500;
                break;
            case 'M':
                if (buf[j-1] == 'I')
                        result += 998;
                else if (buf[j-1] == 'V')
                    result += 990;
                else if (buf[j-1] == 'X')
                    result += 980;
                else if (buf[j-1] == 'L')
                    result += 900;
                else if (buf[j-1] == 'C')
                    result += 800;
                result += 1000;
                break;
            default:
                break;
            }
        }
        
        if (break_flag) continue;
        printf("%d\n", result);
    }

    return 0;
}            