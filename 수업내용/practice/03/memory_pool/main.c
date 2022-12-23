    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>

    #define INITIAL_ITEMS 100
    #define MAXIMUM_ITEMS 200

    struct sample_t {
        int value;
        struct sample_t *next;
    };

    static int items;
    static struct sample_t *sample_pool;
    static pthread_spinlock_t sample_lock;

    int push_sample(struct sample_t *sample)
    {
        memset(sample, 0, sizeof(struct sample_t));

        pthread_spin_lock(&sample_lock);

        if (items + 1 > MAXIMUM_ITEMS) {
            free(sample);
            pthread_spin_unlock(&sample_lock);
            printf("Released a used sample\n");
            return 0;
        }

        if (sample_pool == NULL) {
            sample_pool = sample;
        } else {
            sample->next = sample_pool;
            sample_pool = sample;
        }

        printf("Pushed an empty sample into the sample pool\n");

        items++;

        pthread_spin_unlock(&sample_lock);

        return 0;
    }

    struct sample_t * pop_sample()
    {
        struct sample_t *sample;

        pthread_spin_lock(&sample_lock);

        if (sample_pool == NULL) {
            sample = (struct sample_t *)malloc(sizeof(struct sample_t));
            memset(sample, 0, sizeof (struct sample_t));
            printf("Allocated a new sample\n");
        } else {
            sample = sample_pool;
            sample_pool = sample_pool->next;
            items--;
            printf("Got a sample form the sample pool\n");
        }

        pthread_spin_unlock(&sample_lock);

        return sample;
    }

    int initialize_memory_pool()
    {
        items = 0;

        if (pthread_spin_init(&sample_lock, PTHREAD_PROCESS_PRIVATE)) {
            printf("[ERROR] Failed to initialize sample_lock\n");
            return -1;
        }

        for (int i=0; i<INITIAL_ITEMS; i++) {
            struct sample_t *sample = (struct sample_t *)malloc(sizeof(struct sample_t));
            push_sample(sample);
        }

        return 0;
    }

    int destroy_memory_pool()
    {
        struct sample_t *sample = sample_pool;

        pthread_spin_lock(&sample_lock);

        while (sample != NULL) {
            struct sample_t *temp = sample;
            sample = sample->next;
            free(temp);
        }

        pthread_spin_unlock(&sample_lock);

        pthread_spin_destroy(&sample_lock);

        return 0;
    }

    int main() {
        struct sample_t *sample;

        initialize_memory_pool();

        sample = pop_sample();
        push_sample(sample);

        destroy_memory_pool();

        return 0;
    }