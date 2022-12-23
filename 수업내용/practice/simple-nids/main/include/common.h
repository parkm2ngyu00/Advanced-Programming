#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <ctype.h>

// interface | pcap file | log file | message | content | regex
#define MAX_STRING   1024

// http request (method)
#define SHORT_STRING 8

// max packet size
#define MAX_PKT_SIZE 4096

// protocol
enum {
    PROTO_IPV4 = 1 << 0,
    PROTO_TCP  = 1 << 1,
    PROTO_UDP  = 1 << 2,
    PROTO_ICMP = 1 << 3,
    PROTO_HTTP = 1 << 4,
};

// rule table
#define IP_RULES     0
#define TCP_RULES    1
#define UDP_RULES    2
#define ICMP_RULES   3
#define HTTP_RULES   4
#define NUM_OF_PROTO 5
