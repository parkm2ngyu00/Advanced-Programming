# 다차원 배열

- 구조화된 데이터를 프로그램에서 관리/사용할 때 가장 많이 쓰는 방법이 배열임
- 보통 1차원 배열과 2차원 배열까지 많이 사용되지만, 간혹 3차원 배열을 쓰는 경우도 있음
- 3차원 이상으로 넘어갈 경우 데이터 관리 자체가 어렵기 때문에 다른 형태의 자료구조를 활용하는 것이 좋음

# 다차원 배열 동적할당

- 1차원 배열 동적할당

    - n 개의 아이템을 가진 배열

        ```
        int *p = (int *)malloc(sizeof(int) * n);
        ```

    - 메모리 반환

        ```
        free(p);
        ```

    - 예시: practice/05/1d_array/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            int n = 10;

            int *p = (int *)malloc(sizeof(int) * n);

            int i;
            for (i=0; i<n; i++) {
                printf("%d: %d\n", i, p[i]);
            }

            free(p);

            return 0;
        }
        ```

- 2차원 배열 동적할당

    - n (행) X m (열) 배열

        ```
        int **p = (int **)malloc(sizeof(int *) * n);

        int i;
        for (i=0; i<n; i++) {
            p[i] = (int *)malloc(sizeof(int) * m);
        }
        ```

    - 메모리 반환

        ```
        int i;
        for (i=0; i<n; i++) {
            free(p[i]);
        }

        free(p);
        ```

    - 예시: practice/05/2d_array/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            int n = 2, m = 5;

            int **p = (int **)malloc(sizeof(int *) * n);

            int i;
            for (i=0; i<n; i++) {
                p[i] = (int *)malloc(sizeof(int) * m);
            }

            for (i=0; i<n; i++) {
                int j;
                for (j=0; j<m; j++) {
                    printf("%d, %d: %d\n", i, j, p[i][j]);
                }
            }

            for (i=0; i<n; i++) {
                free(p[i]);
            }

            free(p);

            return 0;
        }
        ```

- 3차원 배열 동적할당

    - x * y * z 배열

        ```
        int ***p = (int ***)malloc(sizeof(int **) * x);

        int i;
        for (i=0; i<x; i++) {
            p[i] = (int **)malloc(sizeof(int *) * y);

            int j;
            for (j=0; j<y; j++) {
                p[i][j] = (int *)malloc(sizeof(int) * z);
            }
        }
    
    - 메모리 반환

        ```
        int i, j;
        for (i=0; i<x; i++) {
            for (j=0; j<y; j++) {
                free(p[i][j]);
            }

            free(p[i]);
        }

        free(p);
        ```

    - 예시: practice/05/3d_array/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            int x = 3, y = 4, z = 5;

            int ***p = (int ***)malloc(sizeof(int **) * x);

            int i;
            for (i=0; i<x; i++) {
                p[i] = (int **)malloc(sizeof(int *) * y);

                int j;
                for (j=0; j<y; j++) {
                    p[i][j] = (int *)malloc(sizeof(int) * z);
                }
            }

            for (i=0; i<x; i++) {
                int j;
                for (j=0; j<y; j++) {
                    int k;
                    for (k=0; k<z; k++) {
                        printf("%d, %d, %d: %d\n", i, j, k, p[i][j][k]);
                    }
                }
            }

            for (i=0; i<x; i++) {
                int j;
                for (j=0; j<y; j++) {
                    free(p[i][j]);
                }

                free(p[i]);
            }

            free(p);

            return 0;
        }
        ```

# 다차원 포인터 배열 동적할당

