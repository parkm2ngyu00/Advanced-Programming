#include "entry.h"

int update_entry_info(struct entry *node, const char *path)
{
    struct stat info = {0};

    strcpy(node->name, path);

    if (stat(path, &info) != 0) {
        printf("Failed to get the stat of %s\n", path);
        return -1;
    }

    node->mode = info.st_mode;
    node->size = info.st_size;
    node->atime = info.st_atime;
    node->mtime = info.st_mtime;

    hash_func(node->name, node->hash);

    node->sibling = NULL;
    node->child = NULL;

    return 0;
}

struct entry * update_entries(struct entry *head, const char *current_dir)
{
    DIR *dp = opendir(current_dir);
    if (dp == NULL) {
        printf("Failed to open %s\n", current_dir);
        return NULL;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name)) {
            continue;
        }

        char path[1024] = {0};
        sprintf(path, "%s/%s", current_dir, entry->d_name);

        struct entry *new_node = (struct entry *)malloc(sizeof(struct entry));
        if (new_node == NULL) {
            printf("Failed to allocate a new node\n");
            continue;
        }
        update_entry_info(new_node, path);

        char atime[MAX_STRING];
        sprintf(atime, "%s", ctime(&new_node->atime));
        atime[strlen(atime)-1] = 0;

        char mtime[MAX_STRING];
        sprintf(mtime, "%s", ctime(&new_node->mtime));
        mtime[strlen(mtime)-1] = 0;

        if (S_ISDIR(new_node->mode)) {
            printf("d: %s | %lld | %s | %s | %02x\n", path, (long long)new_node->size, atime, mtime, new_node->hash[0]);
            new_node->child = update_entries(new_node->child, path);
        } else {
            printf("f: %s | %lld | %s | %s | %02x\n", path, (long long)new_node->size, atime, mtime, new_node->hash[0]);
        }

        if (head == NULL) {
            head = new_node;
        } else {
            new_node->sibling = head;
            head = new_node;
        }
    }

    closedir(dp);

    return head;
}

struct entry *load_entries(struct entry *head, char *dir)
{
    head = (struct entry *)malloc(sizeof(struct entry));
    if (head == NULL) {
        printf("Failed to allocate a new node\n");
        return NULL;
    }
    update_entry_info(head, dir);

    head->child = update_entries(head->child, dir);

    return head;
}

// == //

int release_entries(struct entry *head)
{
    if (head == NULL) {
        return -1;
    }

    struct entry *peer = head;
    while (peer != NULL) {
        struct entry *temp = peer;
        peer = peer->sibling;

        if (S_ISDIR(temp->mode)) {
            release_entries(temp->child);
            printf("(release) d: %s\n", temp->name);
        } else {
            printf("(release) f: %s\n", temp->name);
        }

        free(temp);
    }

    return 0;
}

// == //

int add_entry(struct entry *head, const char *path)
{
    if (head == NULL) {
        return -1;
    }

    struct entry *peer = head, *prev = NULL;
    while (peer != NULL) {
        if (S_ISDIR(peer->mode)) {
            if (strncmp(peer->name, path, strlen(peer->name)) == 0) {
                printf("lookup: %s\n", peer->name);
                if (add_entry(peer->child, path) == 0) {
                    return 0;
                }
            }
        } else { // file
            if (strcmp(peer->name, path) == 0) {
                printf("update (not add): %s\n", peer->name);
                update_entry_info(peer, path);
                return 0;
            }
        }

        prev = peer;
        peer = peer->sibling;
    }

    printf("add: %s\n", path);

    struct entry *new_node = (struct entry *)malloc(sizeof(struct entry));
    if (new_node == NULL) {
        printf("Failed to allocate a new node\n");
        return -1;
    }
    update_entry_info(new_node, path);

    if (head == NULL) {
        head = new_node;
    } else {
        prev->sibling = new_node;
    }

    return 0;
}

int update_entry(struct entry *head, const char *path)
{
    if (head == NULL) {
        return -1;
    }

    struct entry *peer = head;
    while (peer != NULL) {
        if (S_ISDIR(peer->mode)) {
            if (strncmp(peer->name, path, strlen(peer->name)) == 0) {
                printf("lookup: %s\n", peer->name);
                update_entry(peer->child, path);
            }
        } else { // file
            if (strcmp(peer->name, path) == 0) {
                printf("update: %s\n", peer->name);
                update_entry_info(peer, path);
                return 0;
            }
        }

        peer = peer->sibling;
    }

    return 0;
}

int remove_entry(struct entry *head, const char *path)
{
    if (head == NULL) {
        return -1;
    }

    struct entry *peer = head, *prev = NULL;
    while (peer != NULL) {
        if (S_ISDIR(peer->mode)) {
            if (strncmp(peer->name, path, strlen(peer->name)) == 0) {
                printf("lookup: %s\n", peer->name);
                remove_entry(peer->child, path);
            }
        } else { // file
            if (strcmp(peer->name, path) == 0) {
                printf("remove: %s\n", peer->name);
                if (prev != NULL) {
                    struct entry *temp = peer;
                    prev->sibling = peer->sibling;
                    free(temp);
                } else {
                    head = peer->sibling;
                    free(peer);
                }
                return 0;
            }
        }

        prev = peer;
        peer = peer->sibling;
    }

    return 0;
}
