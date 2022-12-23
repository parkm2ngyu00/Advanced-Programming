# 단순 문자열 매칭

- 일반적으로 문자열 내 서브 문자열을 찾기 위해서 strstr() 함수를 사용할 수 있음

    - 예시: practice/05/strstr/main.c

        ```
        #include <stdio.h>
        #include <string.h>
        
        int main(void)
        {
            char *string1 = "Advanced Programming Practice";
            char *string2 = "ming";

            char *result = strstr(string1, string2);
            if (result != NULL) {
                printf("%s\n", result);
            } else {
                printf("Not found\n");
            }

            char *string3 = "DKU";

            result = strstr(string1, string3);
            if (result != NULL) {
                printf("%s\n", result);
            } else {
                printf("Not found\n");
            }

            char *string4 = "Dankook\0University";
            char *string5 = "Univ";

            result = strstr(string1, string3);
            if (result != NULL) {
                printf("%s\n", result);
            } else {
                printf("Not found\n");
            }

            return 0;
        }
        ```
    
        - 문제점

            - string.h에서 제공하는 함수들의 경우 기본적으로 Null-Termination을 사용
            - 문자열 중간에 \0이 존재할 경우 \0 뒤는 비교 불가

    - practice/05/strstr2/main.c

        ```
        #include <stdio.h>
        #include <string.h>

        int strstr2(char *s1, int s1_len, char *s2, int s2_len)
        {
            int i, j;
            
            for (i=0; i<(s1_len-s2_len); i++) {
                for (j=0; j<s2_len; j++) {
                    if (s1[i+j] != s2[j])
                        break;
                }

                if (j == s2_len)
                    return 1;
            }
            
            return 0;
        }

        int main(void)
        {
            char *string1 = "Advanced Programming Practice";
            char *string2 = "ming";

            int result = strstr2(string1, 29, string2, 4);
            if (result) {
                printf("Found\n");
            } else {
                printf("Not found\n");
            }

            char *string3 = "DKU";

            result = strstr2(string1, 29, string3, 3);
            if (result) {
                printf("Found\n");
            } else {
                printf("Not found\n");
            }

            char *string4 = "Dankook\0University";
            char *string5 = "Univ";

            result = strstr2(string4, 18, string5, 4);
            if (result) {
                printf("Found\n");
            } else {
                printf("Not found\n");
            }

            return 0;
        }
        ```

        - 앞서 발생했던 Null-Termination 문제를 문자열 길이를 추가하여 해결 가능

# 커누스-모리스-프랫 (KMP) 알고리즘

- Knuth, Morris, Prett가 만든 문자열 검색 알고리즘
- KMP 알고리즘의 경우 O(N+M)의 시간복잡도를 가짐

- KMP 알고리즘에서의 두 가지 개념

    - 접두사 (Prefix)와 접미사 (suffix)
    - 실패 함수 (Pi array) -> check if prefix == suffix

        - ABAABAB의 Pi 배열

            ```
            i      SubString   p[i]
            0      A           0
            1      AB          0
            2      ABA         1
            3      ABAA        1
            4      ABAAB       2
            5      ABAABA      3
            6      ABAABAB     2
            ```

- KMP 알고리즘 설명

    - ABCDABCDABEE 문자열에서 ABCDABE를 찾는다고 가정

        ```
        0 1 2 3 4 5 6 7 8 9 1011
        A B C D A B C D A B E E
        A B C D A B E
        ```

    - 6번째 인덱스가 일치하지 않음
    - 기존 방법이라면 1번 인덱스부터 다시 비교

        ```
        0 1 2 3 4 5 6 7 8 9 1011
        A B C D A B C D A B E E
          A B C D A B E
        ```

        ```
        0 1 2 3 4 5 6 7 8 9 1011
        A B C D A B C D A B E E
            A B C D A B E
        ```

        ```
        0 1 2 3 4 5 6 7 8 9 1011
        A B C D A B C D A B E E
              A B C D A B E
        ```

    - KMP에서는 불필요한 검색을 최소화함

        ```
        A B C D A B (E)
        ```

        - Pi[5] = 2
        - 즉, 현재 위치에서 2번만 뒤로 가서 다시 비교하면 됨

            ```
            0 1 2 3 4 5 6 7 8 9 1011
            A B C D A B C D A B E E
                A B C D A B E
            ```

