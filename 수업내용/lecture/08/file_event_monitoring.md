# inotify

- 리눅스 파일 시스템에서 발생되는 다양한 이벤트들을 모니터링하기 위한 API 제공
- 보안, 성능 등 다양한 목적으로 사용자 공간을 모니터링할 수 있음

# inotify API

- int inotify_init(void);

    - 이 함수는 inotify 인스턴스를 작성하고 이 인스턴스가 참조하는 파일 디스크립터를 리턴하는 시스템 호출

- int inotify_add_watch(int fd, const char *pathname, uint32_t mask);

    - 이 함수는 파일이나 디렉토리에 감시를 추가하며 감시할 이벤트를 지정함
    - 기존 감시에 이벤트를 추가해야 하는지, 경로에 디렉토리가 표시되는 경우에만 감시를 수행할 것인지, 심볼릭 링크를 수행해야 하는지, 그리고 감시가 첫 번째 이벤트가 발생하면 중지되어야 하는 일회성 감시인지 등을 플래그를 통해 제어할 수 있음

- int inotify_rm_watch(int fd, int wd);

    - 이 함수는 감시 목록에서 감시 항목을 제거함

- ssize_t read(int fd, void *buf, size_t count);

    - 이 함수는 하나 이상의 이벤트에 관한 정보가 포함된 버퍼를 읽음

- int close(int fd);

    - 이 함수는 파일 디스크립터를 닫고 파일 디스크립터에 남아 있는 모든 감시를 제거함

# inotify를 이용한 모니터링 절차

1. intofiy_init을 사용하여 파일 디스크립터를 연다
2. 하나 이상의 감시를 추가한다
3. 이벤트를 대기한다
4. 이벤트를 처리한 후 대기 상태로 돌아간다
5. 더 이상 활성화된 감시가 없거나 어떤 신호를 수신하는 경우 파일 디스크립터를 닫고 정리한 후 종료한다

# inotify 이벤트

- inotify_event 구조

    ```
    struct inotify_event {
        int wd; /* Watch descriptor. */
        uint32_t mask; /* Watch mask. */
        uint32_t cookie; /* Cookie to synchronize two events. */
        uint32_t len; /* Length (including NULs) of name. */
        char name __flexarr; /* Name. */
    };
    ```

- 감시할 수 있는 이벤트

    - IN_ACCESS
        - 감시 디렉토리에 있는 감시 항목이 액세스됨
        - 예를 들면, 열린 파일이 읽힌 경우

    - IN_ATTRIB
        - 감시 디렉토리에 있는 감시 항목에서 메타데이터가 변경됨
        - 예를 들면, 시간소인이나 사용 권한이 변경된 경우

    - IN_MODIFY
        - 감시 디렉토리에 있는 감시 항목이 수정됨
        - 예를 들면, 열린 파일이 업데이트된 경우

    - IN_OPEN
        - 파일이나 디렉토리가 열렸음

    - IN_CLOSE_WRITE
        - 쓰기 위해 연 파일이나 디렉토리가 닫혔음

    - IN_CLOSE_NOWRITE
        - 읽기 전용으로 연 파일이나 디렉토리가 닫혔음

    - IN_CLOSE
        - IN_CLOSE_WRITE | IN_CLOSE_NOWRITE

    - IN_MOVED_FROM
        - 감시 디렉토리에 있는 감시 항목이 감시 위치에서 이동되었음
        - 또한, 이 이벤트에는 쿠키가 포함되어 있으며 사용자는 이 쿠키를 이용하여 IN_MOVED_FROM와 IN_MOVED_TO의 연관성을 확인할 수 있음

    - IN_MOVED_TO
        - 파일이나 디렉토리가 감시 위치에서 이동되었음
        - 이 이벤트에는 IN_MOVED_FROM과의 연관성을 확인할 수 있는 쿠키가 포함되어 있음
        - 파일이나 디렉토리의 이름이 변경되면 두 가지 이벤트가 모두 표시됨
        - 파일이나 디렉토리가 감시하고 있지 않은 위치로 이동하거나 이 위치에서 이동되는 경우에는 한 가지 이벤트만 표시됨
        - 사용자가 감시 항목을 이동하거나 이름을 변경하는 경우에도 감시는 계속됨

    - IN_MOVE
        - IN_MOVED_FROM | IN_MOVED_TO

    - IN_MOVE_SELF
        - 감시 항목 자체가 이동되었음

    - IN_CREATE
        - 서브디렉토리나 파일이 감시 디렉토리에서 작성되었음

    - IN_DELETE
        - 서브디렉토리나 파일이 감시 디렉토리에서 삭제되었음

    - IN_DELETE_SELF
        - 감시 항목 자체가 삭제되었음
        - 감시가 종료되고 IN_IGNORED 이벤트를 수신하게 됨

    - IN_ALL_EVENTS
        - 모든 이벤트를 포함함

    - IN_DONT_FOLLOW
        - 심볼릭 링크에 대해서 역참조하지 않음

