#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sys/inotify.h>
#include "thpool.h"

#define MAX_STRING 1024
#define NUM_OF_THREADS 8

struct entry {
    char name[MAX_STRING];       // name
    mode_t mode;                 // mode
    off_t size;                  // total size
    time_t atime;                // time of last access
    time_t mtime;                // time of last modification

    unsigned char hash[MD5_DIGEST_LENGTH];

    struct entry *sibling;
    struct entry *child;
};

struct entry *load_entries(struct entry *entries, char *dir);
int release_entries(struct entry *entries);

int add_entry(struct entry *entries, const char *path);
int update_entry(struct entry *entries, const char *path);
int remove_entry(struct entry *entries, const char *path);

int hash_func(char *path, unsigned char *hash);

struct thread_arg {
    int *RUN;
    char *root;
    struct entry *entries;
};

void *watch_dir(void *arg);
