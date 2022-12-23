# 패킷 캡쳐

- 컴퓨터에서 패킷을 전송하면 네트워크를 통해 라우팅과 포워딩이라는 단계를 거쳐 대상 컴퓨터의 네트워크 인터페이스로 패킷이 전달됨
- 패킷 캡쳐는 이처럼 네트워크를 통해 패킷들이 전달되는 도중 패킷의 내용을 확인하는 것을 의미함
- 주로 네트워크의 상태를 파악하기 위한 통계 수집, 보안을 목적으로 한 패킷 검사, 또는 네트워크를 디버깅하기 위해 많이 사용됨

# Libpcap

- 패킷 캡쳐를 용이하게 해주는 대표적인 패킷 캡쳐 라이브러리
- BPF (Berkeley Packet Filter)를 통해 캡쳐 할 패킷을 필터링 할 수 있는 기능 지원
- 사용자 레벨 라이브러리이기 때문에, 성능적인 오버헤드는 피할 수 없음

# Tcpdump

- Libpcap 라이브러리를 기반으로 개발된 대표적인 패킷 캡쳐 프로그램

    ```
    tcpdump [options] [filter]
    ```

- 우분투 환경에서 tcpdump 설치

    ```
    sudo apt-get -y install tcpdump
    ```

- 필터 예제

    ```
    tcpdump -i eth0
    tcpdump -i eth0 -c 10
    tcpdump -i eth0 tcp port 80
    tcpdump -i eth0 src 10.0.10.10
    tcpdump -i eth0 dst 10.0.20.10
    tcpdump -i eth0 src 10.0.10.10 and tcp port 80
    tcpdump -i eth0 dst 10.0.20.10 and dst port '(80 or 8080)'
    ```

- 패킷 캡쳐 후 파일 I/O

    - 실습을 위해 practice/03/tcpdump 디렉토리를 만들고 이동

        ```
        mkdir -p practice/03/tcpdump
        cd practice/03/tcpdump
        ```

    - 패킷 캡쳐 후 파일로 저장

        ```
        tcpdump -w capture.pcap
        ```

    - 다양한 네트워크 트래픽 생성

        ```
        curl dankook.ac.kr # TCP
        nslookup yahoo.com # UDP
        ping google.com    # ICMP
        ```

    - 저장한 파일 불러오기

        ```
        tcpdump -r capture.pcap
        ```

- 네트워크를 다룬다면 tcpdump는 정말 많이 쓰이는 툴이므로 알아두면 좋음

# Wireshark

- Lippcap 기반의 또 다른 패킷 캡쳐 프로그램

    - tcpdump는 주로 터미널 환경에서 많이 사용되고, Wireshark는 GUI 환경에서 많이 사용함
    - 기본적인 내용은 tcpdump와 동일하나 UI가 있다 보니 패킷을 분석하는데 유용