# inotify를 이용한 예제

- practice/08/inotify 밑에 main.c 파일을 만들고 아래의 내용을 작성

    ```
    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <unistd.h>
    #include <sys/inotify.h>

    static void __handle_inotify_event(const struct inotify_event *event)
    {
        if (event->mask & IN_ACCESS)
            printf("IN_ACCESS ");
        if (event->mask & IN_ATTRIB)
            printf("IN_ATTRIB ");
        if (event->mask & IN_MODIFY)
            printf("IN_MODIFY ");
        if (event->mask & IN_OPEN)
            printf("IN_OPEN ");
        if (event->mask & IN_CLOSE_WRITE)
            printf("IN_CLOSE_WRITE ");
        if (event->mask & IN_CLOSE_NOWRITE)
            printf("IN_CLOSE_NOWRITE ");
        if (event->mask & IN_CREATE)
            printf("IN_CREATE ");
        if (event->mask & IN_DELETE)
            printf("IN_DELETE ");
        if (event->mask & IN_MOVED_FROM)
            printf("IN_MOVED_FROM ");
        if (event->mask & IN_MOVED_TO)
            printf("IN_MOVED_TO ");
        if (event->mask & IN_MOVE_SELF)
            printf("IN_MOVE_SELF ");
        if (event->mask & IN_ISDIR)
            printf("IN_ISDIR ");
        if (event->len > 0)
            printf(": name = %s\n", event->name);
    }

    int main(int argc, char *argv[])
    {
        char buf[4096] __attribute__ ((aligned(__alignof__(struct inotify_event))));
        const struct inotify_event *event;

        int fd = inotify_init();
        if (fd < 0) {
            printf("Failed to initialize inotify\n");
            return -1;
        }

        int wd = inotify_add_watch(fd, argv[1], IN_MODIFY | IN_CREATE | IN_DELETE);
        if (wd < 0) {
            printf("Failed to add watch %s", argv[1]);
            return -1;
        }

        while (1) {
            ssize_t size = read(fd, buf, sizeof(buf));
            if (size == -1 && errno != EAGAIN) {
                printf("Failed to read an event\n");
                return -1;
            } else if (size <= 0) {
                break;
            }

            char *ptr;
            for (ptr = buf; ptr < buf + size; ptr += sizeof(struct inotify_event) + event->len) {
                event = (struct inotify_event *)ptr;
                __handle_inotify_event(event);
            }
        }

        int ret = inotify_rm_watch(fd, wd);
        if (ret < 0) {
            printf("Failed to remove watch (fd: %d) (wd: %d)", fd, wd);
            return -1;
        }

        return 0;
    }
    ```

- 코드 컴파일 후 실행

    ```
    gcc -o main main.c
    ./main [directory to monitor]
    ```

# 실습 3: 파일 추가/변경/삭제 모니터링 (File Event Monitoring)

- All implementation should be under practice/simple-hids.

- Implement the functions to monitor the changes in given directories and files.

    - practice/simple-hids/watch.{c, h}

- Update the entry information when receiving events.

    - Print the change of the entry information.
    - If the content is changed, update the MD5 hash as well.

- Add a signal handler.

    - When entering Ctrl + C, stop monitoring events.
