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
