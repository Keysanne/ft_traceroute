#ifndef MAIN_H
# define MAIN_H

#include "argparse/arg.h"

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>

typedef struct  tr
{
    void*   help;
    char*   arg;
    char*   ip;

    int     ttl;
    int     sockfd;
    char    packet[64];
}               tr;

tr      init_struct_tr();
char*   get_arg(char **arg);
void    help_options(arg_opt options, void* help);
char*   convert_to_ip(char *ip);
bool    is_a_hostname(char *str);

char	*ft_strdup(char *s);
char	**ft_split(const char *s, char c);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int     size_tab(char **tab);
void    free_tab(char **tab);
int	    ft_isdigit(int c);
int     ft_strlen(char *str);

#endif