#include "main.h"

int     ping_ip(tr *struc, arg_opt options)
{
    struct sockaddr_in  dst, from;

    char        ip[INET_ADDRSTRLEN];
    socklen_t   fromlen = sizeof(from);
    char        buffer[64], msg[50];
    bool        ip_w = false;

    dst.sin_port = 4000;
    dst.sin_family = AF_INET;
    inet_aton(struc->ip, &(dst.sin_addr));
    if (struc->ttl > 9)
        sprintf(msg, " %d  ", struc->ttl);
    else
        sprintf(msg, "  %d  ", struc->ttl);
    write(1, msg, strlen(msg));
    bzero(msg, sizeof(msg));
    /*--------------------SEND-3-PACKETS--------------------*/
    for (int i = 0; i < 3; i++)
    {
        //time start
        if(sendto(struc->sockfd, struc->packet, sizeof(struct icmphdr), 0, (struct sockaddr*)&dst, sizeof(dst)) <= 0)
        {
            perror("sendto");
            return 0;
        }
        int x = recvfrom(struc->sockfd, (char *)buffer, 64, 0, (struct sockaddr *)&from, &fromlen);
        if (x < 0)
            write(1, "* ", 2);
        else
        {
            if (ip_w == false)
            {
                sprintf(msg, "1 ");
                ip_w = true;
            }
            else
                sprintf(msg, "2 ");
            write(1, msg, ft_strlen(msg));
            bzero(msg, sizeof(msg));
        }
    }
    write(1, "\n", 1);
    /*--------------------RECUP-IP--------------------*/
    inet_ntop(AF_INET, &(from.sin_addr), ip, INET_ADDRSTRLEN);
    if (strcmp(ip, struc->ip) == 0)
        return 0;
    /*--------------------UPDATE-TTL--------------------*/
    struc->ttl += 1;
    if (struc->ttl > 64)
        return 0;
    if (setsockopt(struc->sockfd, IPPROTO_IP, IP_TTL, &struc->ttl, sizeof(struc->ttl)) < 0)
    {
        perror("sockopt ttl");
        free(struc->ip);
        arg_end(options);
    }
    return 1;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("./ft_traceroute: missing host operand\n");
        printf("Try './ft_traceroute --help' or './ft_traceroute -?' for more information.\n");
        return 1;
    }
    tr       struc = init_struct_tr();
    arg_opt     options = arg_init(argc, argv);
    
    init_options(&options, '?', "help", BOOL);
    arg_start(&options);
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
    for (int i = 1; i != 0;)
        i = ping_ip(&struc, options);
    free(struc.ip);
    arg_end(options);
    return 0;
}