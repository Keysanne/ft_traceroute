#include "main.h"

int     ping_ip(tr *struc, arg_opt options)
{
    struct sockaddr_in  dst, from;

    char        ip[INET_ADDRSTRLEN];
    socklen_t   fromlen = sizeof(from);
    char        buffer[64], msg[50];
    bool        ip_w = false;
    struct timeval  start, end;

    dst.sin_port = struc->_port;
    dst.sin_family = AF_INET;
    inet_aton(struc->ip, &(dst.sin_addr));
    if (struc->ttl > 9)
        sprintf(msg, " %d   ", struc->ttl);
    else
        sprintf(msg, "  %d   ", struc->ttl);
    write(1, msg, strlen(msg));
    ft_bzero(msg, sizeof(msg));
    /*--------------------SEND-3-PACKETS--------------------*/
    for (int i = 0; i < struc->_nb_of_packets; i++)
    {
        gettimeofday(&start, NULL);
        if(sendto(struc->sockfd, struc->packet, sizeof(struct icmphdr), 0, (struct sockaddr*)&dst, sizeof(dst)) <= 0)
        {
            printf("Error: sendto\n");
            return 0;
        }
        int x = recvfrom(struc->sockfd, (char *)buffer, 64, 0, (struct sockaddr *)&from, &fromlen);
        if (x < 0)
        {
            write(1, "*  ", 3);
            ip[0] = 0;
        }
        else
        {
            gettimeofday(&end, NULL);
            double time = (end.tv_sec - start.tv_sec) * 1000.0;
            time += (end.tv_usec - start.tv_usec) / 1000.0;
            if (ip_w == false)
            {
                inet_ntop(AF_INET, &(from.sin_addr), ip, INET_ADDRSTRLEN);
                sprintf(msg, "%s  %.3fms  ", ip, time);
                ip_w = true;
            }
            else
                sprintf(msg, "%.3fms  ", time);
            write(1, msg, ft_strlen(msg));
            ft_bzero(msg, sizeof(msg));
        }
    }
    write(1, "\n", 1);
    /*--------------------RECUP-IP--------------------*/
    if (strcmp(ip, struc->ip) == 0)
        return 0;
    /*--------------------UPDATE-TTL--------------------*/
    struc->ttl += 1;
    if (struc->ttl > struc->_max_hop)
        return 0;
    if (setsockopt(struc->sockfd, IPPROTO_IP, IP_TTL, &struc->ttl, sizeof(struc->ttl)) < 0)
    {
        printf("Error: sockopt ttl update\n");
        free(struc->ip);
        arg_end(options);
    }
    return 1;
}

void    _options(tr *struc, arg_opt options)
{
    /*------------------MAX_HOP------------------*/
    struc->max_hop = find_options(&options, "max-hop");
    if(struc->max_hop == NULL)
        struc->_max_hop = 64;
    else
        struc->_max_hop = *(int *)struc->max_hop;
    /*-------------------PORTS-------------------*/
    struc->port = find_options(&options, "port");
    if(struc->port == NULL)
        struc->_port = 4000;
    else
        struc->_port = *(int *)struc->port;
    /*---------------NB_OF_PACKETS---------------*/
    struc->nb_of_packets = find_options(&options, "tries");
    if(struc->nb_of_packets == NULL)
        struc->_nb_of_packets = 3;
    else
        struc->_nb_of_packets = *(int *)struc->nb_of_packets;
    /*---------------WAIT---------------*/
    struc->wait = find_options(&options, "wait");
    if(struc->wait == NULL)
        struc->_wait = 3;
    else
        struc->_wait = *(int *)struc->wait;
    struct timeval  timeout;
    timeout.tv_sec = struc->_wait;
    timeout.tv_usec = 0;
    if (setsockopt(struc->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        printf("Error: sockopt recv timeout\n");
        close(struc->sockfd);
        arg_end(options);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("./ft_traceroute: missing host operand\n");
        printf("Try './ft_traceroute --help' or './ft_traceroute -?' for more information.\n");
        return 1;
    }
    arg_opt     options = arg_init(argc, argv);
    tr       struc = init_struct_tr();
    
    init_options(&options, '?', "help", BOOL);
    init_options(&options, 'm', "max-hop", INT);
    init_options(&options, 'p', "port", INT);
    init_options(&options, 'q', "tries", INT);
    init_options(&options, 'w', "wait", INT);
    arg_start(&options);
    _options(&struc, options);
    struc.help = find_options(&options, "help");
    if ((bool)struc.help == true)
        help_options(options, struc.help);
    struc.arg = get_arg(options.clean_arg);
    struc.ip = convert_to_ip(struc.arg);
    if (!struc.ip)
    {
        free(struc.ip);
        printf("./ft_traceroute: unknown host\n");
        arg_end(options);
    }
    printf("./ft_traceroute to %s (%s), %d hops max\n", struc.arg, struc.ip, struc._max_hop);
    for (int i = 1; i != 0;)
        i = ping_ip(&struc, options);
    free(struc.ip);
    close(struc.sockfd);
    arg_end(options);
    return 0;
}