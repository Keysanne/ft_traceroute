#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i])
		return (-1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i = 0, rst = 0, cpt = 0;

	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			cpt = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		rst = rst * 10 + (nptr[i++] - '0');
	if (cpt == 1)
		rst = -rst;
	return (rst);
}

char	*ft_strdup(char *s)
{
	char	*final;
	int		i = -1;

	final = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	while (s[++i])
		final[i] = s[i];
	final[i] = 0;
	return (final);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i = -1;
	unsigned char	*dest2 = (unsigned char *)dest, *src2 = (unsigned char *)src;

	if (!dest && !src)
		return (NULL);
	while (++i < n)
		dest2[i] = src2[i];
	return (dest);
}

void    *ft_realloc(void *ptr, size_t size)
{
    void    *new_ptr = malloc(size);

    if (!new_ptr)
        return NULL;
    ft_memcpy(new_ptr, ptr, sizeof(ptr));
    free(ptr);
    return new_ptr;
}
