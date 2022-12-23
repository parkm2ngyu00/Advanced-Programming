#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    struct Node *next;
} Node;

typedef struct {
    int count;
    Node *front;
    Node *rear;
} Queue;

void push(Queue *queue, int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if(queue->count == 0) {
        queue->front = node;
    } else {
        queue->rear->next = node;
    }
    queue->rear = node;
    queue->count++;
}

int pop(Queue *queue) {
        Node *node = queue->front;
        int data = node->data;
        queue->front = node->next;
        free(node);
        queue->count--;
        return data;
}

int result[50][2] = {{0}};

int main(void) 
{
    Queue queue;
    queue.front = queue.rear = NULL;
    queue.count = 0;

    int personNumber, kill, test_case;
    scanf("%d", &test_case);
    for (int i = 0; i < test_case; i++) {
        scanf("%d %d", &personNumber, &kill);

        for(int i = 0; i < personNumber; i++) {
            push(&queue, i+1);
        }
        pop(&queue);
        while(queue.count > 2) {
            for(int i = 0; i < kill - 1; i++) {
                push(&queue, pop(&queue));
            }
            pop(&queue);
        }
        int a = pop(&queue);
        int b = pop(&queue);
        if (a > b) {
            result[i][0] = b;
            result[i][1] = a;
        }
        else {
            result[i][0] = a;
            result[i][1] = b;
        }
    }
    for (int i = 0; i < test_case; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }

    return 0;
}