- 1차원 포인터 배열 동적할당

    - n 개의 포인터를 가진 배열

        ```
        int **p = (int **)malloc(sizeof(int *) * n);

        int i;
        for (i=0; i<n; i++) {
            p[i] = (int *)malloc(sizeof(int));
        }
        ```

    - 메모리 반환

        ```
        int i;
        for (i=0; i<n; i++) {
            free(p[i]);
        }

        free(p);
        ```

    - 예시: practice/05/1d_pointer_array/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            int n = 10;

            int **p = (int **)malloc(sizeof(int *) * n);

            int i;
            for (i=0; i<n; i++) {
                p[i] = (int *)malloc(sizeof(int));
            }

            for (i=0; i<n; i++) {
                printf("%d: %p, %d\n", i, p[i], *p[i]);
            }

            for (i=0; i<n; i++) {
                free(p[i]);
            }

            free(p);

            return 0;
        }
        ```

- 2차원 포인터 배열 동적할당

    - n (행) X m (열) 포인터 배열

        ```
        int ***p = (int ***)malloc(sizeof(int **) * n);

        int i;
        for (i=0; i<n; i++) {
            p[i] = (int **)malloc(sizeof(int *) * m);

            int j;
            for (j=0; j<m; j++) {
                p[i][j] = (int *)malloc(sizeof(int));
            }
        }
        ```

    - 메모리 반환

        ```
        int i, j;
        for (i=0; i<n; i++) {
            for (j=0; j<m; j++) {
                free(p[i][j]);
            }

            free(p[i]);
        }

        free(p);
        ```

    - 예시: practice/05/2d_pointer_array/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        int main()
        {
            int n = 5, m = 3;

            int ***p = (int ***)malloc(sizeof(int **) * n);

            int i;
            for (i=0; i<n; i++) {
                p[i] = (int **)malloc(sizeof(int *) * m);

                int j;
                for (j=0; j<m; j++) {
                    p[i][j] = (int *)malloc(sizeof(int));
                }
            }

            for (i=0; i<n; i++) {
                int j;
                for (j=0; j<m; j++) {
                    printf("%d, %d: %p, %d\n", i, j, p[i][j], *p[i][j]);
                }
            }

            for (i=0; i<n; i++) {
                int j;
                for (j=0; j<m; j++) {
                    free(p[i][j]);
                }

                free(p[i]);
            }

            free(p);

            return 0;
        }
        ```

# 다차원 포인터 배열 동적할당 with 구조체

