# 변수에 대한 포인터

- 포인터 변수 초기화

    ```
    int *ptr = NULL;
    ```

- 포인터 참조

    ```
    int a = 10;
    int *b = &a;

    printf("a=%d, b=%d\n", a, *b); // a=10, b=10
    ```

- 포인터 역참조

    ```
    int a = 10;
    int *b = &a;

    printf("a's address: %p, b's value: %p\n", &a, b); // a의 주소값
    ```

- 포인터 연산

    ```
    int numbers[] = {1, 2, 3, 4, 5};

    int *ptr = numbers;

    printf("*ptr = %d\n", *ptr); // 1

    ptr = ptr + 1;

    printf("*ptr = %d\n", *ptr); // 2
    ```

- 2차원 배열

    ```
    int arr[2][5] = {
        {1,2,3,4,5},
        {6,7,8,9,10}
    };

    int *ptr1 = &arr[0][0]; // arr[0][0]의 주소값

    printf("*ptr1 = %d\n", *ptr1); // 1

    int *ptr2 = arr[0]; // arr[0]의 주소값 (arr[0]의 시작주소 = arr[0][0])

    printf("*ptr2 = %d\n", *ptr2); // 1

    // arr[2][5] -> arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

    printf("(*arr)[0] = %d\n", (*arr)[0]); // 1
    printf("(*arr)[1] = %d\n", (*arr)[1]); // 2
    printf("(*arr)[5] = %d\n", (*arr)[5]); // 6
    
    printf("(*arr+1)[0] = %d\n", (*arr+1)[0]); // 2
    printf("(*arr+1)[1] = %d\n", (*arr+1)[1]); // 3
    printf("(*arr+1)[5] = %d\n", (*arr+1)[5]); // 7

    printf("*(arr)[0] = %d\n", *(arr)[0]); // 1
    printf("*(arr+1)[0] = %d\n", *(arr+1)[0]); // 6
    ```

# 함수에 대한 포인터

- 변수에 대한 포인터처럼 함수도 똑같이 주소값을 가지고 있기에 함수를 포인터 변수에 저장하여 주고 받을 수 있다.

    - (실습) 'practice/02/fp-test' 디렉토리 생성 후 이동

        ```
        mkdir fp-test
        cd fp-test
        ```

    - (실습) 'main.c' 파일에 아래의 내용 작성

        ```
        #include <stdio.h>

        void hello()
        {
            printf("Hello World\n");
        }

        int main()
        {
            printf("%p\n", hello);
            return 0;
        }
        ```

    - (실습) 컴파일 후 실행

        ```
        gcc -o main main.c
        ./main
        ```

    - 실행 결과

        ```
        0x56402f654169
        ```

- 파라미터와 리턴값이 없는 경우

    - 함수 포인터 = 반환값자료형 (*함수포인터이름)();

    - (실습) 'practice/02/fp-wo-param' 디렉토리 생성 후 이동

        ```
        mkdir fp-wo-param
        cd fp-wo-param
        ```

    - (실습) 'main.c' 파일에 아래의 내용 작성

        ```
        #include <stdio.h>

        void hello()
        {
            printf("Hello World\n");
        }

        int main()
        {
            void (*hello_ptr)();

            hello_ptr = hello;
            hello_ptr(); // "Hello World"

            return 0;
        }
        ```

    - (실습) 컴파일 후 실행

        ```
        gcc -o main main.c
        ./main
        ```

    - 실행 결과

        ```
        Hello World
        ```

