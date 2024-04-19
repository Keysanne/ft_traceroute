#include "main.h"
#include <netdb.h>


int find(char* str, char find)
{
	for(int i = 0; str[i]; i++)
		if (str[i] == find)
			return i;
	return -1;
}

long hxtoi(char* str)
{
	long		x = 0, y = 0, rst = 0; 
	char	*base[] = {"0123456789abcdef", "0123456789ABCDEF"};

	for(int i = 2; str[i]; i++)
	{
		rst *= 16;
		if ((x = find(base[0], str[i])) == -1 && (y = find(base[1], str[i])) == -1)
			return -1;
		rst += x > y ? x : y;
	}
	return rst;
}

char* hostname_to_ip(char * hostname)
{
	/*-------------------FQDN-------------------*/
	if (is_a_hostname(hostname))
	{
		char**	tab = ft_split(hostname, '.');
		if (size_tab(tab) != 3)
		{
			free_tab(tab);
			free(hostname);
			return strdup("");
		}
		free_tab(tab);
	}
	/*------------------------------------------*/
	struct hostent	*host = gethostbyname(hostname);

	free(hostname);
	if (host == NULL)
		return strdup("");
    return strdup(inet_ntoa(**(struct in_addr **)host->h_addr_list));
}

char*    convert_to_ip(char *str)
{
    struct sockaddr_in sa;
	char *ip = ft_strdup(str);

    if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1)
        return ip;
    else
    {
        if (ft_strncmp(ip, "0x", 2) == 0)
            sprintf(ip, "%ld", hxtoi(ip));
        ip = hostname_to_ip(ip);
        if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1)
            return ip;
    }
	free(ip);
	return NULL;
}