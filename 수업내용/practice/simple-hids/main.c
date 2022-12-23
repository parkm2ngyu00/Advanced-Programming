#include "common.h"

int RUN;

void sig_handler(int signo)
{
    printf("Got an interrupt\n");
    RUN = 0;
}

int main(int argc, char **argv)
{
    struct entry *entries = NULL;

    if (argc != 2) {
        printf("Usage: %s [target directory]\n", argv[0]);
        return -1;
    }

    // remove the last '/'
    if (argv[1][strlen(argv[1])-1] == '/') {
        argv[1][strlen(argv[1])-1] = 0;
    }

    // initialize a thread pool (NUM_OF_THREADS)

    // create entries for sub-directories and files
    entries = load_entries(entries, argv[1]);

    // add signal handler
    signal(SIGINT, (void *)sig_handler);

    RUN = 1;

    pthread_t thread;
    struct thread_arg t_arg = {.RUN = &RUN, .root = argv[1], .entries = entries};

    // call watch function
    int ret = pthread_create(&thread, NULL, watch_dir, (void*)&t_arg);
    if (ret < 0) {
        printf("Failed to create a thread\n");
        return -1;
    }

    while(RUN) {
        sleep(1);
    }

    pthread_join(thread, NULL);

    // release the entries
    // (when the signal handler is implemented, move this in the signal handler)
    release_entries(entries);

    // destroy the thread pool
    // (when the signal handler is implemented, move this in the signal handler)

    return 0;
}
