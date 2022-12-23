# 문자열 처리

# 문자열 길이 구하기

- strlen(문자열포인터);
- strlen(문자배열);

    - size_t strlen(const *_Str);
    - 문자열의 길이를 반환

# 문자열 비교하기

- strcmp(문자열1, 문자열2);

    - int strcmp(const *_Str1, char const *_Str2);
    - 문자열 비교 결과를 반환

- 예시

    - practice/04/string_compare/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[10] = "Hello";
            char *s2 = "Hello";

            int ret = strcmp(s1, s2);

            printf("%d\n", ret);

            return 0;
        }
        ```

    - 참고

        - -1: ASCII 코드 기준으로 문자열2(s2)가 클 때
        - 0: ASCII 코드 기준으로 두 문자열이 같을 때
        - 1: ASCII 코드 기준으로 문자열1(s1)이 클 때

# 문자열 복사하기

- strcpy(대상문자열, 원본문자열);

    - char *strcpy(char *_Dest, char const *_Source);
    - 대상문자열의 포인터를 반환

- 예시

    - practice/04/string_copy/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[10] = "Hello";
            char s2[10];

            strcpy(s2, s1);

            printf("%s\n", s2);

            return 0;
        }
        ```

    - 참고

        - 문자열 자체 뿐만 아니라 마지막에 포함되는 NULL까지 고려해야 함

# 문자열 붙이기

- strcat(최종문자열, 붙일문자열);

    - char *strcat(char *_Destination, char const *_Source);
    - 최종 문자열의 포인터를 반환

- 예시

    - practice/04/string_concatenate/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[10] = "world";
            char s2[20] = "Hello";

            strcat(s2, s1);

            printf("%s\n", s2);

            return 0;
        }
        ```

# 문자열 만들기

- sprintf(배열, 서식, 값);
- sprintf(배열, 서식, 값1, 값2, ...);

    - int sprintf(char * const _Buffer, char const * const _Format, ...);
    - 성공하면 만든 문자열의 길이를 반환, 실패하면 음수를 반환

- 예시

    - practice/04/string_format/main.c

        ```
        #include <stdio.h>

        int main()
        {
            char s1[20];

            sprintf(s1, "Hello, %s", "world!");

            printf("%s\n", s1);

            return 0;
        }
        ```

# 문자열 검색하기

- strchr(대상문자열, 검색할문자);

    - char *strchr(char * const _String, int const _Ch);
    - 문자를 찾았으면 문자로 시작하는 문자열의 포인터를 반환, 문자가 없으면 NULL을 반환

- 예시

    - practice/04/string_find/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[30] = "dankook university";

            char *ptr = strchr(s1, 'n');

            while (ptr != NULL) {
                printf("%s\n", ptr);
                ptr = strchr(ptr + 1, 'n');
            }

            return 0;
        }
        ```

    - 결과

        ```
        nkook university
        niversity
        ```

- strrchr(대상문자열, 검색할문자);

    - char *strrchr(char * const _String, int const _Ch);
    - 문자열의 끝에서부터 역순으로 검색해서 문자를 찾았으면 해당 문자로 시작하는 문자열의 포인터를 반환, 문자가 없으면 NULL을 반환

- 예시

    - practice/04/string_find_from_right/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[30] = "dankook university";

            char *ptr = strrchr(s1, 'n');

            printf("%s\n", ptr);

            return 0;
        }
        ```

    - 결과

        ```
        niversity
        ```

- strstr(대상문자열, 검색할문자열);

    - char *strstr(char * const _String, char const * const _SubString);
    - 문자열을 찾았으면 문자열로 시작하는 문자열의 포인터를 반환, 문자열이 없으면 NULL을 반환

- 예시

    - practice/04/string_find_string/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[30] = "dankook university";

            char *ptr = strstr(s1, "kook");

            printf("%s\n", ptr);

            return 0;
        }
        ```

    - 결과

        ```
        kook university
        ```

# 문자열 자르기

- strtok(대상문자열, 기준문자);

    - char *strtok(char *_String, char const *_Delimiter);
    - 자른 문자열을 반환, 더 이상 자를 문자열이 없으면 NULL을 반환

- 예시

    - practice/04/string_tokenize/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int main()
        {
            char s1[30] = "Advanced Programming Practice";

            char *ptr = strtok(s1, " ");
            while (ptr != NULL) {
                printf("%s\n", ptr);
                ptr = strtok(NULL, " ");
            }

            return 0;
        }
        ```

    - 참고

        - strtok() 함수는 내부적으로 전역변수로 문자열 위치를 관리함
        - 따라서, 연속적으로 strtok()를 사용해야 하며, 중간에 다른 곳에서 strtok() 함수를 사용하면 기존 문자열에 대한 정보를 잃어버림

# 문자열을 정수로 변환하기

- atoi(문자열);

    - int atoi(char const *_String);
    - 성공하면 변환된 정수를 반환, 실패하면 0을 반환

- 예시

    - practice/04/string_atoi/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            char *s1 = "2022";
            int n1;

            n1 = atoi(s1);

            printf("%d\n", n1);

            return 0;
        }
        ```

- atof(문자열);

    - double atof(char const *_String);
    - 성공하면 변환된 실수를 반환, 실패하면 0을 반환

