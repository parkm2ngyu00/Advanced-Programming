# Simple Host Intrusion Detection System (HIDS)

- 시스템 내부에 대해서 악의적인 동작이나 상태 변화를 탐지하는 시스템

    - 동작 감시

        - 악의적인 사용자가 시스템에서 어떤 일을 하고 어떤 프로그램을 실행하고 어떤 리소스에 접근하는지 여부를 감시

    - 상태 감시

        - 악의적인 사용자가 시스템 내부에 어떤 파일을 추가하고 변조하고 삭제하는지 시스템 변경사항을 감시

    - 참고: 네트워크 침입 탐지 시스템 (NIDS)

        - 네트워크 트래픽을 감시하여 서비스 거부 공격, 포트 스캔, 악성 코드 삽입 등과 같은 악의적인 동작들을 탐지하는 시스템

# Simple HIDS 기능

- 관리자가 감시하고자 하는 디렉토리 위치를 지정하면, 해당 디렉토리 및 서브 디렉토리 내 파일들의 상태 변화를 감시한다.

    - 디렉토리와 파일들에 대한 구조와 각 오브젝트의 속성 (권한, 크기, 변경된 날짜 등)을 저장한다.
    - 오브젝트에 내용이 있다면 특정 형식 (MD5 해시 또는 유사한 해시)의 체크섬도 저장한다.

    - 새로운 파일이 추가되면 해당 오브젝트의 정보를 업데이트한다.
    - 기존 파일 (특히, 실행 파일)이 변경이 탐지되었을 때 체크섬 값을 통해 무결성이 회손되었는지 확인한다.
    - 무결성이 회손되었다면 이에 대한 경고 로그를 생성한다.

    - 외부 클라이언트가 시스템에 연결되어 있다면 로그를 클라이언트로 전달하여 사용자가 실시간으로 로그를 확인할 수 있도록 한다.
    - 외부 클라이언트를 통해서 사용자를 시스템 재시작 없이 새로운 디렉토리 위치를 감시할 수 있다.

# 실습 1: 파일 관리 (File Management)

- All implementation should be under practice/simple-hids.

- Construct a pointer array with the information of sub-directories and files based on the given directory.

    - Input

        - ./simple-hids [file path]

        - Example
            - ./simple-hids /home/vagrant/problems

    - Entry Structure

        ```
        #define MAX_STRING 1024
        ```

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

        - Reference

            - [Left-child right-sibling binary tree](https://en.wikipedia.org/wiki/Left-child_right-sibling_binary_tree)

    - Pointer Array with dynamic memory allocation

        ```
        files
            ㄴ entry (/home/vagrant/problems)
                ㄴ entry (picnic)
                    ㄴ entry (picnic)
                    ㄴ entry (picnic.c)
                    ㄴ entry (README.md)
                ㄴ entry (restore)
                    ㄴ entry (restore)
                    ㄴ entry (restore.c)
                    ㄴ entry (README.md)
                ㄴ entry (lunchbox)
                    ㄴ entry (lunchbox)
                    ㄴ entry (lunchbox.c)
                    ㄴ entry (README.md)
                ㄴ entry (README.md)
        ```

- Print all directories and files like below by travaling the pointer array.

    - Output

        - [entry]/[entry]/[entry]... | [Size] | [Last Access Time] | [Last Modification Time]

        ```
        /home/vagrant/problems/picnic/picnic | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/picnic/picnic.c | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/picnic/README.md | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/restore/restore | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/restore/restore.c | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/restore/README.md | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/lunchbox/lunchbox | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/lunchbox/lunchbox.c | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/lunchbox/README.md | 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        /home/vagrant/problems/README.md 1234 | Thu Nov  3 15:00:00 2022 | Thu Nov  3 15:00:00 2022
        ```
