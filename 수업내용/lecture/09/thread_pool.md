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

# Thread Pool
 
- 작업을 처리 하기 위한 쓰레드를 미리 생성한 후 작업 큐(Queue)에 작업이 들어오면 하나씩 쓰레드가 맡아서 처리

## 그럼 왜 Thread Pool을 만드는 것인가?
    
    - 우리가 사용하는 자원 (CPU, Memory)는 항상 제한이 있음
    - 따라서, 무한정 쓰레드를 만들 수 없기 때문에 효율적인 처리와 함께 자원 관리를 하기 위해 Thread Pool을 사용

## Thread Pool의 단점

    - 너무 많이 만들면 아무 일도 안 하는 쓰레드들이 불필요하게 메모리를 차지
    - 병렬적으로 작업을 처리할 때 작업의 불균형으로 일부 쓰레드만 일을 하고 다른 쓰레드들은 유휴 상태에 빠질 수 있음

## Thread Pool을 동작원리

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Ft1.daumcdn.net%2Fcfile%2Ftistory%2F231B374B595F67F43A)

# 실습 4: 쓰레드 풀 (Thread Pool)

- All implementation should be under practice/simple-hids.

- Implement the function for initializing and destroying a thread pool.

    - practice/simple-hids/main.c

- Use the thread pool when calculating the MD5 hashes for given files.