- 파라미터와 리턴값이 있는 경우

    - 함수 포인터 = 반환값자료형 (*함수포인터이름)(매개변수자료형1, 매개변수자료형2);

    - (실습) 'practice/02/fp-w-param' 디렉토리 생성 후 이동

        ```
        mkdir fp-w-param
        cd fp-w-param
        ```

    - (실습) 'main.c' 파일에 아래의 내용 작성

        ```
        #include <stdio.h>

        int add(int a, int b)
        {
            return a + b;
        }

        int mul(int a, int b)
        {
            return a * b;
        }

        int main()
        {
            int (*fp)(int , int);

            fp = add;
            printf("%d\n", fp(10, 20)); // 30

            fp = mul;
            printf("%d\n", fp(10, 20)); // 200

            return 0;
        }
        ```

        - 위와 같이 상황에 따라서 다른 함수를 참조할 수 있다

    - (실습) 컴파일 후 실행

        ```
        gcc -o main main.c
        ./main
        ```

    - 실행 결과

        ```
        30
        200
        ```

# 함수 포인터의 활용

- (실습) 'practice/02/fp-example' 디렉토리 생성 후 이동

    ```
    mkdir fp-example
    cd fp-example
    ```

- (실습) 'main.c' 파일에 아래의 내용 작성

    ```
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
        int (*fp)(int, int) = NULL;

        printf("사칙연산 (num1 {+|-|*|/} num2): ");
        scanf("%d %lc %d", &num1, &op, &num2);

        switch (op) {
        case '+':
            fp = add;
            break;
        case '-':
            fp = sub;
            break;
        case '*':
            fp = mul;
            break;
        case '/':
            fp = div;
            break;
        }
        
        printf("%d %lc %d = %d\n", num1, op, num2, fp(num1, num2));

        return 0;
    }
    ```

- (실습) 컴파일 후 실행

    ```
    gcc -o main main.c
    ./main
    사칙연산 (num1 {+|-|*|/} num2): 10 + 20
    10 + 20 = 30
    ./main
    사칙연산 (num1 {+|-|*|/} num2): 30 - 10
    30 - 10 = 20
    ./main
    사칙연산 (num1 {+|-|*|/} num2): 15 * 20
    15 * 20 = 300
    ./main
    사칙연산 (num1 {+|-|*|/} num2): 100 / 2
    100 / 2 = 50
    ```

# 함수 포인터 배열

- (실습) 'practice/02/fp-array' 디렉토리 생성 후 이동

    ```
    mkdir fp-array
    cd fp-array
    ```

- (실습) 'main.c' 파일에 아래의 내용 작성

    ```
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
    ```

    - 참고: 일반적인 배열 초기화처럼 함수 포인터 배열도 한번에 초기화 가능

        ```
        int (*fp[4])(int, int) = {add ,sub, mul, div};
        ```

- (실습) 컴파일 후 실행

    ```
    gcc -o main main.c
    ./main
    사칙연산 ({0:add, 1: sub, 2: mul, 3: div} num1 num2): 0 10 20
    30
    ./main
    사칙연산 ({0:add, 1: sub, 2: mul, 3: div} num1 num2): 1 30 10
    20
    ./main
    사칙연산 ({0:add, 1: sub, 2: mul, 3: div} num1 num2): 2 15 20
    300
    ./main
    사칙연산 ({0:add, 1: sub, 2: mul, 3: div} num1 num2): 3 100 2
    50
    ```

# 함수 포인터를 구조체 멤버로 사용

- 구조체 내 함수 포인터 정의

    ```
    struct 구조체_이름 {
        반환값자료형 (*함수포인터이름)(매개변수자료형1, 매개변수자료형2);
    }
    ```

- (실습) 'practice/02/fp-struct' 디렉토리 생성 후 이동

    ```
    mkdir fp-struct
    cd fp-struct
    ```

- (실습) 'main.c' 파일에 아래의 내용 작성

    ```
    #include <stdio.h>

    struct calc {
        int (*fp)(int, int);
    };

    int add(int a, int b)
    {
        return a + b;
    }

    int main()
    {
        struct calc c;
        c.fp = add;

        printf("%d\n", c.fp(10, 20)); // 30

        return 0;
    }
    ```

- (실습) 컴파일 후 실행

    ```
    gcc -o main main.c
    ./main
    ```

