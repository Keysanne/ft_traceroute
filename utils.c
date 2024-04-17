#include "main.h"

unsigned short checksum(void* buffer, int bytes)
{
	unsigned short	*buff = buffer;
	unsigned int	sum;
    unsigned short    result;

	for (sum = 0; bytes > 1; bytes -= 2)
		sum += *buff++;
	if (bytes == 1)
		sum += *(unsigned char*)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
    result = ~sum;
	return result;
}

tr  init_struct_tr()
{
    tr  new;
	new.ttl = 1;
    new.help = false;
	/*----------------SOCKET----------------*/
	new.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (new.sockfd == -1)
    {
        perror("socket");
		exit(1);
    }
	struct timeval  timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt(new.sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        perror("sockopt recv timeout");
        exit(1);
    }
    if (setsockopt(new.sockfd, IPPROTO_IP, IP_TTL, &new.ttl, sizeof(new.ttl)) < 0)
    {
        perror("sockopt ttl");
		exit(1);
    }
	/*----------------PACKET----------------*/
	struct icmphdr *icmp = (struct icmphdr *)new.packet;
    icmp->un.echo.sequence = 0;
    icmp->code = 0;
    icmp->type = 8;
    icmp->un.echo.id = 1;
    icmp->checksum = checksum((unsigned short *)icmp, sizeof(struct icmphdr));
    return new;
}

char*   get_arg(char **arg)
{
    int i;
    for (i = 0; arg[i]; i++)
        ;
    i--;
    return arg[i];
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

	if (n == 0)
		return (0);
	for (i = 0;s1[i] && i < n; i++)
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (s2[i] && i < n)
		return (-1);
	return (0);
}

int	gd_malloc(const char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			j++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (j + 1);
}

char	*mot(int *i, const char *str, char c)
{
	char	*mot;
	int		j;
	int		x;

	x = 0;
	j = 0;
	while (str[*i] == c)
		(*i)++;
	while (str[*i + j] != c && str[*i + j])
		j++;
	mot = malloc (j + 1 * sizeof(char));
	if (!mot)
		return (NULL);
	while (x < j)
	{
		mot[x++] = str[*i];
		(*i)++;
	}
	mot[j] = 0;
	return (mot);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	tab = malloc (gd_malloc(s, c) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < gd_malloc(s, c) - 1)
		tab[j++] = mot(&i, s, c);
	tab[j] = 0;
	return (tab);
}

int size_tab(char **tab)
{
    int i;
    for (i = 0; tab[i]; i++)
        ;
    return i;
}

void    free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

bool    is_a_hostname(char *str)
{
    for(int i = 0; str[i]; i++)
    {
        if (ft_isdigit(str[i]))
            return false;
        if (str[i] == '.')
            return true;
    }
    return false;
}