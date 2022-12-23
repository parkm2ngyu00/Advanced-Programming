# Command-line Interface (CLI)

- 터미널 환경에서 사용자와 프로그램 사이 상호작용을 하기 위한 인터페이스
- 일반 사용자 입장에서는 Graphical User Interface (GUI)를 많이 사용
- 하지만, 개발자나 시스템 운영자들의 경우 터미널 환경에서 CLI를 주로 이용

# CLI vs. Terminal User Interface (TUI)

- 터미널 환경에서 프로그램과의 소통을 위해 대부분 CLI를 사용
- 하지만, CLI 사용을 어려워하는 경우도 많음
- 이 때, CLI 대신 TUI를 사용할 수 있으나 상대적으로 개발이 어려울 수 있음

    ![](https://miro.medium.com/max/1400/1*qWhXCMEpWe1hYIfHDcnI4g.png)

    ![](https://warehouse-camo.ingress.cmh1.psfhosted.org/2b0377ab99b00f73ef67da1a81d51952dbab00d8/68747470733a2f2f6769746875622e636f6d2f616d616e75736b2f732d7475692f626c6f622f6d61737465722f53637265656e53686f74732f732d7475692d312e302e6769663f7261773d74727565)

# CLI vs. Command-line Arguments

- 사용자로 부터 어떠한 입력을 받기 위해서 CLI를 제공할 수도 있지만, 때때로 명령행인자를 통해 CLI를 대체하기도 함
- 동일한 바이너리를 가지고 서비스를 돌릴 수도 있고, 또는 해당 서비스에 특정 명령을 전달할 수도 있음

    ```
    ./program # 프로그램 실행
    ./program list /home/vagrant # 특정 명령 실행
    ./program get /home/vagrant/.bashrc # 특정 명령 실행
    ```

- 명령행 인자를 통해 프로그램을 제어하기 위해서 내부적으로 소켓 기반의 통신을 주로 사용함

    - 프로그램 내 CLI 기능을 내포되어 있는 형태로 구현은 하지만, 실제로 두 개의 프로그램을 동작하는 형태
    - 분리할 수도 있지만 편의상 하나에 구현한 것임

# Libcli - CLI Library

- Libcli는 Cisco-like CLI 구현을 위한 C 라이브러리
- 기본적으로 텔넷 인터페이스를 사용하여 접근
- 명령 처리 뿐만 아니라 인증, 자동 완성, 히스토리 등의 간단한 기능 제공

## Libcli 설치

- 코드 컴파일

    ```
    make
    ```

    - 컴파일을 하게 되면 libcli.so 라는 공유 라이브러리 파일 생성

- 라이브러리 설치

    ```
    make install
    ```

    - 설치하게 되면 libcli.so 파일을 /usr/local/lib 폴더에 복사

## 주요 라이브러리 사용법

- Libcli 라이브러리를 사용하기 위해서 헤더 추가

    ```
    #include <libcli.h>
    ```

- Libcli를 코드에 포함하였다면 컴파일 시 해당 라이브러리 추가

    ```
    $ gcc -o main main.c -lcli
    ```

- 주요 함수들은 다음과 같음

    ```
    cli = cli_init(); // 초기화

    cli_telnet_protocol(cli, 1); // 텔넷 기반 프로토콜 활성화
    cli_set_banner(cli, "Welcome Message!"); // 접속시 출력할 메시지
    cli_set_hostname(cli, "command"); // prompt 형태

    cli_regular(cli, regular_callback);
    cli_regular_interval(cli, 5); // cli timeout (seconds)
    cli_set_idle_timeout_callback(cli, 300, idle_timeout); // cli idle timeout (seconds)

    // 기본 인증 후 사용할 수 있는 명령어

    // > test1
    // > test2

    cli_register_command(cli, NULL, "test1", cmd_test1, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test1");
    cli_register_command(cli, NULL, "test2", cmd_test2, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test2");

    // > get test3
    // > get test4

    c = cli_register_command(cli, NULL, "get", NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL);
    cli_register_command(cli, c, "test3", cmd_test3, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test3 with get");
    cli_register_command(cli, c, "test4", cmd_test4, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test4 with get");

    // 추가 인증 후 사용할 수 있는 명령어

    // # set test5
    // # set test6

    c = cli_register_command(cli, NULL, "set", NULL, PRIVILEGE_PRIVILEGED, MODE_EXEC, NULL);
    cli_register_command(cli, c, "test5", cmd_test5, PRIVILEGE_PRIVILEGED, MODE_EXEC, "call test5 with set");
    cli_register_command(cli, c, "test6", cmd_test6, PRIVILEGE_PRIVILEGED, MODE_EXEC, "call test6 with set");

    cli_set_auth_callback(cli, check_auth);
    cli_set_enable_callback(cli, check_enable);
    ```

    - 세부 구현은 [샘플 프로그램](../../practice/11/simple_cli/main.c) 참조

- CLI로 메시지 출력

    ```
    char message[1024];
    sprintf(message, "helloworld");
    cli_print(message);
    ```

# 실습 5: CLI 구현

- All implementation should be under practice/simple-hids.

- Implement the commands to get all file and directory structures and the details of a file.

    - If we give the directory '/home/vagrant' as an argument

        - Normal mode

            ```
            > list /home/vagrant // print all files and directories
            > list /home/vagrant/problems // print all files and directories under the given directory
            ```

        - Privilieged mode

            ```
            # get /home/vagrant/problems/README.md // print the details of a specific file
            ```

    - practice/simple-hids/main.c
