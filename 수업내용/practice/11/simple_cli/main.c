#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <libcli.h>

#ifdef __GNUC__
# define UNUSED(d) d __attribute__ ((unused))
#else
# define UNUSED(d) d
#endif

#define CLI_HOST "0.0.0.0"
#define CLI_PORT 8080

#define MAX_STRING 1024
#define SECRET_CLI_FILE "cli_passwd.txt"

struct cli_def *cli;

// == //

void sigint_handler(int sig)
{
    cli_done(cli);
    exit(0);
}

// == //

#define CMD_TEST_BODY() {\
    printf("%s: ", __FUNCTION__); \
    int i; \
    for (i=0; i<argc; i++) { \
        printf("%s ", argv[i]); \
    } \
    printf("\n"); \
}

int cmd_test1(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(__FUNCTION__);
    CMD_TEST_BODY();
    return 0;
}

int cmd_test2(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(__FUNCTION__);
    CMD_TEST_BODY();
    return 0;
}

int cmd_test3(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(__FUNCTION__);
    CMD_TEST_BODY();
    return 0;
}

int cmd_test4(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(__FUNCTION__);
    CMD_TEST_BODY();
    return 0;
}

int cmd_test5(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(__FUNCTION__);
    CMD_TEST_BODY();
    return 0;
}

int cmd_test6(struct cli_def *cli, UNUSED(const char *command), char *argv[], int argc)
{
    cli_print(__FUNCTION__);
    CMD_TEST_BODY();
    return 0;
}

// == //

static int regular_callback(struct cli_def *cli)
{
    return CLI_OK;
}

static int idle_timeout(struct cli_def *cli)
{
    return CLI_QUIT;
}

static int check_auth(const char *username, const char *password)
{
    FILE *fp = fopen(SECRET_CLI_FILE, "r");
    if (fp != NULL) {
        char buf[MAX_STRING] = {0};

        while (fgets(buf, MAX_STRING-1, fp) != NULL) {
            if (buf[0] == '#') continue;

            char userid[MAX_STRING];
            char userpw[MAX_STRING];

            sscanf(buf, "%s %s", userid, userpw);

            if (strcasecmp(username, userid) == 0 && strcasecmp(password, userpw) == 0) {
                fclose(fp);
                return CLI_OK;
            }
        }

        return CLI_ERROR;
    }

    return CLI_ERROR;
}

static int check_enable(const char *password)
{
    FILE *fp = fopen(SECRET_CLI_FILE, "r");
    if (fp != NULL) {
        char buf[MAX_STRING] = {0};

        while (fgets(buf, MAX_STRING-1, fp) != NULL) {
            if (buf[0] == '#') continue;

            char userid[MAX_STRING];
            char userpw[MAX_STRING];

            sscanf(buf, "%s %s", userid, userpw);

            if (strcasecmp("root", userid) == 0 && strcasecmp(password, userpw) == 0) {
                fclose(fp);
                return 1;
            }
        }

        return 0;
    }

    return 0;
}

// == //

struct arg_struct {
    struct cli_def *cli;
    int acc_sock;
};

static void *connection_handler(void *t_args)
{
    struct arg_struct *args = (struct arg_struct *)t_args;
    struct cli_def *cli = args->cli;
    int acc_sock = args->acc_sock;

    cli_loop(cli, acc_sock);

    return NULL;
}

// == //

int main(void) {
    struct cli_command *c;

    // == //

    cli = cli_init();

    cli_telnet_protocol(cli, 1);
    cli_set_banner(cli, "Welcome Message!");
    cli_set_hostname(cli, "command"); // prompt

    cli_regular(cli, regular_callback);
    cli_regular_interval(cli, 5); // cli timeout (seconds)
    cli_set_idle_timeout_callback(cli, 300, idle_timeout); // cli idle timeout (seconds)

    cli_register_command(cli, NULL, "test1", cmd_test1, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test1");
    cli_register_command(cli, NULL, "test2", cmd_test2, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test2");

    c = cli_register_command(cli, NULL, "get", NULL, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, NULL);
    cli_register_command(cli, c, "test3", cmd_test3, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test3 with get");
    cli_register_command(cli, c, "test4", cmd_test4, PRIVILEGE_UNPRIVILEGED, MODE_EXEC, "call test4 with get");

    c = cli_register_command(cli, NULL, "set", NULL, PRIVILEGE_PRIVILEGED, MODE_EXEC, NULL);
    cli_register_command(cli, c, "test5", cmd_test5, PRIVILEGE_PRIVILEGED, MODE_EXEC, "call test5 with set");
    cli_register_command(cli, c, "test6", cmd_test6, PRIVILEGE_PRIVILEGED, MODE_EXEC, "call test6 with set");

    cli_set_auth_callback(cli, check_auth);
    cli_set_enable_callback(cli, check_enable);

    printf("Initialized command-line interface\n");

    // == //

    signal(SIGINT, sigint_handler);

    // == //

    int server_sock, client_sock;
    struct sockaddr_in server_addr;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("Failed to create a socket\n");
        return -1;
    }

    int on = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(CLI_HOST);
    server_addr.sin_port = htons(CLI_PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Failed to bind the socket\n");
        close(server_sock);
        return -1;
    }

    if (listen(server_sock, 5) == -1) {
        printf("Failed to listen new connections\n");
        close(server_sock);
        return -1;
    }

    printf("Wait for new connections (%s, %d)\n", CLI_HOST, CLI_PORT);

    while ((client_sock = accept(server_sock, NULL, 0))) {
        socklen_t len = sizeof(server_addr);
        if (getpeername(client_sock, (struct sockaddr *)&server_addr, &len) >= 0) {
            printf("Accepted a new connection from %s\n", inet_ntoa(server_addr.sin_addr));
        }

        struct arg_struct t_args = {.cli = cli, .acc_sock = client_sock};
    
        pthread_t thread;
        if (pthread_create(&thread, NULL, connection_handler, (void *)&t_args) < 0) {
            printf("Failed to create a thread\n");
            close(server_sock);
            return -1;
        }
    }

    // == //

    cli_done(cli);

    return 0;
}