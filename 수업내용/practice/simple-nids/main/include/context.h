#pragma once

#include "common.h"

struct packet_t {
    // raw packet
    int pkt_len;
    char pkt[MAX_PKT_SIZE];

    // protocol
    uint32_t proto;

    // ip + port
    uint32_t src_ip;
    uint32_t dst_ip;

    union {
        uint16_t src_port;
        uint8_t icmp_type;
    };
    union {
        uint16_t dst_port;
        uint8_t icmp_code;
    };

    // payload
    int payload_len;
    char *payload;

    struct packet_t *next;
};

struct rule_t {
    uint32_t src_ip;
    uint32_t dst_ip;

    uint32_t proto;

    union {
        uint16_t src_port;
        uint8_t icmp_type;
    };
    union {
        uint16_t dst_port;
        uint8_t icmp_code;
    };

    // alert message
    char message[MAX_STRING];

    // content for string matching
    char content[MAX_STRING];

    // pattern for regular expression matching
    char regex[MAX_STRING];

    // HTTP method
    char method[SHORT_STRING];

    struct rule_t *next;
};

struct context_t {
    // running flag
    int RUN;

    // interface | pcap file
    char source[MAX_STRING];

    // stdout | log file
    char log[MAX_STRING];

    // rule table
    struct rule_t **rule_table;

    // function pointer for packet reception
    int (*reception_func)(struct context_t *ctx);

    // function pointer to stop packet reception
    int (*reception_destroy_func)();

    // function pointer for protocol parsing
    int (*decoder_func)(struct context_t *ctx, struct packet_t *packet);

    // function pointer for string matching
    struct rule_t * (*string_match_func)(struct context_t *ctx, struct packet_t *packet);

    // function pointer for regex matching
    int (*regex_match_func)(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet);

    // function pointer for logging
    int (*log_func)(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet);
};

// context initialization
int init_context(struct context_t *ctx, int argc, char **argv);

// packet reception from pcap-file
int pkt_file(struct context_t *ctx);
int destroy_pkt_file();

// packet reception from live-stream
int pkt_live(struct context_t *ctx);
int destroy_pkt_live();

// protocol parsing
int decoder(struct context_t *ctx, struct packet_t *packet);

// rule management
int load_rules(struct context_t *ctx);
int initialize_rule_table(struct context_t *ctx);
int destroy_rule_table(struct context_t *ctx);

// string matching
struct rule_t * match_string1(struct context_t *ctx, struct packet_t *packet);
struct rule_t * match_string2(struct context_t *ctx, struct packet_t *packet);

// regular expression matching
int match_regex(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet);

// logging
int log_file(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet);
int log_stdout(struct context_t *ctx, struct rule_t *rule, struct packet_t *packet);
