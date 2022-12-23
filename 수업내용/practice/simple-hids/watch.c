#include "watch.h"

char moved_from[MAX_STRING];

static void __handle_inotify_event(struct thread_arg *t_arg, const struct inotify_event *event)
{
    char path[MAX_STRING];
    sprintf(path, "%s/%s", t_arg->root, event->name);

    if (event->mask & IN_ACCESS) {
        printf("IN_ACCESS : name = %s\n", path);
    }
    if (event->mask & IN_ATTRIB) {
        update_entry(t_arg->entries, path);
        printf("IN_ATTRIB : name = %s\n", path);
    }
    if (event->mask & IN_CREATE) {
        add_entry(t_arg->entries, path);
        printf("IN_CREATE : name = %s\n", path);
    }
    if (event->mask & IN_MODIFY) {
        update_entry(t_arg->entries, path);
        printf("IN_MODIFY : name = %s\n", path);
    }
    if (event->mask & IN_DELETE) {
        remove_entry(t_arg->entries, path);
        printf("IN_DELETE : name = %s\n", path);
    }
    if (event->mask & IN_DELETE_SELF) {
        remove_entry(t_arg->entries, path);
        printf("IN_DELETE_SELF : name = %s\n", path);
    }
    if (event->mask & IN_MOVED_FROM) {
        remove_entry(t_arg->entries, path);
        strcpy(moved_from, path);
    }
    if (event->mask & IN_MOVED_TO) {
        add_entry(t_arg->entries, path);
        printf("IN_MOVED_FROM : name = %s, IN_MOVED_TO : name = %s\n", moved_from, path);
    }
    if (event->mask & IN_MOVE_SELF) {
        remove_entry(t_arg->entries, path);
        printf("IN_MOVE_SELF : name = %s\n", path);
    }
}

int read_with_timeout(int fd, char *buf, int buf_size, int timeout_ms)
{
    int rx_len = 0;
    struct timeval timeout;
    fd_set readFds;

    timeout.tv_sec = 0;
    timeout.tv_usec = timeout_ms*1000;

    FD_ZERO(&readFds);
    FD_SET(fd, &readFds);
    select(fd+1, &readFds, NULL, NULL, &timeout);

    if (FD_ISSET(fd, &readFds)) {
        rx_len = read(fd, buf, buf_size);
    }

	return rx_len;
}

void *watch_dir(void *arg) {
    struct thread_arg *t_arg = (struct thread_arg *)arg;

    char buf[4096] __attribute__ ((aligned(__alignof__(struct inotify_event))));
    const struct inotify_event *event;

    int fd = inotify_init();
    if (fd < 0) {
        printf("Failed to initialize inotify\n");
        return NULL;
    }

    int wd = inotify_add_watch(fd, t_arg->root, IN_CREATE | IN_MODIFY | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO | IN_MOVE_SELF);
    if (wd < 0) {
        printf("Failed to add watch %s", t_arg->root);
        return NULL;
    }

    printf("Started to watch %s\n", t_arg->root);

    while (*(t_arg->RUN)) {
        ssize_t size = read_with_timeout(fd, buf, sizeof(buf), 1000);
        if (size == -1 && errno != EAGAIN) {
            printf("Failed to read an event\n");
            return NULL;
        } else if (size <= 0) {
            continue;
        }

        char *ptr;
        for (ptr = buf; ptr < buf + size; ptr += sizeof(struct inotify_event) + event->len) {
            event = (struct inotify_event *)ptr;
            __handle_inotify_event(t_arg, event);
        }
    }

    int ret = inotify_rm_watch(fd, wd);
    if (ret < 0) {
        printf("Failed to remove watch (fd: %d) (wd: %d)", fd, wd);
        return NULL;
    }

    printf("Stopped watching %s\n", t_arg->root);

    return NULL;
}
