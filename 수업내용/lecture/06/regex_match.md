# 정규표현식 매칭 (Regular Expression Matching)

- 정규표현식을 통해서 문자열을 매칭하기 위해서 regcomp()와 regexec() 함수를 사용함

- 정규표현식 컴파일

    - 함수 원형

        - int regcomp(regex_t *preg, const char *regex, int cflags);

    - 예제

        - practice/06/regcomp 밑에 main.c 파일을 만들고 아래의 내용을 작성

            ```
            #include <stdio.h>
            #include <regex.h>

            int main()
            {
                char pattern[] = "[:word:]";
                regex_t r1;

                int ret = regcomp(&r1, pattern, 0);
                if (ret == 0) {
                        printf("Compiled %s successfully\n", pattern);
                } else {
                        printf("Failed to compile %s\n", pattern);
                }

                return 0;
            }
            ```

        - 코드 컴파일 후 실행

            ```
            gcc -o main main.c
            ./main
            ```

        - 실행 결과

            ```
            Compiled [:word:] successfully
            ```

- 정규표현식 매칭

    - 함수 원형

        - int regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);

    - 예제

        - practice/06/regexec 밑에 main.c 파일을 만들고 아래의 내용을 작성

            ```
            #include <stdio.h>
            #include <regex.h>

            int main()
            {
                regex_t r1;
                int ret;

                char p1[] = "^01[016789][-]?[0-9]{3,4}[-]?[0-9]{4}$";

                char s1[] = "010-1234-5678";
                char s2[] = "017-345-7890";
                char s3[] = "01009876543";
                char s4[] = "0117892345";
                char s5[] = "02-1234-1234";

                ret = regcomp(&r1, p1, REG_EXTENDED);
                if (ret != 0) {
                        printf("Failed to compile %s\n", p1);
                        return -1;
                }

                ret = regexec(&r1, s1, 0, NULL, 0);
                if (ret == 0) {
                        printf("Found %s\n", s1);
                } else if (ret == REG_NOMATCH) {
                        printf("Failed to find %s\n", s1);
                } else {
                        printf("Error!\n");
                }

                ret = regexec(&r1, s2, 0, NULL, 0);
                if (ret == 0) {
                        printf("Found %s\n", s2);
                } else if (ret == REG_NOMATCH) {
                        printf("Failed to find %s\n", s2);
                } else {
                        printf("Error!\n");
                }

                ret = regexec(&r1, s3, 0, NULL, 0);
                if (ret == 0) {
                        printf("Found %s\n", s3);
                } else if (ret == REG_NOMATCH) {
                        printf("Failed to find %s\n", s3);
                } else {
                        printf("Error!\n");
                }

                ret = regexec(&r1, s4, 0, NULL, 0);
                if (ret == 0) {
                        printf("Found %s\n", s4);
                } else if (ret == REG_NOMATCH) {
                        printf("Failed to find %s\n", s4);
                } else {
                        printf("Error!\n");
                }

                ret = regexec(&r1, s5, 0, NULL, 0);
                if (ret == 0) {
                        printf("Found %s\n", s5);
                } else if (ret == REG_NOMATCH) {
                        printf("Failed to find %s\n", s5);
                } else {
                        printf("Error!\n");
                }

                return 0;
            }
            ```

        - 코드 컴파일 후 실행

            ```
            gcc -o main main.c
            ./main
            ```

        - 실행 결과

            ```
            Found 010-1234-5678
            Found 017-345-7890
            Found 01009876543
            Found 0117892345
            Failed to find 02-1234-1234
            ```

        - 참고: Basic vs. Extended

            - [Basic Regex](https://en.wikibooks.org/wiki/Regular_Expressions/POSIX_Basic_Regular_Expressions)
            - [Extended Regex](https://en.wikibooks.org/wiki/Regular_Expressions/POSIX-Extended_Regular_Expressions)

- 정규표현식 메모리 해제

    - 함수 원형

        - void regfree(regex_t *preg);

    - 참고

    - regcomp() 함수를 통해 정규표현식을 컴파일하면 내부적으로 메모리가 할당되고 컴파일된 정규표현식이 저장됨
    - 따라서, 정규표현식을 사용한 후에는 할당된 메모리 해제가 필요함
    - 위 함수 원형에서 볼 수 있듯이 regfree()의 경우 따로 리턴값이 존재하지 않음

    - 예제

        ```
        #include <stdio.h>
        #include <regex.h>

        int main()
        {
            char pattern[] = "[:word:]";
            regex_t r1;

            int ret = regcomp(&r1, pattern, 0);
            if (ret == 0) {
                    printf("Compiled %s successfully\n", pattern);
            } else {
                    printf("Failed to compile %s\n", pattern);
            }

            regfree(&r1);

            return 0;
        }
        ```

# 실습: 정규표현식 엔진

- practice/simple-nids/detection/match_regex.c

    ```
    int match_regex(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet)
    {
        // pattern: rule->regex
        // string: packet->payload

        // if matched, return 1
        // otherwise, return 0

        return 0;
    }
    ```

# 실습: 로깅 엔진

- practice/simple-nids/log/log_stdout.c

    ```
    int log_stdout(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet)
    {
        // char src_ip_addr[16] = {0}, dst_ip_addr[16] = {0};
        // struct in_addr ip_addr;

        // ip_addr.s_addr = rule->src_ip;
        // strcpy(src_ip_addr, inet_ntoa(ip_addr));

        // ip_addr.s_addr = rule->dst_ip;
        // strcpy(dst_ip_addr, inet_ntoa(ip_addr));

        // message format
        // no content + no regex -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message
        // content + no regex    -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; content:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message, rule->content
        // no content + regex    -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; regex:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message, rule->regex
        // content + regex       -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; content:\"%s\"; regex:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message, rule->content, rule->regex

        // print out the message

        return 0;
    }
    ```

- practice/simple-nids/log/log_file.c

    ```
    int log_file(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet)
    {
        // char src_ip_addr[16] = {0}, dst_ip_addr[16] = {0};
        // struct in_addr ip_addr;

        // ip_addr.s_addr = rule->src_ip;
        // strcpy(src_ip_addr, inet_ntoa(ip_addr));

        // ip_addr.s_addr = rule->dst_ip;
        // strcpy(dst_ip_addr, inet_ntoa(ip_addr));

        // open ctx->log (append mode)

        // message format
        // no content + no regex -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message
        // content + no regex    -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; content:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message, rule->content
        // no content + regex    -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; regex:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message, rule->regex
        // content + regex       -> "[ALERT] %s %s %d -> %s %d (msg:\"%s\"; content:\"%s\"; regex:\"%s\";)", protocol extracted from (packet->proto), src_ip_addr, packet->src_port, dst_ip_addr, packet->dst_port, rule->message, rule->content, rule->regex

        // write the message in ctx->log

        // close the file descriptor

        return 0;
    }
    ```
