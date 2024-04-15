#include "main.h"

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
    // create the socket
    // create an ICMP packet
    // ----loop
    // sendto() the packet one by one and print the result (3 packet for the RTT) (set a timeout for the packet 2sec)
    // recvfrom() the ip will be stored in the struct print the info
    // use setsockopt to update the TTL
    // ----loop
    free(struc.ip);
    arg_end(options);
    return 0;
}
