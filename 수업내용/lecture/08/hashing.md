# 해시 (Hash)

- 임의의 길이를 가지는 데이터를 고정된 길이의 데이터로 변환
    - 해시 함수: 임의의 길이를 가지는 데이터를 고정된 길이의 데이터로 변환하는 함수

    - 해시 함수 예시: Jenkins Hash Function (one at a time)

        - practice/08/jenkins 밑에 main.c 파일을 만들고 아래의 내용을 작성

        ```
        #include <stdio.h>
        #include <string.h>
        #include <stdint.h>

        uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
            size_t i = 0;
            uint32_t hash = 0;
            while (i != length) {
                hash += key[i++];
                hash += hash << 10;
                hash ^= hash >> 6;
            }
            hash += hash << 3;
            hash ^= hash >> 11;
            hash += hash << 15;
            return hash;
        }

        int main(int argc, char *argv[])
        {
            uint32_t val = jenkins_one_at_a_time_hash((uint8_t *)argv[1], strlen(argv[1]));
            printf("0x%x\n", val);

            return 0;
        }
        ```

    - [List of Hash Functions](https://en.wikipedia.org/wiki/List_of_hash_functions#Non-cryptographic_hash_functions)

- 임의의 길이를 고정된 길이로 변환하다 보니 서로 다른 데이터가 해싱되면서 동일한 해시 값을 가질 수 있음

# 해시 사용 용도

- 해시 테이블을 기반으로 빠른 탐색을 위해 주로 사용됨
    - 해시 테이블: Key-Value 형태로 구성된 테이블

    ![](https://yourbasic.org/algorithms/hash-table.png)

- 또 다른 용도로 무결성 (Integrity) 검증을 위해 사용됨
    - 예시: 비밀번호, 설치 바이너리, 네트워크 패킷

# 해시 사용 용도: 무결성 검증을 위한 MD5 해시 예시

- practice/08/md5 밑에 main.c 파일을 만들고 아래의 내용을 작성

    ```
    #include <stdio.h>
    #include <openssl/md5.h>

    int main(int argc, char *argv[])
    {
        FILE *fp = fopen(argv[1], "rb");
        if (fp == NULL) {
            printf("Failed to open %s\n", argv[1]);
            return -1;
        }

        MD5_CTX ctx;

        MD5_Init(&ctx);

        int bytes;
        unsigned char data[1024];

        while ((bytes = fread(data, 1, 1024, fp)) != 0)
            MD5_Update(&ctx, data, bytes);

        unsigned char c[MD5_DIGEST_LENGTH];

        MD5_Final(c,&ctx);

        int i;
        for(i=0; i<MD5_DIGEST_LENGTH; i++)
            printf("%02x", c[i]);

        printf(" %s\n", argv[1]);

        fclose (fp);

        return 0;
    }
    ```

- 코드 컴파일 후 실행

    ```
    gcc -o main main.c -lssl -lcrypto
    ./main [Target File]
    ```

    - 참고: -lssl과 -lcrypto 옵션이 추가되었음

# 해시 사용 용도: 무결성 검증을 위한 SHA256 해시 예시

- practice/08/sha256 밑에 main.c 파일을 만들고 아래의 내용을 작성

    ```
    #include <stdio.h>
    #include <openssl/sha.h>

    int main(int argc, char *argv[])
    {
        FILE *fp = fopen(argv[1], "rb");
        if (fp == NULL) {
            printf("Failed to open %s\n", argv[1]);
            return -1;
        }

        SHA256_CTX ctx;

        SHA256_Init(&ctx);

        int bytes;
        unsigned char data[1024];

        while ((bytes = fread(data, 1, 1024, fp)) != 0)
            SHA256_Update(&ctx, data, bytes);

        unsigned char c[SHA256_DIGEST_LENGTH];

        SHA256_Final(c,&ctx);

        int i;
        for(i=0; i<SHA256_DIGEST_LENGTH; i++)
            printf("%02x", c[i]);

        printf(" %s\n", argv[1]);

        fclose (fp);

        return 0;
    }
    ```

- 코드 컴파일 후 실행

    ```
    gcc -o main main.c -lssl -lcrypto
    ./main [Target File]
    ```

    - 참고: -lssl과 -lcrypto 옵션이 추가되었음

# 실습: 파일 해시값 추출 (Hash Value Extraction)

- All implementation should be under practice/simple-hids.

- Add a string in the previous entry structure.

    - Before

        ```
        struct entry {
            char name[MAX_STRING]; // entry name
            off_t size;            // file size
            time_t atime;          // time of last access
            time_t mtime;          // time of last modification
            struct entry *sibling;
            struct entry *child;
        }
        ```

    - After

        ```
        struct entry {
            char name[MAX_STRING]; // entry name
            off_t size;            // file size
            time_t atime;          // time of last access
            time_t mtime;          // time of last modification

            char hash[MAX_STRING]; // hash value

            struct entry *sibling;
            struct entry *child;
        }
        ```

- Update the previous code to calculate and store the hash value for each file.

    - To simplify the program, let's use the MD5 hash function for extracting the the hash values of given files.

    - Calculate the MD5 hash for executables while loading sub-directories and files.

        - Implement the functions for MD5 in practice/simple-hids/hash.{c, h}
        - Add the prototypes for the functions in practice/simple-hids/common.h
        - Use the above functions in practice/simple-hids/entry.c
