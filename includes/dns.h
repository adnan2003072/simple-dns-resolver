#ifndef DNS_H
# define DNS_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/types.h>

# define DNS_RESOLVER_IP "192.168.100.1"

// RR types
typedef enum
{
    DNS_TYPE_A       = 1,
    DNS_TYPE_NS      = 2,
    DNS_TYPE_MD      = 3,
    DNS_TYPE_MF      = 4,
    DNS_TYPE_CNAME   = 5,
    DNS_TYPE_SOA     = 6,
    DNS_TYPE_MB      = 7,
    DNS_TYPE_MG      = 8,
    DNS_TYPE_MR      = 9,
    DNS_TYPE_NULL_RR = 10,
    DNS_TYPE_WKS     = 11,
    DNS_TYPE_PTR     = 12,
    DNS_TYPE_HINFO   = 13,
    DNS_TYPE_MINFO   = 14,
    DNS_TYPE_MX      = 15,
    DNS_TYPE_TXT     = 16
} e_dns_type;

// QTYPE values
typedef enum
{
    DNS_QTYPE_AXFR   = 252,
    DNS_QTYPE_MAILIB = 253,
    DNS_QTYPE_MAILA  = 254,
    DNS_QTYPE_ALL    = 255
} e_dns_qtype;

// DNS CLASS values
typedef enum
{
    DNS_CLASS_IN     = 1,
    DNS_CLASS_CS     = 2,
    DNS_CLASS_CH     = 3,
    DNS_CLASS_HS     = 4
} e_dns_class;

# define DNS_QCLASS_ANY 255

//                    DNS header format
//      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                      ID                       |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    QDCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    ANCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    NSCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                    ARCOUNT                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

typedef struct s_dns_head
{
    uint16_t     id;
    unsigned int qr: 1;
    unsigned int opcode: 4;
    unsigned int aa: 1;
    unsigned int tc: 1;
    unsigned int rd: 1;
    unsigned int ra: 1;
    unsigned int z: 1;
    unsigned int rcode: 4;
    uint16_t     qdcount;
    uint16_t     ancount;
    uint16_t     nscount;
    uint16_t     arcount;
} t_dns_head;

//                  Question section format
//      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                                               |
//    /                     QNAME                     /
//    /                                               /
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                     QTYPE                     |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                     QCLASS                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
typedef struct s_dns_question
{
    uint16_t      qtype;
    uint16_t      qclass;
} t_dns_question;

//                    Resource Record RR
//      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                                               |
//    /                                               /
//    /                      NAME                     /
//    |                                               |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                      TYPE                     |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                     CLASS                     |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                      TTL                      |
//    |                                               |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//    |                   RDLENGTH                    |
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
//    /                     RDATA                     /
//    /                                               /
//    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

typedef struct s_dns_RR
{
    uint16_t type;
    uint16_t _class;
    uint32_t ttl;
    uint16_t rdlen;
    u_char   rdata[4];
} t_dns_RR;

void display_err(char t);
uint16_t format_name(u_char *p, char *name);
void print_formatted_name(u_char *formatted_name);
void print_dns_header(t_dns_head *head);
void print_RR(t_dns_RR *rr);

#endif // !DNS_H
