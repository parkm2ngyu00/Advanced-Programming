#pragma once

#include "common.h"
#include "context.h"

// memory pool

#define INITIAL_ITEMS 1024
#define MAXIMUM_ITEMS 2048

int push_packet(struct packet_t *packet);
struct packet_t * pop_packet();

int initialize_packet_pool();
int destroy_packet_pool();
