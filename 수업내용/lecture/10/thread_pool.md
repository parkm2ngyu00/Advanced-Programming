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

##

- Use the thread pool when calculating the MD5 hashes for given files.
