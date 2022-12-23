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