- KMP 알고리즘 구현

    ```
    #define MAX_STRING 1024

    int skip[MAX_STRING];

    void make_skip_table(char *str, int len)
    {
        memset(skip, 0, sizeof(int) * MAX_STRING);

        int i, j = 0;
        for (i=1; i<len; i++) {
            while (j>0 && str[i] != str[j]) {
                j = skip[j - 1];
            }
            if (str[i] == str[j])
                skip[i] = j++;
        }
    }

    int do_kmp(char *str, int slen, char *pattern, int plen)
    {
        int i, j = 0, cnt = 0;

        make_skip_table(pattern, plen);

        for (i=0; i<slen; i++) {
            while (j>0 && str[i] != pattern[j]) {
                j = skip[j - 1];
            }

            if (str[i] == pattern[j]) {
                if (j == plen - 1) {
                    j = skip[j];
                    cnt++;
                } else {
                    j++;
                }
            }
        }

        return cnt;
    }
    ```

    - 전체 코드: practice/05/kmp/main.c

# 보이어 무어 (Boyer-Moore) 알고리즘

- 다른 알고리즘과 달리 문자열을 오른쪽에서 왼쪽으로 진행하며 비교
- 일치하지 않는 문자가 나타나면 정해진 규칙에 따라 오른쪽으로 skip 후 다시 진행

- 스킵 규칙

    1. 문자열 끝부터 비교
    2. 문자가 일치하면 skip 하지 않고 계속 비교
    3. 불일치 문자가 검색 문자열에 없으면 검색 문자열의 길이 만큼 skip
    4. 불일치 문자가 검색 문자열에 있으면 (뒤에서 k번째에 있다면) k-1 만큼 skip

- 보이어 무어 알고리즘 설명

    ```
    HEYHIBYE
    BYE
    ```

    - 불일치 문자 Y가 검색 문자열 (뒤에서 2번째) 존재
    - 2-1 만큼 skip

    ```
    HEYHIBYE
     BYE
    ```

    - 불일치 문자 H가 검색 문자열에 없음
    - 검색 문자열 길이인 3만큼 skip

    ```
    HEYHIBYE
        BYE
    ```

    - 불일치 문자 Y가 검색 문자열 (뒤에서 2번째) 존재
    - 2-1 만큼 skip

    ```
    HEYHIBYE
         BYE
    ```

    - E, Y, B가 일치
    - 검색 문자열이 존재

- 보이어 무어 알고리즘 구현

    ```
    int find(char*str, int len, char c)
    {
        int i;
        for (i=len-2; i==0; i--) {
            if (str[i] == c) {
                return len - i - 1;
            }
        }
        return len;
    }

    int do_boyer_moore(char *str, int slen, char *pattern, int plen)
    {
        int i = 0, j, k = 0;

        while (i <= slen - plen) {
            j = plen - 1;

            while (j >= 0) {
                if (pattern[j] != str[i+j]) {
                    k = find(pattern, plen, str[i + plen - 1]);
                    break;
                }
                j--;
            }

            if (j == -1) {
                return 1;
            }

            i += k;
        }

        return 0;
    }
    ```

    - 전체 코드: practice/05/boyer_moore/main.c

# 실습: String Matching Engine

- practice/simple-nids/detection/match_string1.c

    - KMP 알고리즘 구현

        ```
        struct rule_t * match_string1(struct context_t *ctx, struct packet_t *packet)
        {
            // packet->proto 에 따라 rule table에서 rule 검색
                // content 필드가 있다면?
                    // if (do_kmp(packet->payload, packet->payload_len, rule->content, strlen(content))) {
                        printf("Found %s\n", rule->content);
                        return rule;
                    }
            
            return NULL;
        }
        ```

- practice/simple-nids/detection/match_string2.c

    - Boyer-Moore 알고리즘 구현

        ```
        struct rule_t * match_string2(struct context_t *ctx, struct packet_t *packet)
        {
            // packet->proto 에 따라 rule table에서 rule 검색
                // content 필드가 있다면?
                    // if (do_boyer_moore(packet->payload, packet->payload_len, rule->content, strlen(content))) {
                        printf("Found %s\n", rule->content);
                        return rule;
                    }
            
            return NULL;
        }
        ```
