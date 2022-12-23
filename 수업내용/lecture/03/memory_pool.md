# 메모리 풀 (Memory Pool)

- 런타임에 메모리를 동적으로 할당이 필요할 경우 워크로드가 높다면 성능적인 문제가 발생
- 이를 보완하기 위해 고정된 크기의 블록을 미리 할당해 놓은 것
- 애플리케이션은 런타임에 할당된 블럭을 사용함으로 동적 할당 오버헤드를 최소화할 수 있음
- 일반적으로 큐(자료구조)를 이용하여 메모리 풀을 관리

# 메모리 풀의 활용

- 함수 내 지역 변수를 사용할 경우 해당 함수가 종료 시 변수값을 잃게 됨
- 이 때, 동적으로 메모리를 할당 받아 해당 변수에 값을 저장하게 되면 값을 유지할 수 있음
- 만약 워크로드가 낮다면 필요할 때마다 메모리를 할당 받아 사용할 수 있지만, 아니라면?
- 메모리 풀을 통해 미리 할당 받은 블럭을 사용하여 값을 유지
- 더 이상 필요없다면, 초기화 후 다시 메모리 풀에 넣어 추후 다시 사용

# 메모리 풀 구현

- 주요 함수

    - init(number of items)

        - N개의 item을 사전에 할당/초기화 후 큐이나 스택과 같은 자료구조의 메모리 풀에 넣음

    - pull() / pop()

        - 메모리 풀에서 item을 꺼냄
        - 메모리 풀에 item이 없는 경우, 사용중인 item이 반환될 때까지 기다리거나 동적 할당을 통해 새 item을 만들 수도 있음

    - push(item)

        - 다 사용한 item은 초기화 후 다시 메모리 풀에 넣음
        - item의 개수를 유지하며 일정 수 이상일 경우 메모리 풀에 넣지 않고 바로 메모리 공간 반환할 수도 있음

    - destroy()

        - 메모리 풀에 있는 모든 item에 대해서 메모리 공간 반환

- 추가 고려 사항

    - 성능을 높이기 위해 Multi-threading을 활용
    - 이 경우 메모리 풀을 쓰고자 한다면 Lock이 필요

- 실습을 위해 practice/03/memory_pool 디렉토리를 만들고 이동

    ```
    mkdir -p practice/03/memory_pool
    cd practice/03/memory_pool
    ```

- main.c 파일을 아래와 같이 작성

    ```
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>

    #define INITIAL_ITEMS 100
    #define MAXIMUM_ITEMS 200

    struct sample_t {
        int value;
        struct sample_t *next;
    };

    static int items;
    static struct sample_t *sample_pool;
    static pthread_spinlock_t sample_lock;

    int push_sample(struct sample_t *sample)
    {
        memset(sample, 0, sizeof(struct sample_t));

        pthread_spin_lock(&sample_lock);

        if (items + 1 > MAXIMUM_ITEMS) {
            free(sample);
            pthread_spin_unlock(&sample_lock);
            printf("Released a used sample\n");
            return 0;
        }

        if (sample_pool == NULL) {
            sample_pool = sample;
        } else {
            sample->next = sample_pool;
            sample_pool = sample;
        }

        printf("Pushed an empty sample into the sample pool\n");

        items++;

        pthread_spin_unlock(&sample_lock);

        return 0;
    }

    struct sample_t * pop_sample()
    {
        struct sample_t *sample;

        pthread_spin_lock(&sample_lock);

        if (sample_pool == NULL) {
            sample = (struct sample_t *)malloc(sizeof(struct sample_t));
            memset(sample, 0, sizeof (struct sample_t));
            printf("Allocated a new sample\n");
        } else {
            sample = sample_pool;
            sample_pool = sample_pool->next;
            items--;
            printf("Got a sample form the sample pool\n");
        }

        pthread_spin_unlock(&sample_lock);

        return sample;
    }

    int initialize_memory_pool()
    {
        items = 0;

        if (pthread_spin_init(&sample_lock, PTHREAD_PROCESS_PRIVATE)) {
            printf("[ERROR] Failed to initialize sample_lock\n");
            return -1;
        }

        for (int i=0; i<INITIAL_ITEMS; i++) {
            struct sample_t *sample = (struct sample_t *)malloc(sizeof(struct sample_t));
            push_sample(sample);
        }

        return 0;
    }

    int destroy_memory_pool()
    {
        struct sample_t *sample = sample_pool;

        pthread_spin_lock(&sample_lock);

        while (sample != NULL) {
            struct sample_t *temp = sample;
            sample = sample->next;
            free(temp);
        }

        pthread_spin_unlock(&sample_lock);

        pthread_spin_destroy(&sample_lock);

        return 0;
    }

    int main() {
        struct sample_t *sample;

        initialize_memory_pool();

        sample = pop_sample();
        push_sample(sample);

        destroy_memory_pool();

        return 0;
    }
    ```

# 실습: Packet Pool

- practice/simple-nids/pool/include/packet_pool.h

    - 메모리 풀을 생성하기 위해 필요한 정보는 packet_pool.h에 정의되어 있음

        ```
        #define INITIAL_ITEMS 1024
        #define MAXIMUM_ITEMS 2048

        int push_packet(struct packet_t *packet);
        struct packet_t * pop_packet();

        int initialize_packet_pool();
        int destroy_packet_pool();
        ```

- practice/simple-nids/pool/packet_pool.c

    - 'struct packet_t'을 위한 메모리 풀 관련 함수들을 작성

        ```
        static int packet_items;
        static struct packet_t *packet_pool;
        static pthread_spinlock_t packet_lock;

        int push_packet(struct packet_t *packet)
        {
            //
        }

        struct packet_t * pop_packet()
        {
            //
        }

        int initialize_packet_pool()
        {
            //
        }

        int destroy_packet_pool()
        {
            //
        }
        ```
