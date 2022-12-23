#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signo);

int main()
{
    int cnt = 1;

    // SIGINT에 대한 signal handler 정의
    signal(SIGINT, (void *)sig_handler);

    while (1) {
        printf("%d\n", cnt++);
        sleep(1);
    }

    return 0;
}

void sig_handler(int signo)
{
    printf("Got an interrupt\n");
    signal(SIGINT, SIG_DFL);
}
