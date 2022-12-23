#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_func(void *arg)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    char *name = (char *)arg;

    sleep(1);

    int i;
    for (i=0; i<5; i++) {
        printf("Thread: %s, pid: %u, tid: %x\n", name, (unsigned int)tid, (unsigned int)pid);
        sleep(1);
    }

    unsigned int *ret = (unsigned int *)malloc(sizeof(unsigned int));
    *ret = tid;

    return ret;
}

int main()
{
    pthread_t thread[2];

    char p1[] = "thread1";
    char p2[] = "thread2";
    char p3[] = "thread3";

    int ret = pthread_create(&thread[0], NULL, thread_func, (void *)p1);
    if (ret < 0) {
        printf("Failed to create a thread\n");
        return -1;
    }

    ret = pthread_create(&thread[1], NULL, thread_func, (void *)p2);
    if (ret < 0) {
        printf("Failed to create a thread\n");
        return -1;
    }

    thread_func((void*)p3);

    void *thread_ret;

    pthread_join(thread[0], (void **)&thread_ret);

    printf("p1 ret: %u\n", *(unsigned int *)thread_ret);
    free(thread_ret);

    pthread_join(thread[1], (void **)&thread_ret);

    printf("p2 ret: %u\n", *(unsigned int *)thread_ret);
    free(thread_ret);

    return 0;
}
