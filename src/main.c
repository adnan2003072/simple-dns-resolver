#include "../includes/dns.h"

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        display_err('a');
        return 1;
    }
    char buf[65535];
    int s;
    struct sockaddr_in sock;

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sock.sin_addr.s_addr = inet_addr(DNS_RESOLVER_IP);
    sock.sin_port = htons(53);
    sock.sin_family = AF_INET;

    t_dns_head *dns = (t_dns_head *)&buf;
    dns->id = htons(getpid());
    dns->qr = htons(1);
    dns->opcode = 0;
    dns->aa = 0;
    dns->tc = 0;
    dns->rd = 0;
    dns->ra = 0;
    dns->z = 0;
    dns->qdcount = htons(1);
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    uint16_t qname_size = format_name((u_char *)&buf[sizeof(t_dns_head)], av[1]);
    t_dns_question *question = (t_dns_question *)(&buf[sizeof(t_dns_head)] + qname_size + 1);
    question->qtype = htons(1);
    question->qclass = htons(1);

    if (sendto(s, buf, sizeof(t_dns_head) + qname_size + 1 + sizeof(t_dns_question), 0,
               (struct sockaddr *)&sock, sizeof(sock)) < 0)
    {
        perror("sendto error");
    }

    socklen_t socklen = sizeof(sock);
    long response_size = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&sock, &socklen);
    if (response_size < 0)
    {
        perror("recvfrom error");
    }

    /*print_dns_header(dns);*/
    uint16_t ans_RRs; /*auth_RRs, add_RRs;*/
    ans_RRs = ntohs(dns->ancount);
    /*auth_RRs = dns->nscount;*/
    /*add_RRs = dns->qdcount;*/
    
    u_char *answers = (u_char *)&buf[sizeof(t_dns_head) + qname_size + 1 + sizeof(t_dns_question)];
    uint16_t answer_count = 0;
    uint16_t i = 0;
    uint16_t *offset;
    printf("Got %u Answers :\n", ans_RRs);
    if (ans_RRs > 0)
    {
        while (answers[i])
        {
            printf("Answer[%d]:\n", answer_count);
            int highest_two_bits = answers[i] & 192;
            if (highest_two_bits == 192) // this is a pointer to the name
            {
                offset = (uint16_t *)&answers[i];
                *offset = ntohs(*offset) & 16383;
                /*printf("\toffset = %u\n", *offset);*/
                print_formatted_name((u_char *)&buf[*offset]);
                print_RR((t_dns_RR *)&answers[i + 2]);
            }
            if (ntohs(((t_dns_RR *)&answers[i + 2])->type) == 5)
                i += ntohs(((t_dns_RR *)&answers[i + 2])->rdlen) - 4;
            i += sizeof(t_dns_RR);
            answer_count++;
        }
    } else {
        printf("%s : Name \'%s\' not found\n", av[1], av[1]);
        return 1;
    }

    return 0;
}
