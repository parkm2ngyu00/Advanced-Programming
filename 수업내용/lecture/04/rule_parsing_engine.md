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
