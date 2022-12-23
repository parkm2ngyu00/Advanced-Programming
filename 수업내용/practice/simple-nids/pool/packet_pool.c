#include "packet_pool.h"

static int packet_items;
static struct packet_t *packet_pool;
static pthread_spinlock_t packet_lock;

int push_packet(struct packet_t *packet)
{
    memset(packet, 0, sizeof(struct packet_t));

    pthread_spin_lock(&packet_lock);

    if (packet_items + 1 > MAXIMUM_ITEMS) {
        free(packet);
        pthread_spin_unlock(&packet_lock);
        return 0;
    }

    if (packet_pool == NULL) {
        packet_pool = packet;
    } else {
        packet->next = packet_pool;
        packet_pool = packet;
    }

    packet_items++;

    pthread_spin_unlock(&packet_lock);

    return 0;
}

struct packet_t * pop_packet()
{
    struct packet_t *packet;

    pthread_spin_lock(&packet_lock);

    if (packet_pool == NULL) {
        packet = (struct packet_t *)malloc(sizeof(struct packet_t));
        memset(packet, 0, sizeof (struct packet_t));
    } else {
        packet = packet_pool;
        packet_pool = packet_pool->next;
        packet_items--;
    }

    pthread_spin_unlock(&packet_lock);

    return packet;
}

int initialize_packet_pool()
{
    if (pthread_spin_init(&packet_lock, PTHREAD_PROCESS_PRIVATE)) {
        printf("[ERROR] Failed to initialize packet_lock\n");
        return -1;
    }

    int i;

    for (i=0; i<INITIAL_ITEMS; i++) {
        struct packet_t *packet = (struct packet_t *)malloc(sizeof(struct packet_t));
        push_packet(packet);
    }

    return 0;
}

int destroy_packet_pool()
{
    struct packet_t *packet = packet_pool;

    pthread_spin_lock(&packet_lock);

    while (packet != NULL) {
        struct packet_t *temp = packet;
        packet = packet->next;
        free(temp);
    }

    pthread_spin_unlock(&packet_lock);

    pthread_spin_destroy(&packet_lock);

    return 0;
}
