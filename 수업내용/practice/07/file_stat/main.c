#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat info;

    if (stat(argv[1], &info) != 0) {
        printf("Failed to get the stat of %s\n", argv[1]);
        return -1;
    }

    printf("%s\n", argv[1]);

    switch(info.st_mode & S_IFMT) {
        case S_IFBLK:
            printf("\tType: block device\n");
            break;
        case S_IFCHR:
            printf("\tType: character device\n");
            break;
        case S_IFDIR:
            printf("\tType: directory\n");
            break;
        case S_IFIFO:
            printf("\tType: FIFO/pipe\n");
            break;
        case S_IFLNK:
            printf("\tType: symlink\n");
            break;
        case S_IFREG:
            printf("\tType: regular file\n");
            break;
        case S_IFSOCK:
            printf("\tType: socket\n");
            break;
        default:
            printf("\tType: unknown\n");
            break;
    }

    printf("\tMode: %lo (octal)\n", (unsigned long)info.st_mode);
    printf("\tUID: %ld\n", (long)info.st_uid);
    printf("\tGID: %ld\n", (long)info.st_gid);
    printf("\tSize: %lld bytes\n", (long long)info.st_size);
    printf("\tLast Access: %s", ctime(&info.st_atime));
    printf("\tLast Modification: %s", ctime(&info.st_mtime));

    return 0;
}
