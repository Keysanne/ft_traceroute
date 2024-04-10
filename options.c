#include "main.h"

void    help_options(arg_opt options, void* help)
{
    printf("Usage: ./ft_traceroute [OPTION...] HOST\n");
    printf("Print the route packets trace to network host.\n\n");
    printf("   -?, --help\t\tgive this help list\n\n");
    free(help);
    arg_end(options);
}