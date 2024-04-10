#include "argparse.h"

bool    valid_str(char *str)
{
    if(str[0] == '-')
        return false;
    return true;
}

bool    valid_int(char *str)
{
    if (str[0] == '-' || ft_isdigit(str[0]))
    {
        for(int i = 1; str[i]; i++)
            if(!ft_isdigit(str[i]))
                return false;
        return true;
    }
    return false;
}

bool    valid_float(char *str)
{
    bool    dot = false;
    if (str[0] == '-' || ft_isdigit(str[0]))
    {
        for(int i = 1; str[i]; i++)
        {
            if(!ft_isdigit(str[i]))
            {
                if(str[i] == '.' && dot == false)
                {
                    dot = true;
                    continue;
                }
                return false;
            }
        }
    }
    return true;
}

char*   to_str(char c)
{
    char    *rst = malloc(2);
    rst[0] = c;
    rst[1] = 0;
    return rst;
}

char    *ft_strjoin(char *s1, char *s2)
{
    int j = 0;
    char *rst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    for(int i = 0; s1[i];i++)
        rst[j++] = s1[i];
    for(int i = 0; s2[i];i++)
        rst[j++] = s2[i];
    rst[j] = 0;
    return rst;
}

bool    only_tiret(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] != '-')
            return false;
    return true;
}