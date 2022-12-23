# 컴파일 (Compile)

- 코드를 작성하면 꼭 하는 과정

    - (실습) 'practice/02/make-test' 디렉토리 생성 후 이동

        ```
        mkdir -p practice/02/make-test
        cd practice/02/make-test
        ```

    - (실습) 아래의 파일들을 생성한다.

        - common.h

        ```
        #include <stdio.h>
        ```

        - test1.h

        ```
        #include "common.h"

        int test1();
        ```

        - test1.c

        ```
        #include "test1.h"

        int test1() {
            printf("test1\n");
            return 0;
        }
        ```

        - test2.h

        ```
        #include "common.h"

        int test2();
        ```

        - test2.c

        ```
        #include "test2.h"

        int test2() {
            printf("test2\n");
            return 0;
        }
        ```

        - main.c

        ```
        #include "test1.h"
        #include "test2.h"

        int main() {
            test1();
            test2();

            return 0;
        }
        ```

- 위의 소스 코드를 컴파일 하려면?

    - (실습) 단순하게 컴파일을 하면?

        ```
        gcc -o main main.c
        ```

    - 아래와 같은 에러 메시지가 뜸

        ```
        /usr/bin/ld: /tmp/ccSYNAmN.o: in function `main':
        main.c:(.text+0xe): undefined reference to `test1'
        /usr/bin/ld: main.c:(.text+0x18): undefined reference to `test2'
        collect2: error: ld returned 1 exit status
        ```

    - (실습) 여러 소스 파일을 만들었으니, 각각에 대한 오브젝트 파일 생성 필요

        ```
        gcc -c main.c
        gcc -c test1.c
        gcc -c test2.c
        ```

    - (실습) 그리고 생성된 오브젝트 파일들을 통해 컴파일

        ```
        gcc -o main main.o test1.o test2.o
        ```

    - (실습) 이제 정상적으로 프로그램이 동작함

        ```
        ./main
        test1
        test2
        ```

# 복잡한 컴파일 과정

- 파일의 개수가 적을 때는 개별적으로 컴파일하는 것이 큰 문제가 되지 않음
- 하지만, 프로젝트 크기가 커지면 필요한 명령어의 수도 많아져 복잡해짐

    - 특히, 파일들이 여러 디렉토리로 분산되어 있다면 더 그러함

- 필요한 명령어들을 쉘 스크립트 형태로 만들어서 사용하면?

    - 물론 쉘 스크립트를 활용해도 됨
    - 하지만, 파일 하나만 바뀌어도 스크립트를 다시 수정해야 함

- 이러한 컴파일 과정의 복잡도를 줄이기 위한 방법으로 'make'를 사용

# make

- 주어진 쉘 명령어들을 조건에 맞게 실행하는 프로그램

- 어떠한 조건으로 명령어를 실행할지 명시된 파일이 'Makefile'

- 터미널에서 'make'를 실행하면 현재 위치에 있는 'Makefile'을 참조하여 실행

# Makefile

- Makefile의 기본 구조

    ```
    target ... : prerequisites ...
    (tab)   recipe
    (tab)   recipe
    ```

    - target

        - make 명령어를 실행할 때 부를 대상
        - 'make build' 라고 명령어를 실행한다면, 'build' 라는 target이 실행됨

    - recipe

        - 실행 할 명령어
        - 명령어를 쓸 때는 반드시 탭 (TAB)으로 들여쓰기를 해주어야 함

            - 스페이스로 들여쓰기 하면 안 됨

        - 요즘 사용하는 대부분의 코드 편집기들에서는 스페이스를 자동으로 탭으로 변환하는 기능을 많이 제공
        - 하지만, 해당 기능이 꺼져 있거나 자동 변환을 제공하지 않을 수도 있으니 항상 주의 할 것!

    - prerequisites

        - 필요 조건들
        - 다른 말로 의존 파일 (dependency)라고도 함

- Makefile 작성

    - (실습) 우선, 앞서 만든 오브젝트 파일들을 삭제한다.

        ```
        rm *.o
        ```

    - (실습) 아래의 내용을 Makefile 이라는 이름의 파일로 생성한다.

        ```
        test1.o: test1.c test1.h
            gcc -c test1.c
        
        test2.o: test2.c test2.h
            gcc -c test2.c
        
        main.o: main.c test1.h test2.h
            gcc -c main.c
        
        main: main.o test1.o test2.o
            gcc -o main test1.o test2.o main.o
        ```

- Makefile을 이용하여 컴파일

    - (실습) 아래의 명령어를 실행한다.

        ```
        make main
        ```

    - 실행 결과

        ```
        gcc -c test1.c
        gcc -c test2.c
        gcc -c main.c
        gcc -o main test1.o test2.o main.o
        ```

    - 내부 동작

        1. Makefile 내 main target을 찾음
        2. main target을 실행하기 위해 test1.o test2.o main.o가 필요
        3. 해당 파일이 없다면, 각 파일명으로 된 target을 찾음
        4. test1.o의 경우 test1.h와 test1.c가 필요
        5. 해당 파일이 존재한다면, 'gcc -c test1.c'를 실행
        6. 마찬가지로 test2.o와 main.o에 대한 target을 실행
        7. test1.o test2.o main.o가 모두 준비가 되면, main target 내 명령어를 실행
        8. 최종적으로 main 파일(바이너리)가 생성

- Makefile 사용법

    - 변수

        - Makefile 내에서 변수들을 정의하여 사용할 수 있음

            ```
            CC = gcc

            test1.o: test1.c test1.h
                $(CC) -c test1.c
            ```

        - (실습) Makefile 파일을 아래의 내용으로 수정한다.

            ```
            CC = gcc
            CFLAGS = -Wall -O2
            OBJS = test1.o test2.o main.o

            test1.o: test1.c test1.h
                $(CC) $(CFLAGS) -c test1.c
            
            test2.o: test2.c test2.h
                $(CC) $(CFLAGS) -c test2.c
            
            main.o: main.c test1.h test2.h
                $(CC) $(CFLAGS) -c main.c
            
            main: main.o test1.o test2.o
                $(CC) $(CFLAGS) -o main $(OBJS)
            ```

        - (실습) 앞서 만든 오브젝트 파일들을 삭제한다.

            ```
            rm *.o
            ```

        - (실습) 아래의 명령어를 실행한다.

            ```
            make main
            ```

            - 앞서 실행했던 결과도 동일한 결과를 확인할 수 있다.

    - PHONY

        - make를 실행할 때 target 이름의 파일이 존재할 경우 해당 target이 실행되지 않음

            - 일반적으로 Makefile을 만들 때 빌드 관련된 파일들을 제거하는 명령을 추가함

                - (실습) clean target을 추가한다.

                    ```
                    clean:
                        rm -f *.o main
                    ```

                - (실습) 'make clean' 실행한다.

                    ```
                    make clean
                    ```

                - 실행 결과

                    ```
                    rm -f *.o main
                    ```

            - 만약, 'clean'이라는 파일이 존재한다면?

                - (실습) clean 파일 생성한다.

                    ```
                    touch clean
                    ```

                - (실습) 'make clean' 실행한다.

                    ```
                    make clean
                    ```

                - 실행 결과

                    ```
                    make: 'clean' is up to date.
                    ```

            - 그럼, 어떻게 clean target을 실행할 수 있을까?

                - 이 때, PHONY를 사용함 (의존 파일의 상태와 무관하게 항상 실행)

                    - (실습) Makefile을 아래와 같이 수정한다.

                        ```
                        .PHONY: clean
                        clean:
                            rm -f *.o main
                        ```

                        - 참고로 PHONY 앞에 '.'이 있음
    
    - 패턴

        - 빌드에 필요한 파일들이 수십 ~ 수백 개가 된다면, 하나 하나 다 명시하는 것은 어려우면서 비효율적임
        - 이런 이유로 Makefile에 몇 가지 패턴들이 사전 정의되어 있음

            - %.o

                - 와일드 카드로 마치 *.o 와 같다고 보면 됨
                - 즉, .o로 끝나는 모든 파일 이름들이 target이 될 수 있음

                - 예시

                    ```
                    test1.o: test1.c test1.h
                        $(CC) $(CFLAGS) -c test1.c
                    ```

                    ```
                    %.o: %.c %.h
                        $(CC) $(CFLAGS) -c $<
                    ```

                    - 참고로 패턴은 target과 prerequisites 부분에만 사용할 수 있음
                    - 따라서, recipe 부분에는 %.c와 같은 패턴을 사용할 수 없음
            
    - 자동변수

        - Makefile에서는 여러 자동 변수들을 제공

            ```
            test1.o: test1.c test1.h
            ```

            - $@ : target의 이름에 대응 (test1.o)
            - $< : 의존 파일 목록에 첫 번째 파일에 대응 (test1.c)
            - $^ : 의존 파일 목록 전체 (test1.c test1.h)
            - $? : target 보다 최신인 의존 파일들에 대응
            - $+ : $^와 비슷하지만, 중복된 파일 이름들까지 모두 포함

    - 하지만, 패턴과 자동변수를 통해 모든 것을 표현할 수 있는 것은 아님

        - 예시

            ```
            main.o : main.c test1.h test2.h
                $(CC) $(CFLAGS) -c main.c
            ```

            - 위 경우 main.h가 없고 test1.h와 test2.h가 존재하기 때문에 패턴으로 표현하기 어려움

    - vpath

        - 프로그램의 크기가 클 경우 단일 디렉토리 내 모든 소스 파일을 두기 어려움
        - 소스 파일들이 여러 디렉토리로 분산되어 있는 경우, target과 prerequisites을 정의하기 어려움
        - vpath는 명시적으로 소스 파일 위치를 정의하지 않아도 하위 디렉토리 내 소스 파일을 자동으로 찾아 target과 prerequisites에 적용

        - vpath 활용

            ```
            vpath %.c src_1 src_2

            test.o: test.c
                ...
            ```

            - Makefile이 위치한 디렉토리 내 test.c가 없으면 src_1과 src_2 디렉토리를 검색해 test.c 파일을 찾음

    - Makefile에서 자주 사용하는 기능

        - $(addsuffix surfix, string)

            - $(addsurfix .c, test1 test2 main) => test1.c test2.c main.c

        - $(addprefix prefix, string)

            - $(addprefix src/, test1 test2 main) => src/test1 src/test2 src/main
        
        - $(shell 명령어)

            - SH = $(shell ls *.c) => shell 명령에 대한 결과가 변수에 들어감

        - $(subst 찾을 문자열, 변경할 문자열, 대상 문자열)

            - "대상 문자열"에서 "찾을 문자열"을 "변경할 문자열"로 변경함

        - $(patsubst 찾을 패턴, 변경할 패턴, 대상 문자열)

            - subst와 기능은 동일하나 확장자를 바꿀 때 사용함

        - $(strip 대상문자열)

            - 대상 문자열에서 모든 공백을 1칸으로 줄임

        - $(filter 찾을 문자열, 대상 문자열)

            - 대상 문자열에서 찾을 문자열을 포함한 문자열을 찾아서 저장함
        
        - $(filter-out 찾을 문자열, 대상 문자열)

            - filter와 반대로 찾을 문자열이 있는 경우를 제외하고 저장함

        - $(join 원본 문자열, 붙일 문자열)

            - 원본 문자열 뒤에 붙일 문자열을 추가하여 하나의 문자열로 만듬

        - $(dir 대상 문자열)

            - 대상 문자열에서 파일명 부분을 제외한 경로명만 추출함
        
        - $(notdir 대상 문자열)

            - 대상 문자열에서 파일명만 추출함

        - $(basename 대상 문자열)

            - 대상 문자열에서 확장자를 제외한 문자열만 추출함


    - Default Target

        - 'make'를 실행할 때 target을 지정하지 않으면 첫번째 target이 실행됨
        - 위의 예제에서 'make main'이 아닌 'make'만으로 main을 실행하고 싶다면, 아래와 같이 순서를 변경하면 됨

            ```
            CC = gcc
            CFLAGS = -Wall -O2
            OBJS = test1.o test2.o main.o

            main: $(OBJS)
                $(CC) $(CFLAGS) -o main $(OBJS)

            %.o: %.c %.h
                $(CC) $(CFLAGS) -c $<

            main.o: main.c test1.h test2.h
                $(CC) $(CFLAGS) -c main.c

            .PHONY: clean
            clean:
                rm -f *.o main
            ```

# Makefile 활용

- (실습) Makefile을 이용해서 코드 컴파일

    - 일반적으로 소스 파일을 단일 디렉토리에 모두 두지 않음 (특히, 규모가 있는 프로그램이라면 더욱 그러함)

    - practice/simple-nids/Makefile

        ```
        .PHONY: all clean

        CC = gcc

        INC_DIR = include
        SRC_DIR = main reception decoder flow detection log
        OBJ_DIR = obj

        CFLAGS = -O2 -Wall -std=gnu99 $(addprefix -I,$(shell find $(SRC_DIR) -type d))
        LDFLAGS = -lpthread

        PROG = nids

        # find 명령어를 통해 모든 c 파일을 찾는다.

        SRC = $(shell find [빈칸 채우기] -name '*.c')
        OBJ = $(patsubst %.c, %.o, $(notdir $(SRC)))

        # 각각의 c 파일이 여러 디렉토리에 분산되어 있다.
        # vpath를 통해 디렉토리를 명시적으로 지정하지 않아도 각 파일을 찾을 수 있도록 한다.
        # 참고로, 필요한 디렉토리 정보는 이미 위에서 변수로 정의하였다.

        vpath %.c [빈칸 채우기]
        vpath %.o [빈칸 채우기]

        all: $(PROG)

        # CC와 LDFLAGS를 이용하여 오브젝트 파일들을 Linking, 최종 바이너리를 생성한다.

        $(PROG): $(addprefix $(OBJ_DIR)/, $(OBJ))
            mkdir -p $(@D)
            $(CC) -o [빈칸 채우기] [빈칸 채우기] $(LDFLAGS)
        
        # CC와 CFLAGS를 이용하여 c 파일들을 컴파일한다.

        $(OBJ_DIR)/%.o: %.c
            mkdir -p $(@D)
            $(CC) $(CFLAGS) -o [빈칸 채우기] -c [빈칸 채우기]
        
        # 생성한 바이너리와 오브젝트 파일들을 제거한다.

        clean:
            rm -rf [빈칸 채우기] [빈칸 채우기]
        ```