- 실행 결과

    ```
    30
    ```

# 함수 포인터를 매개변수로 전달

- 함수 정의

    ```
    반환값자료형 함수이름( 함수포인터반환값자료형 (*함수포인터이름)(함수포인터매개변수자료형1, 함수포인터매개변수자료형2) )
    {
        //
    }
    ```

- (실습) 'practice/02/fp-parameter' 디렉토리 생성 후 이동

    ```
    mkdir fp-parameter
    cd fp-parameter
    ```

- (실습) 'main.c' 파일에 아래의 내용 작성

    ```
    #include <stdio.h>

    int add(int a, int b)
    {
        return a + b;
    }

    void execute(int (*fp)(int, int), int num1, int num2, int *res)
    {
        *res = fp(num1, num2);
    }

    int main()
    {
        int res = 0;

        execute(add, 10, 20, &res);

        printf("%d\n", res);

        return 0;
    }
    ```

- (실습) 컴파일 후 실행

    ```
    gcc -o main main.c
    ./main
    ```

- 실행 결과

    ```
    30
    ```

# Function Pointer 활용

- 주어진 옵션에 따라 모듈 선택 조건

    - Reception

        - Interface Name이 들어오면 pcap_live(char *) 선택
        - Interface Name 없이 Pcap File Path만 들어오면 pcap_file(char *) 선택
        - 옵션이 정의되지 않을 경우 기본적으로 pcap_live(char *) 선택

    - Decoder

        - decoder() 선택

    - Detection

        - "string1"이 들어오면 match_string1() 선택
        - "string2"가 들어오면 match_string2() 선택
        - 옵션이 정의되지 않을 경우 match_string1() 선택

        - '-r' flag가 set되면 match_regex() 호출
        - 옵션이 정의되지 않을 경우 NULL값을 주고, match_regex()는 호출하지 않음
    
    - Log

        - '-l' 옵션의 값이 'stdout'이면 log_stdout(char *) 선택
        - '-l' 옵션의 값이 'stdout'이 아니라면 log_file(char *) 선택
        - 옵션이 정의되지 않을 경우 기본적으로 log_stdout(char *) 선택

    - practice/simple-nids/main/include/context.h

        - context.h 내 function pointer 변수들이 정의되어 있음

            ```
            typedef struct context_s {
                ...

                char source[MAX_STRING];
                char log[MAX_STRING];

                // function pointer for packet reception
                int (*reception_func)(struct context_t *);

                // function pointer to stop packet reception
                int (*reception_destroy_func)();

                // function pointer for protocol parsing
                int (*decoder_func)(struct context_t *, struct raw_packet_t *raw);

                // function pointer for string matching
                int (*string_match_func)(struct context_t *);

                // function pointer for regex matching
                int (*regex_match_func)(struct context_t *);

                // function pointer for logging
                int (*log_func)(struct context_t *);
            } context_t;
            ```

    - practice/simple-nids/main/context.c

        - 전달된 옵션과 모듈 선택 조건에 기반하여 함수를 연결하는 부분 구현

        ```
        // command-line arguments

        // ...

        // function pointer configuration

        // ctx->reception_func
        // ctx->reception_destroy_func

        // ctx->decoder_func

        // ctx->string_match_func

        // ctx->regex_match_func

        // ctx->log_func
        ```

    - practice/simple-nids/main/main.c

        - 테스트를 위해 main() 함수 내 function pointer를 통해서 각각의 함수 호출

        ```
        int main(int argc, char **argv)
        {
            ...

            printf("\nInitialized Simple NIDS\n");

            // ctx.reception_func(&ctx);
            // ctx.decoder_func(&ctx, NULL);
            // ctx.string_match_func(&ctx);
            // ctx.regex_match_func(&ctx);
            // ctx.log_func(&ctx);

            printf("\nDestroyed Simple NIDS\n");

            return 0;
        }
        ```

- 
