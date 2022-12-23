# 디렉토리와 파일 (Directories and Files)

- Directory Structure

    ```
    struct dirent {
        long           d_ino; // i-node number
        off_t          d_off; // offset
        unsigned short d_reclen; // file name length
        char           d_name[NAME_MAX+1]; // file name
    }
    ```

- opendir()

    - Prototype
    
        ```
        DIR *opendir(const char *dirname);
        ```

    - Return

        - 성공 시: 디렉토리 포인터
        - 실패 시: NULL

- readdir()

    - Prototype

        ```
        struct dirent *readdir(DIR *dirp);
        ```

    - Return

        - 성공 시: 파일 정보가 담긴 dirent 구조체
        - 실패 시: NULL

- closedir()

    - Prototype

        ```
        int closedir(DIR *dirp);
        ```
    
    - Return

        - 성공 시: 0
        - 실패 시: -1

- Example: 디렉토리 내 파일 목록 출력

    - practice/07/dir_file 밑에 main.c 파일을 만들고 아래의 내용을 작성

        ```
        #include <stdio.h>
        #include <dirent.h>

        int main(char argc, char *argv[])
        {
            DIR *dp = opendir(argv[1]);
            if (dp == NULL) {
                printf("Failed to open %s\n", argv[1]);
                return -1;
            }

            struct dirent *entry;
            while ((entry = readdir(dp)) != NULL) {
                if (entry->d_ino == 0) {
                    continue;
                }

                printf("%s (i-node: %ld)\n", entry->d_name, entry->d_ino);
            }

            closedir(dp);

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o main main.c
        ./main /home/vagrant/problems
        ```

    - 실행 결과

        ```
        . (i-node: 3151716)
        picnic (i-node: 3289048)
        restore (i-node: 3151499)
        lunchbox (i-node: 3150192)
        README.md (i-node: 3151717)
        .. (i-node: 2886293)
        ```

- Example: 디렉토리 및 하위 디렉토리 내 파일 목록 출력

    - practice/07/dir_sub_dir_file 밑에 main.c 파일을 만들고 아래의 내용을 작성

        ```
        #include <stdio.h>
        #include <unistd.h>
        #include <string.h>
        #include <dirent.h>
        #include <sys/stat.h>

        int printdir(char *dir)
        {
            DIR *dp = opendir(dir);
            if (dp == NULL) {
                printf("Failed to open %s\n", dir);
                return -1;
            }

            struct dirent *entry;
            while ((entry = readdir(dp)) != NULL) {
                struct stat statbuf;
                lstat(entry->d_name, &statbuf);

                if (S_ISDIR(statbuf.st_mode)) {
                    if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name)) {
                        continue;
                    }

                    char buf[1024];
                    sprintf(buf, "%s/%s", dir, entry->d_name);
                    printf("d: %s\n", buf);

                    chdir(buf);

                    printdir(buf);
                } else {
                    printf("f: %s/%s\n", dir, entry->d_name);
                }
            }

            closedir(dp);

            return 0;
        }

        int main(char argc, char *argv[])
        {
            printdir(argv[1]);

            return 0;
        }
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o main main.c
        ./main /home/vagrant/problems
        ```

    - 실행 결과

        ```
        d: /home/vagrant/problems/picnic
        f: /home/vagrant/problems/picnic/picnic.c
        f: /home/vagrant/problems/picnic/picnic
        f: /home/vagrant/problems/picnic/README.md
        d: /home/vagrant/problems/restore
        f: /home/vagrant/problems/restore/restore.c
        f: /home/vagrant/problems/restore/README.md
        d: /home/vagrant/problems/lunchbox
        f: /home/vagrant/problems/lunchbox/lunchbox.c
        f: /home/vagrant/problems/lunchbox/README.md
        f: /home/vagrant/problems/README.md
        ```

# 파일 정보 (File Information)

- File Stat Structure

    ```
    struct stat {
        dev_t      st_dev;      /* ID of device containing file */
        ino_t      st_ino;      /* inode number */
        mode_t     st_mode;     /* protection */
        nlink_t    st_nlink;    /* number of hard links */
        uid_t      st_uid;      /* user ID of owner */
        gid_t      st_gid;      /* group ID of owner */
        dev_t      st_rdev;     /* device ID (if special file) */
        off_t      st_size;     /* total size, in byte */
        blksize_t  st_blksize;  /* blocksize for file system I/O */
        blkcnt_t   st_blocks;   /* number of 512B blocks allocated */
        time_t;    st_atime;    /* time of last access */
        time_t;    st_mtime;    /* time of last modification */
        time_t     st_xtime;    /* time of last status change */
    };
    ```

- stat()

    - Prototype
    
        ```
        int stat(const char *path, struct stat * buf);
        ```

    - Return

        - 성공 시: 0을 반환하며, 두번째 인자 stat 구조체에 파일 정보들로 채워짐
        - 실패 시: -1을 반환하며, errno 변수에 에러 상태가 저장됨

- lstat()

    - Prototype

        ```
        int lstat(const char *path, struct stat * buf);
        ```

    - Return

        - 성공 시: 0을 반환하며, 두번째 인자 stat 구조체에 파일 정보들로 채워짐
        - 실패 시: -1을 반환하며, errno 변수에 에러 상태가 저장됨

- fstat()

    - Prototype

        ```
        int fstat(int fd, struct stat * buf);
        ```
    
    - Return

        - 성공 시: 0을 반환하며, 두번째 인자 stat 구조체에 파일 정보들로 채워짐
        - 실패 시: -1을 반환하며, errno 변수에 에러 상태가 저장됨

- Note

    - lstat()의 경우 path가 심볼릭 링크일 때, 해당 심볼릭 링크 파일에 대한 정보가 구조체에 저장됨
    - stat()의 경우 path가 심볼릭 링크이더라도, 원본 파일의 정보가 구조체에 저장됨

- Example: 파일 정보 출력

    - practice/07/file_stat 밑에 main.c 파일을 만들고 아래의 내용을 작성

        ```
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
        ```

    - 코드 컴파일 후 실행

        ```
        gcc -o main main.c
        ./main ./main.c
        ```

    - 실행 결과

        ```
        ./main.c
            Type: regular file
            Mode: 100664 (octal)
            UID: 1000
            GID: 1000
            Size: 1386 bytes
            Last Access: Thu Nov  3 15:00:00 2022
            Last Modification: Thu Nov  3 15:00:00 2022
        ```

# 실습: 파일 관리 (File Management)

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
