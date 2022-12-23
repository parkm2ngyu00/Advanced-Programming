#include "common.h"
#include "context.h"
#include <signal.h>

struct context_t ctx;

void sigint_handler(int signo)
{
	stop_capturing();

	destroy_stats(&ctx);

	destroy_rules(&ctx);

	exit(0);
}

int main(int argc, char **argv)
{
	if (init_context(&ctx, argc, argv) != 0) {
		printf("Failed to initialize context\n");
		return -1;
	}

	if (init_rules(&ctx) != 0) {
		printf("Failed to initialize rules\n");
		return -1;
	}

	if (load_rules(&ctx) != 0) {
		printf("Failed to load rules\n");
		return -1;
	}

	if (init_stats(&ctx) != 0) {
		printf("Failed to initialize stats\n");
		return -1;
	}

	signal(SIGINT, sigint_handler);

	if (start_to_capture(&ctx) != 0) {
		printf("Failed to capture packets\n");
		return -1;
	}

	while (1) {
		sleep(1);
	}

	return 0;
}
