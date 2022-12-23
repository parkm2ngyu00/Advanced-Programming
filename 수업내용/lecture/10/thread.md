# Process vs. Thread

- Process

    - 실행되고 있는 프로그램
    - 운영체제로 부터 자원을 할당 받는 작업의 단위
    - 스케쥴링의 대상이 되는 작업(task)과 거의 같은 의미로 사용
    - 여러 프로세서를 사용하면 멀티 프로세싱, 같은 시간에 여러 개의 프로그램을 띄우는 시분할 방식을 멀티태스킹이라고 함

- Thread

    - 프로세스 내에서 실행되는 흐름의 단위
    - 프로세스가 할당 받은 자원을 이용하는 실행의 단위
    - 하나의 프로그램 환경에서 둘 이상의 쓰레드를 동시에 실행하는 것을 멀티쓰레딩이라고 함

##

- 멀티프로세스와 멀티쓰레드는 모두 여러 흐름이 동시에 진행된다는 점에서 비슷한 부분이 있음
- 멀티 프로세스에서 각 프로세스는 독립된 실행 환경 (별개의 메모리)를 가짐
- 멀티쓰레드는 프로세스 내 메모리를 공유하며, 프로세스 간 전환 속도보다 쓰레드 간 전환 속도가 빠름
- 멀티쓰레드의 경우 CPU가 여러 개일 때 각각의 CPU에 쓰레드를 하나씩 할당할 수 있어 성능 향상이 도움이 됨
- 멀티쓰레드의 단점이라고 하면 쓰레드를 중 어떤 것이 먼저 실행되고 어떤 것이 나중에 실행될 지 실행 순서를 알 수 없음

# Concurrency vs. Parallelism

- 동시성은 싱글 코어에서 멀티 쓰레드를 동작시키기 위한 방식으로 여러 쓰레드가 번갈아가며 실행
- 병렬성은 멀티 코에에서 멀티 쓰레드를 동작시큰 방식으로 한 개 이상의 쓰레드가 각 코어들에서 동시에 실행되는 것을 의미

    - 데이터 병렬성 (data parallelism)

        - 전체 데이터를 쪼개 서브 데이터로 만든 후 각 데이터를 분리된 쓰레드에서 병렬 처리

    - 작업 병렬성 (task parallelism)

        - 서로 다른 작업을 병렬 처리

# POSIX Thread

- 주요 함수

    - int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*func)(void *), void *arg);

        - thread: 쓰레드 식별자
        - attr: 쓰레드 속성, 일반적으로 NULL을 입력
        - func: 쓰레드 형태로 호출할 함수 이름
        - arg: 함수 파라미터

    - int pthread_join(pthread_t thread, void **ret);

        - thread: 쓰레드 식별자
        - ret: 함수 리턴 값

- practice/10/thread 밑에 main.c 파일을 만들고 아래의 내용을 작성

    ```
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
    ```

- 코드 컴파일 후 실행

    ```
    gcc -o main main.c -lpthread
    ./main
    ```

# 선택: 여러 디렉토리 모니터링

- All implementation should be under practice/simple-hids.

- The current implementation targets a single directory.

- Implement the functions that monitor the changes in multiple directories using threads.

    - ./simple_hids /bin /usr/bin /home/vagrant/practice

        - argv[0] = ./simple_hids
        - argv[1] = /bin
        - argv[2] = /usr/bin
        - argv[3] = /home/vagrant/practice