- 예시

    - practice/04/string_atof/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            char *s1 = "3.14159265";
            float f1;

            f1 = atof(s1);

            printf("%f\n", f1);

            return 0;
        }
        ```

# 숫자를 문자열로 변환하기

- sprintf(문자열, "%d", 정수);
- sprintf(문자열, "%f", 실수);

- 예시

    - practice/04/string_sprintf/main.c

        ```
        #include <stdio.h>

        int main()
        {
            char s1[10];
            int n1 = 2022;

            char s2[10];
            float f2 = 3.1415;

            sprintf(s1, "%d", n1);
            sprintf(s2, "%f", f2);

            printf("%s\n", s1);
            printf("%s\n", s2);

            return 0;
        }
        ```

# 실습: Rule Parsing Logic

- practice/simple-nids 밑에 rule.txt 파일이 있음

    ```
    alert {protocol} {srcip} {sport} -> {dstip} {dport} (msg:"message"; options...)
    ```

    - Essentials

        - protocol = [ "ip" | "tcp" | "udp" | "icmp" | "http" ]
        - srcip = [ IP address (x.x.x.x) | "any" ]
        - sport = [ Port number | ICMP type | "any" ]
        - dstip = [ IP address (x.x.x.x) | "any" ]
        - dport = [ Port number | ICMP code | "any" ]

    - Options

        - content:"content";
        - regex:"regex";
        - method: [ "GET" | "POST" | "PUT" | "PATCH" | "DELETE" ];

    - 예시

        ```
        # IP rule

        alert ip any any -> any 5000 (msg:"IP rule example";)
        alert ip any any -> any any (msg:"IP rule example"; content:"payload";)
        alert ip any any -> 221.163.205.3 any (msg:"specific IP example"; content:"boanlab"; regex:"^[0-9]*$";)

        # TCP rule

        alert tcp any any -> any any (msg:"TCP rule example"; content:"payload";)
        alert tcp any any -> any 80 (msg:"TCP rule example"; content:"payload"; regex:"^[a-zA-Z]*$";)

        # HTTP rule

        alert http any any -> any any (msg:"HTTP rule example"; method:"GET"; content:"payload";)
        alert http any any -> any any (msg:"HTTP data example"; content:"payload"; regex:"^[0-9]*$";)

        # UDP rule

        alert udp any any -> any any (msg:"UDP rule example"; content:"payload";)
        alert udp any any -> any 53 (msg:"DNS request example"; content:"google"; regex:"^[a-zA-Z]*$";)
        alert udp any 53 -> any any (msg:"DNS reply example"; content:"google";)

        # ICMP rule

        alert icmp any any -> any any (msg:"ICMP packet";)
        alert icmp any 8 -> 8.8.8.8 0 (msg:"ping request example";)
        alert icmp 8.8.8.8 0 -> any 0 (msg:"ping reply example";)
        ```

- 구현에 필요한 정보는 practice/simple-nids/main/include/common.h 에 정의되어 있음

    ```
    enum {
        PROTO_IPV4 = 1 << 0,
        PROTO_TCP  = 1 << 1,
        PROTO_UDP  = 1 << 2,
        PROTO_ICMP = 1 << 3,
        PROTO_HTTP = 1 << 4,
    };
    ```

- 구현에 필요한 정보는 practice/simple-nids/rule/include/rule_mgmt.h 에 정의되어 있음

    ```
    #define RULE_FILE "rule.txt"
    #define OPTION_LIMIT 10
    ```

- practice/simple-nids/rule/rule_mgmt.c 내 load_rules() 함수를 완성

    ```
    int load_rules(struct context_t *ctx)
    {
        // RULE_FILE 파일 열기

        // while (파일을 한줄씩 읽기) {

            // 'struct rule_t' 타입의 메모리 공간 할당
            // struct rule_t *rule = ...;

            // 할당 받은 메모리 공간 초기화

            // strtok() 함수를 통해서 룰 파싱

                // protocol 파싱 시 고려 사항

                // ip = PROTO_IPV4
                // tcp = PROTO_IPV4 + PROTO_TCP
                // udp = PROTO_IPV4 + PROTO_UDP
                // icmp = PROTO_IPV4 + PROTO_ICMP
                // http = PROTO_IPV4 + PROTO_TCP + PROTO_HTTP

            // 파싱한 결과 출력

            if (rule != NULL) {
                printf("Rule %d:\n", cnt++);
                if (rule->proto == PROTO_HTTP) {
                    printf("  Protocol: %d, SrcIP: %d, DstIP: %d, SrcPort: %d, DstPort: %d, Msg: %s, Content: %s, Regex: %s, Method: %s\n",
                            rule->proto, rule->src_ip, rule->dst_ip, rule->src_port, rule->dst_port, rule->message, rule->content, rule->regex, rule->method);

                } else if (rule->proto == PROTO_ICMP) {
                    printf("  Protocol: %d, SrcIP: %d, DstIP: %d, Type: %d, Code: %d, Msg: %s, Content: %s, Regex: %s\n",
                            rule->proto, rule->src_ip, rule->dst_ip, rule->icmp_type, rule->icmp_code, rule->message, rule->content, rule->regex);

                } else if (rule->proto == PROTO_TCP || rule->proto == PROTO_UDP) {
                    printf("  Protocol: %d, SrcIP: %d, DstIP: %d, SrcPort: %d, DstPort: %d, Msg: %s, Content: %s, Regex: %s\n",
                            rule->proto, rule->src_ip, rule->dst_ip, rule->src_port, rule->dst_port, rule->message, rule->content, rule->regex);

                } else { // PROTO_IPV4
                    printf("  Protocol: %d, SrcIP: %d, DstIP: %d, Msg: %s, Content: %s, Regex: %s\n",
                            rule->proto, rule->src_ip, rule->dst_ip, rule->message, rule->content, rule->regex);
                }
            }

            // 할당 받은 메모리 공간 반환
        }

        // 파일 닫기
    }
    ```
