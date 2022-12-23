#include "common.h"
#include "context.h"
#include "packet_pool.h"

#include <signal.h>

struct context_t ctx;

void sigint_handler(int signo)
{
    // destroy packet reception
    ctx.reception_destroy_func();

    // destroy memory pool
    if (destroy_packet_pool() != 0) {
        printf("[ERROR] Failed to destroy the memory pool for raw packets\n");
    }

    // destroy rule tables
    if (destroy_rule_table(&ctx) != 0) {
        printf("[ERROR] Failed to destroy the rule tables\n");
    }

    // turn the running flag off
    ctx.RUN = 0;
}

int main(int argc, char **argv)
{
    // initialize context
    if (init_context(&ctx, argc, argv) != 0) {
        printf("[ERROR] Failed to initialize the context\n");
        return -1;
    }

    // initialize memory pool
    if (initialize_packet_pool() != 0) {
        printf("[ERROR] Failed to initialize a memory pool for raw packets\n");
        return -1;
    }

    // intialize rule table
    if (initialize_rule_table(&ctx) != 0) {
        printf("[ERROR] Failed to initialize rule tables\n");
        return -1;
    }

    // load rules
    if (load_rules(&ctx) != 0) {
        printf("[ERROR] Failed to load rules\n");
        return -1;
    }

    // add signal handler
    signal(SIGINT, sigint_handler);

    // turn the running flag on
    ctx.RUN = 1;

    printf("[INFO] Initialized Simple NIDS\n");

    // start to capture or load packets
    ctx.reception_func(&ctx);

    while (ctx.RUN) {
        sleep(1);
    }

    printf("[INFO] Destroyed Simple NIDS\n");

    return 0;
}
