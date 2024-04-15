#include "main.h"

tr  init_struct_tr()
{
    tr  new;
    new.help = false;
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