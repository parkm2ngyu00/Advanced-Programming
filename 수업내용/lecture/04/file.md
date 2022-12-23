# 파일 입출력

# 서식을 지정하여 파일에 문자열 쓰기

- FILE *포인터이름 = fopen(파일명, 파일모드);

    - FILE *fopen(char const *_FileName, char const *_Mode);
    - 성공하면 파일 포인터를 반환, 실패하면 NULL을 반환

    - 파일 모드

        - "r": 읽기 전용, 파일이 존재해야 함
        - "w": 쓰기 전용, 파일이 없으면 생성하고 있으면 덮어씀
        - "a": 파일 끝에 추가함, 파일이 없다면 생성
        - "r+": 읽기/쓰기, 파일이 존재해야 함 (없으면 NULL 반환)
        - "w+": 읽기/쓰기, 파일이 없으면 생성하고 있으면 덮어씀
        - "a+": 파일 끝에 추가함, 파일이 없으면 생성, 참고로 읽기는 모든 구간 가능하나, 쓰기는 끝에서만 가능
        - "t": 텍스트 모드 (\n | \r\n)
        - "b": 바이너리 모드 (있는 그대로)

- fprintf(파일포인터, 서식, 값1, 값2, ...);

    - int fprintf(FILE * const _Stream, char const * const _Format, ...);
    - 성공하면 쓴 문자열의 길이를 반환, 실패하면 음수를 반환

- fclose(파일포인터);

    - int fclose(FILE *_stream);
    - 성공하면 0을 반환, 실패하면 EOF(-1)를 반환

- 예시

    - practice/04/file_write/main.c

        ```
        #include <stdio.h>

        int main()
        {
            FILE *fp = fopen("hello.txt", "w");

            fprintf(fp, "%s\n", "Hello, World!");
            fprintf(fp, "%s\n", "See you again!");

            fclose(fp);

            return 0;
        }
        ```

    - hello.txt

        ```
        Hello, World!
        See you again!
        ```

# 서식을 지정하여 파일에 문자열 읽기

- fscanf(파일포인터, 서식, 변수의주소1, 변수의주소2, …);

    - int fscanf(FILE * const _Stream, char const * const _Format, ...);
    - 성공하면 읽어온 값의 개수를 반환, 실패하면 EOF(-1)를 반환

- 예시

    - 사전 준비

        ```
        echo "1234 file_read_data1" > data.txt
        echo "5678 file_read_data2" >> data.txt
        ```

    - practice/04/file_read/main.c

        ```
        #include <stdio.h>

        int main()
        {
            int number;
            char data[100];

            FILE *fp = fopen("data.txt", "r");

            fscanf(fp, "%d %s", &number, data);
            printf("%d %s\n", number, data);

            fscanf(fp, "%d %s", &number, data);
            printf("%d %s\n", number, data);

            fclose(fp);

            return 0;
        }
        ```

    - 실행 결과

        ```
        1234 file_read_data1
        5678 file_read_data2
        ```

# 파일에 문자열 쓰기

- fputs(버퍼, 파일포인터);

    - int fputs(char const *_Buffer, FILE *_Stream);
    - 성공하면 음수가 아닌 값을 반환, 실패하면 EOF(-1)을 반환

- 예시

    - practice/04/file_put/main.c

        ```
        #include <stdio.h>

        int main()
        {
            FILE *fp = fopen("hello.txt", "w");

            fputs("Hello, World!", fp);
            fputs("Hello, World!", fp);

            fclose(fp);

            return 0;
        }
        ```

    - hello.txt

        ```
        Hello, World!Hello, World!
        ```

- fwrite(버퍼, 쓰기크기, 쓰기횟수, 파일포인터);

    - size_t fwrite(void const *_Buffer, size_t _ElementSize, size_t _ElementCount, FILE *_Stream);
    - 성공한 쓰기 횟수를 반환, 실패하면 지정된 쓰기 횟수보다 작은 값을 반환

- 예시

    - practice/04/file_write_string/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char *msg = "Hello, World!";

            FILE *fp = fopen("hello.txt", "w");

            fwrite(msg, strlen(msg), 1, fp);
            fwrite(msg, strlen(msg), 1, fp);

            fclose(fp);

            return 0;
        }
        ```

    - hello.txt

        ```
        Hello, World!Hello, World!
        ```

# 파일에서 문자열 읽기

- fgets(버퍼, 버퍼크기, 파일포인터);

    - char *fgets(char *_Buffer, int _MaxCount, FILE *_Stream);
    - 성공하면 읽은 문자열의 포인터를 반환, 실패하면 NULL을 반환

- 예시

    - 사전 준비

        ```
        echo "Hello, World!" > hello.txt
        echo "See you!" >> hello.txt
        ```

    - practice/04/file_get/main.c

        ```
        #include <stdio.h>

        int main()
        {
            char buffer[100];

            FILE *fp = fopen("hello.txt", "r");

            fgets(buffer, sizeof(buffer), fp);
            printf("%s\n", buffer);

            fgets(buffer, sizeof(buffer), fp);
            printf("%s\n", buffer);

            fclose(fp);

            return 0;
        }
        ```

    - 실행 결과

        ```
        Hello, World!
         
        See you!
         
        ```

- fread(버퍼, 읽기크기, 읽기횟수, 파일포인터);

    - size_t fread(void *_Buffer, size_t _ElementSize, size_t _ElementCount, FILE *_Stream);
    - 성공한 읽기 횟수를 반환, 실패하면 지정된 읽기 횟수보다 작은 값을 반환

- 예시

    - 사전 준비

        ```
        echo "Hello, World!" > hello.txt
        echo "See you!" >> hello.txt
        ```

    - practice/04/file_read_string/main.c

        ```
        #include <stdio.h>

        int main()
        {
            char buffer[100] = {0};

            FILE *fp = fopen("hello.txt", "r");

            fread(buffer, sizeof(buffer), 1, fp);

            printf("%s\n", buffer);

            fclose(fp);

            return 0;
        }
        ```

    - hello.txt

        ```
        Hello, World!
        See you!
        ```

- 연속적으로 파일 읽기

    - 사전 준비

        ```
        echo "Hello, 123!" > hello.txt
        echo "Hello, 456!" >> hello.txt
        echo "Hello, 789!" >> hello.txt
        ```

    - practice/04/file_get_loop_1/main.c

        ```
        #include <stdio.h>

        int main()
        {
            FILE *fp = fopen("hello.txt", "r");
            if (fp != NULL) {
                char buffer[20];
                char *line;

                while (!feof(fp)) {
                    line = fgets(buffer, sizeof(buffer), fp);
                    printf("%s", buffer);
                    printf("%s", line);
                }

                fclose(fp);
            }

            return 0;
        }
        ```

    - 실행 결과

        ```
        Hello, 123!
        Hello, 456!
        Hello, 789!
        ```

    - 사전 준비

        ```
        echo "Hello, 123!" > hello.txt
        echo "Hello, 456!" >> hello.txt
        echo "Hello, 789!" >> hello.txt
        ```

    - practice/04/file_get_loop_2/main.c

        ```
        #include <stdio.h>

        int main()
        {
            FILE *fp = fopen("hello.txt", "r");
            if (fp != NULL) {
                char buffer[20];
                char *line;

                while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                    printf("%s", buffer);
                }

                fclose(fp);
            }

            return 0;
        }
        ```

    - 실행 결과

        ```
        Hello, 123!
        Hello, 456!
        Hello, 789!
        ```
