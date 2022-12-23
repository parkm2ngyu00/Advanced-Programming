#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/inotify.h>

static void __handle_inotify_event(const struct inotify_event *event)
{
    if (event->mask & IN_ACCESS)
        printf("IN_ACCESS");
    if (event->mask & IN_ATTRIB)
        printf("IN_ATTRIB");
    if (event->mask & IN_MODIFY)
        printf("IN_MODIFY");
    if (event->mask & IN_OPEN)
        printf("IN_OPEN");
    if (event->mask & IN_CLOSE_WRITE)
        printf("IN_CLOSE_WRITE");
    if (event->mask & IN_CLOSE_NOWRITE)
        printf("IN_CLOSE_NOWRITE");
    if (event->mask & IN_CREATE)
        printf("IN_CREATE");
    if (event->mask & IN_DELETE)
        printf("IN_DELETE");
    if (event->mask & IN_MOVED_FROM)
        printf("IN_MOVED_FROM");
    if (event->mask & IN_MOVED_TO)
        printf("IN_MOVED_TO");
    if (event->mask & IN_MOVE_SELF)
        printf("IN_MOVE_SELF");
    if (event->mask & IN_ISDIR)
        printf("IN_ISDIR");
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

    int wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_MODIFY | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO | IN_MOVE_SELF);
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
