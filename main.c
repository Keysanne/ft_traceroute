#include "main.h"


void    update_sock(tr struc, arg_opt options)
{
    struc.ttl += 1;
    if (setsockopt(struc.sockfd, IPPROTO_IP, IP_TTL, &struc.ttl, sizeof(struc.ttl)) < 0)
    {
        perror("sockopt ttl");
        free(struc.ip);
        arg_end(options);
    }
}

int     ping_ip(tr struc, int i)
{
    return 0;
    // sendto() the packet one by one and print the result (3 packet for the RTT) (set a timeout for the packet 2sec)
    // recvfrom() the ip will be stored in the struct print the info
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
    for (int i = 1; i != 0; i++)
    {
        i = ping_ip(struc, i);
        update_sock(struc, options);
    }
    free(struc.ip);
    arg_end(options);
    return 0;
}
