# Ethernet

- net/ethernet.h

    ```
    struct ether_header {
        u_int8_t ether_dhost[ETH_ALEN];
        u_int8_t ether_shost[ETH_ALEN];
        u_int16_t ether_type;
    } __attribute__ ((__packed__));
    ```

- netinet/ip.h

    ```
    struct iphdr {
        #if defined(__LITTLE_ENDIAN_BITFIELD)
            __u8    ihl:4,
                    version:4;
        #elif defined (__BIG_ENDIAN_BITFIELD)
            __u8    version:4,
                    ihl:4;
        #else
            #error  "Please fix <asm/byteorder.h>"
        #endif
            __u8   tos;
            __u16  tot_len;
            __u16  id;
            __u16  frag_off;
            __u8   ttl;
            __u8   protocol;
            __u16  check;
            __u32  saddr;
            __u32  daddr;
            /*The options start here. */
    };
    ```

    ```
    struct ip {
    #if BYTE_ORDER == LITTLE_ENDIAN 
        u_char  ip_hl:4,        /* header length */
                ip_v:4;         /* version */
    #endif
    #if BYTE_ORDER == BIG_ENDIAN 
        u_char  ip_v:4,         /* version */
                ip_hl:4;        /* header length */
    #endif
        u_char  ip_tos;         /* type of service */
        short   ip_len;         /* total length */
        u_short ip_id;          /* identification */
        short   ip_off;         /* fragment offset field */
    #define IP_DF 0x4000            /* dont fragment flag */
    #define IP_MF 0x2000            /* more fragments flag */
        u_char  ip_ttl;         /* time to live */
        u_char  ip_p;           /* protocol */
        u_short ip_sum;         /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
    };
    ```

# TCP

- netinet/tcp.h

    ```
    struct tcphdr
    {
        u_int16_t th_sport;              /* source port */
        u_int16_t th_dport;              /* destination port */
        tcp_seq th_seq;                  /* sequence number */
        tcp_seq th_ack;                  /* acknowledgement number */
    #  if __BYTE_ORDER == __LITTLE_ENDIAN
        u_int8_t th_x2:4;                /* (unused) */
        u_int8_t th_off:4;               /* data offset */
    #  endif
    #  if __BYTE_ORDER == __BIG_ENDIAN
        u_int8_t th_off:4;               /* data offset */
        u_int8_t th_x2:4;                /* (unused) */
    #  endif
        u_int8_t th_flags;
    #  define TH_FIN        0x01
    #  define TH_SYN        0x02
    #  define TH_RST        0x04
    #  define TH_PUSH        0x08
    #  define TH_ACK        0x10
    #  define TH_URG        0x20
        u_int16_t th_win;               /* window */
        u_int16_t th_sum;               /* checksum */
        u_int16_t th_urp;               /* urgent pointer */
    };
    ```

# UDP

- netinet/udp.h

    ```
    struct udphdr
    {
        u_int16_t uh_sport;               /* source port */
        u_int16_t uh_dport;               /* destination port */
        u_int16_t uh_ulen;                /* udp length */
        u_int16_t uh_sum;                 /* udp checksum */
    };
    ```

# ICMP

- netinet/ip_icmp.h

    ```
    struct icmphdr
    {
        u_int8_t type;                    /* message type */
        u_int8_t code;                    /* type sub-code */
        u_int16_t checksum;
        union
        {
            struct
            {
            u_int16_t        id;
            u_int16_t        sequence;
            } echo;                        /* echo datagram */
            u_int32_t        gateway;      /* gateway address */
            struct
            {
            u_int16_t        __unused;
            u_int16_t        mtu;
            } frag;                        /* path mtu discovery */
        } un;
    };
    ```
