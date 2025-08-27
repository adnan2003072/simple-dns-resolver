#include "../includes/dns.h"

void display_err(char t)
{
    switch (t) {
        case 'a':
            printf("Usage: ./dnsresolve <domain-name>\n");
            break ;
        default:
            printf("An unknown error occured !\n");
            break ;
    }
}

uint16_t format_name(u_char *p, char *name)
{
    uint16_t i;
    uint16_t j;
    uint16_t k;

    strcat(name, ".");
    i = 0;
    k = 0;
    while (name[i])
    {
        j = 0;
        while (name[i + j] != '.')
            j++;
        p[k] = j;
        k++;
        while (name[i] != '.')
        {
            p[k] = name[i];
            i++;
            k++;
        }
        i++;
    }
    p[k] = '\0';
    return i;
}

void print_formatted_name(u_char *formatted_name)
{
    uint16_t i = 0;
    uint16_t j;
    uint16_t count;

    printf("\tName: ");
    while (formatted_name[i])
    {
        count = formatted_name[i];
        if (i != 0)
            printf(".");
        i++;
        j = i;
        while (i < j + count)
        {
            printf("%c", formatted_name[i]);
            i++;
        }
    }
    printf("\n");
}

void print_dns_header(t_dns_head *head)
{
    printf("id: %d\n", ntohs(head->id));
    printf("qr: %d\n", head->qr);
    printf("opcode: %d\n", head->opcode);
    printf("aa: %d\n", head->aa);
    printf("tc: %d\n", head->tc);
    printf("rd: %d\n", head->rd);
    printf("ra: %d\n", head->ra);
    printf("z: %d\n", head->z);
    printf("qdcount: %d\n", ntohs(head->qdcount));
    printf("ancount: %d\n", ntohs(head->ancount));
    printf("nscount: %d\n", ntohs(head->nscount));
    printf("arcount: %d\n", ntohs(head->arcount));
}

void print_RR(t_dns_RR *rr)
{
    printf("\tType: %d\n", ntohs(rr->type));
    printf("\tClass: %d\n", ntohs(rr->_class));
    printf("\tTime to live: %d\n", ntohs(rr->ttl));
    printf("\tData length: %d\n", ntohs(rr->rdlen));
    if (ntohs(rr->type) == 1) // RR of type A
        printf("\tAddress: %d.%d.%d.%d\n", rr->rdata[0], rr->rdata[1], rr->rdata[2], rr->rdata[3]);
    else if (ntohs(rr->type) == 5) // RR of type CNAME
        print_formatted_name((u_char *)&(rr->rdata));
}
