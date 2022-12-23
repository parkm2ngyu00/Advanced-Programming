#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000
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
    if(data == '(' || data == '[' || data == '{') return TRUE;
    return FALSE;
}
 
int isEqual(Stack *stack, char data) {
    if(data == ')' && peek(stack) == '(') return TRUE;
    if(data == ']' && peek(stack) == '[') return TRUE;
    if(data == '}' && peek(stack) == '{') return TRUE;
    return FALSE;
}

char str[MAX_LEN] = {0};

int main(void)
{
    int test_case; 
    int len;
    Stack stack;
    scanf("%d",&test_case);
    
    for(int i = 0; i < test_case; i++){
        StackInit(&stack);  //stack init.
        scanf("%s",str);
 
        len = strlen(str);  //get length of str.
 
        for(int j=0; j<len; j++){
            if (isOpen(str[j])) { //case (, {, [, 이면 push.
                push(&stack, str[j]);
            } else if (isEqual(&stack, str[j])) {  //case ),},] 일때 각각 맞는지. 맞으면 pop.
                pop(&stack);
            }
        }
       
        if (isEmpty(&stack)) {
            printf("YES\n");            
        } else {
            printf("NO\n");
        }

    } 
    return 0;
}