- Wireshark 다운로드 및 설치

    - [https://www.wireshark.org/download.html](https://www.wireshark.org/download.html)

- Wireshark를 통해서 캡쳐한 파일 확인

    - 앞서 tcpdump를 통해서 패킷 캡쳐 후 저장한 파일을 열기
    - 패킷들을 클릭하며 세부 정보 확인하기

# Libpcap을 통한 패킷 캡쳐

- 모든 네트워크 인테페이스 이름 확인

    - practice/03/pcap-test 밑에 pcap_dev.c 파일을 만들고 아래의 내용을 작성

        ```
        #include <stdio.h>
        #include <pcap.h>

        int main()
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // == START == //

            pcap_if_t *devices, *temp;

            if (pcap_findalldevs(&devices, ebuf) == -1) {
                printf("[ERROR] failed to find devices: %s\n", ebuf);
                return -1;
            }

            int num = 0;

            for (temp=devices; temp; temp=temp->next) {
                printf("%d: %s\n", num++, temp->name);
            }

            // == END == //

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_dev pcap_dev.c -lpcap
        ./pcap_dev
        ```

    - 실행 결과

        ```
        0: ens160
        1: lo
        2: any
        3: bluetooth-monitor
        4: nflog
        5: nfqueue
        ```

- 네트워크 인터페이스에 할당된 네트워크 주소와 네트워크 서브넷 마스크 확인

    - practice/03/pcap-test 밑에 pcap_ip_mask.c 파일을 아래와 같이 수정

        ```
        #include <stdio.h>
        #include <pcap.h>

        int main(int argc, char *argv[])
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // == START == //

            bpf_u_int32 ip, mask;
            struct in_addr net_addr, mask_addr;

            if (pcap_lookupnet(argv[1], &ip, &mask, ebuf) < 0)
            {
                printf("[ERROR] %s\n", ebuf);
            }

            net_addr.s_addr = ip;
            mask_addr.s_addr = mask;

            printf("IP: %s\n", inet_ntoa(net_addr));
            printf("Mask: %s\n", inet_ntoa(mask_addr));

            // == END == //

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_ip_mask pcap_ip_mask.c -lpcap
        ./pcap_ip_mask [interface / e.g., ens160 or enp0s3]
        ```

    - 실행 결과

        ```
        IP: 10.0.10.0
        Mask: 255.255.255.0
        ```

- N개의 패킷 캡쳐 (방법 1)

    - practice/03/pcap-test 밑에 pcap_sniff_1.c 파일을 아래와 같이 수정

        ```
        #include <stdio.h>
        #include <pcap.h>

        #define DATA_SIZE 4096

        void packet_dump(const u_char *pkt, int len)
        {
            int i;

            for (i=0; i<len; i++) {
                printf("%02x ", *pkt);
                pkt++;

                if (i % 16 == 15) {
                    printf("\n");
                }
            }

            printf("\n");
        }

        int main(int argc, char *argv[])
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // == START == //

            pcap_t *handle;

            handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
            if (handle == NULL) {
                printf("[ERROR] %s\n", ebuf);
                return -1;
            }

            int i;
            const u_char *pkt;
            struct pcap_pkthdr header;

            for (i=0; i<10; i++) {
                pkt = pcap_next(handle, &header);
                packet_dump(pkt, header.len);
            }

            pcap_close(handle);

            // == END == //

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_sniff_1 pcap_sniff_1.c -lpcap
        sudo ./pcap_sniff_1 [interface / e.g., ens160 or enp0s3]
        ```

- N개의 패킷 캡쳐 (방법 2)

    - practice/03/pcap-test 밑에 pcap_sniff_2.c 파일을 아래와 같이 수정

        ```
        #include <stdio.h>
        #include <pcap.h>

        #define DATA_SIZE 4096

        void packet_dump(const u_char *pkt, int len)
        {
            int i;

            for (i=0; i<len; i++) {
                printf("%02x ", *pkt);
                pkt++;

                if (i % 16 == 15) {
                    printf("\n");
                }
            }

            printf("\n");
        }

        void callback_func(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
        {
            packet_dump(pkt, header->len);
        }

        int main(int argc, char *argv[])
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // == START == //

            pcap_t *handle;

            handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
            if (handle == NULL) {
                printf("[ERROR] %s\n", ebuf);
                return -1;
            }

            pcap_loop(handle, 10, callback_func, 0);

            pcap_close(handle);

            // == END == //

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_sniff_2 pcap_sniff_2.c -lpcap
        sudo ./pcap_sniff_2 [interface / e.g., ens160 or enp0s3]
        ```

- 패킷 필터 적용

    - practice/03/pcap-test 밑에 pcap_filter.c 파일을 아래와 같이 수정

        ```
        #include <stdio.h>
        #include <string.h>
        #include <pcap.h>

        #define DATA_SIZE 4096
        #define FILTER_SIZE 1024

        void packet_dump(const u_char *pkt, int len)
        {
            int i;

            for (i=0; i<len; i++) {
                printf("%02x ", *pkt);
                pkt++;

                if (i % 16 == 15) {
                    printf("\n");
                }
            }

            printf("\n");
        }

        void callback_func(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
        {
            packet_dump(pkt, header->len);
        }

        int main(int argc, char *argv[])
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            pcap_t *handle;

            handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
            if (handle == NULL) {
                printf("[ERROR] %s\n", ebuf);
                return -1;
            }

            // == START == //

            char filter[FILTER_SIZE] = "";
            struct bpf_program filter_code;

            int i;
            for (i=2; i<argc; i++) {
                sprintf(filter+strlen(filter), " %s", argv[i]);
            }

            if (pcap_compile(handle, &filter_code, filter, 0, 0) < 0) {
                printf("[ERROR] Failed to compile filter\n");
                return -1;
            }

            if (pcap_setfilter(handle, &filter_code) < 0) {
                printf("[ERROR] Failed to set filter\n");
                return -1;
            }

            // == END == //

            pcap_loop(handle, 10, callback_func, 0);

            pcap_close(handle);

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_filter pcap_filter.c -lpcap
        sudo ./pcap_filter [interface / e.g., ens160 or enp0s3] tcp port 22
        ```

- 파일로 패킷 덤프

    - practice/03/pcap-test 밑에 pcap_dump.c 파일을 아래와 같이 수정

        ```
        #include <stdio.h>
        #include <pcap.h>

        #define DATA_SIZE 4096

        void packet_dump(const u_char *pkt, int len)
        {
            int i;

            for (i=0; i<len; i++) {
                printf("%02x ", *pkt);
                pkt++;

                if (i % 16 == 15) {
                    printf("\n");
                }
            }

            printf("\n");
        }

        void callback_func(u_char *dumpfile, const struct pcap_pkthdr *header, const u_char *pkt)
        {
            // stdout
            packet_dump(pkt, header->len);

            // packet dump
            pcap_dump(dumpfile, header, pkt);
        }

        int main(int argc, char *argv[])
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            pcap_t *handle;

            handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
            if (handle == NULL) {
                printf("[ERROR] %s\n", ebuf);
                return -1;
            }

            // == START == //

            pcap_dumper_t *df;

            df = pcap_dump_open(handle, argv[2]);
            if (df == NULL) {
                printf("[ERROR] Failed to dump\n");
                return -1;
            }

            // == END == //

            pcap_loop(handle, 100, callback_func, (u_char *)df);

            pcap_close(handle);

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_dump pcap_dump.c -lpcap
        sudo ./pcap_dump [interface / e.g., ens160 or enp0s3] capture.pcap
        ```


- 덤프 파일 읽기

    - practice/03/pcap-test 밑에 pcap_offline.c 파일을 아래와 같이 수정

        ```
        #include <stdio.h>
        #include <pcap.h>

        void packet_dump(const u_char *pkt, int len)
        {
            int i;

            for (i=0; i<len; i++) {
                printf("%02x ", *pkt);
                pkt++;

                if (i % 16 == 15) {
                    printf("\n");
                }
            }

            printf("\n");
        }

        void callback_func(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
        {
            packet_dump(pkt, header->len);
        }

        int main(int argc, char *argv[])
        {
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // == START == //

            pcap_t *handle;

            // handle = pcap_open_live(argv[1], DATA_SIZE, 1, 0, ebuf);
            // if (handle == NULL) {
            //    ...
            // }

            handle = pcap_open_offline(argv[1], ebuf);
            if (handle == NULL) {
                printf("[ERROR] %s\n", ebuf);
                return -1;
            }

            // == END == //

            pcap_loop(handle, 10, callback_func, 0);

            pcap_close(handle);

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o pcap_offline pcap_offline.c -lpcap
        ./pcap_offline capture.pcap
        ```

# 실습: Packet Capture Engine

- 인터페이스 기반 패킷 캡쳐 엔진

    - 실습 파일: practice/simple-nids/reception/pkt_live.c

        - -i 옵션을 통해 인터페이스 이름을 받은 경우 해당 인터페이스를 통해서 패킷 캡쳐
        - -i 옵션이 없다면 인터페이스 목록 중 첫 번째 인터페이스를 통해서 패킷 캡쳐

        ```
        // context
        struct context_t *local_ctx;

        // pcap handler
        pcap_t *handler;

        // function to destroy pcap handler
        int pkt_live_destroy()
        {
            // break the pcap loop
            pcap_breakloop(handler);

            // release the handler
            pcap_close(handler);

            return 0;
        }

        // function to process each packet
        void packet_live_callback(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
        {
            // 메모리 풀에서 'struct raw_packet_t' 타입의 item 얻기
            struct raw_packet_t *raw;

            // 패킷 길이를 raw->len에 저장

            // 패킷 길이만큼 memcpy()를 통해 pkt 내용을 raw->pkt에 복사

            // 사용한 raw를 메모리 풀에 반환
        }

        // function to capture live-stream packets
        int pkt_live(struct context_t *ctx)
        {
            // copy the pointer of ctx to use in the callback
            local_ctx = ctx;

            // error message
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // 전체 네트워크 인터페이스 확인

            // 만약에 source가 정의되어 있지 않을 경우, 첫번째 인터페이스를 기본값으로 사용

            // pcap_open_live() 함수를 통해 핸들러 생성

            // pcap_loop() 함수를 통해 패킷 캡쳐

            return 0;
        }
        ```

- 파일 기반 패킷 캡쳐 엔진

    - 실습 파일: practice/simple-nids/reception/pkt_file.c

        - -f 옵션을 통해 pcap 파일을 받은 경우 해당 파일로 부터 패킷 읽음

        ```
        // context
        struct context_t *local_ctx;

        // pcap handler
        pcap_t *handler;

        // function to destroy pcap handler
        int pkt_file_destroy()
        {
            // break the pcap loop
            pcap_breakloop(handler);

            // release the handler
            pcap_close(handler);

            return 0;
        }

        // function to process each packet
        void packet_file_callback(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt)
        {
            // 메모리 풀에서 'struct raw_packet_t' 타입의 item 얻기
            struct raw_packet_t *raw;

            // 패킷 길이를 raw->len에 저장

            // 패킷 길이만큼 memcpy()를 통해 pkt 내용을 raw->pkt에 복사

            // 사용한 raw를 메모리 풀에 반환
        }

        // function to read pcap file
        int pkt_file(struct context_t *ctx)
        {
            // copy the pointer of ctx to use in the callback
            local_ctx = ctx;

            // error message
            char ebuf[PCAP_ERRBUF_SIZE] = {0};

            // pcap_open_offline() 함수를 통해 ctx->source로 부터 패킷을 읽는 핸들러 생성

            // pcap_loop() 함수를 통해 패킷 캡쳐

            return 0;
        }
        ```
