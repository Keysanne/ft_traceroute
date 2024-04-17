#include "main.h"

int     ping_ip(tr *struc, arg_opt options)
{
    struct sockaddr_in  dst, from;

    dst.sin_family = AF_INET;
    char ip[INET_ADDRSTRLEN];
    socklen_t   fromlen = sizeof(from);
    char        buffer[64];

    inet_aton(struc->ip, &(dst.sin_addr));
    dst.sin_port = 4000;
    printf("  %d : ", struc->ttl);
    //remplacer par un write
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
            // no time -> '*'
        else
            write(1, "time ", 5);
            //write time end et l'ip si elle n'a pas deja ete ecrite
    }
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