- 1차원 포인터 배열 동적할당

    - 구조체 정의

        ```
        struct sample_t {
            int value;
        };
        ```

    - n 개의 포인터를 가진 배열

        ```
        struct sample_t **p = (struct sample_t **)malloc(sizeof(struct sample_t *) * n);

        int i;
        for (i=0; i<n; i++) {
            p[i] = (struct sample_t *)malloc(sizeof(struct sample_t));
        }
        ```

    - 메모리 반환

        ```
        int i;
        for (i=0; i<n; i++) {
            free(p[i]);
        }

        free(p);
        ```

    - 예시: practice/05/1d_pointer_array_w_struct/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        struct sample_t {
            int value;
        };

        int main()
        {
            int n = 10;

            struct sample_t **p = (struct sample_t **)malloc(sizeof(struct sample_t *) * n);

            int i;
            for (i=0; i<n; i++) {
                p[i] = (struct sample_t *)malloc(sizeof(struct sample_t));
            }

            for (i=0; i<n; i++) {
                printf("%d: %p, %d\n", i, p[i], p[i]->value);
            }

            for (i=0; i<n; i++) {
                free(p[i]);
            }

            free(p);

            return 0;
        }
        ```

# 다차원 포인터 배열 동적할당 with 구조체 + 연결 리스트


- 1차원 포인터 배열 동적할당

    - 구조체 정의

        ```
        struct sample_t {
            int value;
            struct sample_t *next;
        };
        ```

    - n 개의 포인터를 가진 배열 내 연결 리스트 구현

        ```
        struct sample_t **p = (struct sample_t **)malloc(sizeof(struct sample_t *) * n);

        int i;
        for (i=0; i<n; i++) {
            p[i] = (struct sample_t *)malloc(sizeof(struct sample_t));

            // just in case
            p[i]->next = NULL;

            int j;
            for (j=0; j<m; j++) {
                struct sample_t *sample = (struct sample_t *)malloc(sizeof(struct sample_t));
                sample->next = p[i];
                p[i] = sample;
            }
        }
        ```

    - 메모리 반환

        ```
        int i;
        for (i=0; i<n; i++) {
            struct sample_t *sample = p[i];

            while (sample != NULL) {
                struct sample_t *temp = sample;
                sample = sample->next;
                free(temp);
            }

            // No free(p[i]) because of double free!
        }

        free(p);
        ```

    - 예시: practice/05/1d_pointer_array_w_struct_n_linked/main.c

        ```
        #include <stdio.h>
        #include <stdlib.h>

        struct sample_t {
            int value;
            struct sample_t *next;
        };

        int main()
        {
            int n = 10, m = 5;

            struct sample_t **p = (struct sample_t **)malloc(sizeof(struct sample_t *) * n);

            int i;
            for (i=0; i<n; i++) {
                p[i] = (struct sample_t *)malloc(sizeof(struct sample_t));

                // just in case
                p[i]->next = NULL;

                int j;
                for (j=0; j<m; j++) {
                    struct sample_t *sample = (struct sample_t *)malloc(sizeof(struct sample_t));
                    sample->next = p[i];
                    p[i] = sample;
                }
            }

            for (i=0; i<n; i++) {
                struct sample_t *sample = p[i];
                while (sample != NULL) {
                    printf("%d: %p, %d\n", i, sample, sample->value);
                    sample = sample->next;
                }
            }

            for (i=0; i<n; i++) {
                struct sample_t *sample = p[i];

                while (sample != NULL) {
                    struct sample_t *temp = sample;
                    sample = sample->next;
                    free(temp);
                }
            }

            free(p);

            return 0;
        }
        ```

# 실습: Rule Table 관리

- practice/simple-nids/main/context.h

    - struct context_t 안에 rule table을 만들기 위한 변수가 정의되어 있음

        ```
        struct context_t {
        ...

        // rule table
        struct rule_t **rule_table;

        ...
        };
        ```

- practice/simple-nids/rule/rule_mgmt.c

    - 초기화

        ```
        int initialize_rule_table(struct context_t *ctx)
        {
            // rule spec 상 protocol 관련하여
            // IPv4 (0), TCP (1), UDP (2), ICMP (3), HTTP (4) 이렇게 5가지 종류의 rule이 있음
            // load_rules()에서 각각의 rule들을 파싱한 후 프로토콜 별 Linked List 형태로 rule을 관리하고자 함
            // 예를 들어, rule_table[1]에는 TCP와 관련된 rule들이 Linked List 형태로 관리

            // 참고로 practice/simple-nids/main/include/common.h 내 필요한 정보가 정의되어 있음
            // #define IP_RULES     0
            // #define TCP_RULES    1
            // #define UDP_RULES    2
            // #define ICMP_RULES   3
            // #define HTTP_RULES   4
            // #define NUM_OF_PROTO 5

            // 'struct rule_t *' 타입의 1차원 포인터 배열 생성
            // ctx->rule_table = ... n = NUM_OF_PROTO

            // ctx->rule_table[0] ~ [4]까지 돌며 NULL로 초기화

            return 0;
        }
        ```

    - 메모리 반환

        ```
        int destroy_rule_table(struct context_t *ctx)
        {
            // ctx->rule_table[0] ~ [4]까지 돌며
            // 각각에 존재하는 모든 룰들에 대해서 linked list를 따라가며 메모리 반환

            return 0;
        }
        ```
    
    - Rule Table 업데이트

        ```
        int load_rules(struct context_t *ctx)
        {
            int cnt = 1;
            char buf[MAX_STRING] = {0};

                    ...

                } else if ((rule->proto &= PROTO_HTTP) && (strcmp(ptr, "method") == 0)) {
                    ptr = strtok(NULL, ":");
                    strcpy(rule->method, ptr);
                }
            }

            // free(rule) 부분은 이제 제거하고, 프로토콜에 따라 rule table에 rule 추가

            free(rule);
        }

        fclose(fp);

        // rule table 전체를 돌며 저장된 rule을 print_rule(rule) 함수를 이용하여 출력

        printf("%d rules are loaded\n", cnt);
        ```
