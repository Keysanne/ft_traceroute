#include "argparse.h"

bool    next_arg_valid(char *arg, int type)
{
    if (type == CHAR)
    {
        if (valid_str(arg))
            return true;
    }
    else if (type == INT)
    {
        if(valid_int(arg))
        {
            char *verif = malloc(12);
            sprintf(verif, "%d", ft_atoi(arg));
            if(ft_strcmp(verif, arg) == 0)
            {
                free(verif);
                return true;
            }
        }
    }
    else if (type == FLOAT)
    {
         if(valid_float(arg))
            return true;
    }
    return false;
}

void    option_with_arg_check(char *next_arg, options opt, arg_opt tab)
{
    if (opt.type != BOOL)
    {
        if (!next_arg)
        {
            printf("You need to add an argument with : %s/%s\n", opt.opt, opt.fullname_opt);
            arg_end(tab);
        }
        if (!next_arg_valid(next_arg, opt.type))
        {
            printf("Invalid argument with : %s/%s\n", opt.opt, opt.fullname_opt);
            arg_end(tab);
        }
    }
}

bool    is_multiple_flags(char **arg, int x, arg_opt tab)
{
    if(arg[x][1] == '-')
        return false;
    int i, j;
    for (j = 1; arg[x][j]; j++)
    {
        for (i = 0; i < tab.nb_options; i++)
        {
            if (arg[x][j] == tab.options[i].opt[1])
                break;
        }
        if (i == tab.nb_options)
        {
            printf("Unknown flag : '%c'\n", arg[x][j]);
            arg_end(tab);
        }
        if (tab.options[i].type != BOOL)
        {
            if (arg[x][j + 1] != '\0')
            {
                printf("invalid use of : '%s'\n", tab.options[i].opt);
                arg_end(tab);
            }
            option_with_arg_check(arg[x + 1], tab.options[i], tab);
        }
        tab.options[i].is_here = true;
    } 
    return true;
}

void    multiple_definition(arg_opt *tab, int i, int *valid)
{
    if (tab->arg[i][1] == '-')
    {
        int j;
        for(j = 0; j < tab->nb_options; j++)
        {
            if (ft_strcmp(tab->arg[i], tab->options[j].fullname_opt) == 0)
                break ;
        }
        if(j == tab->nb_options)
            (valid)++;
        if (tab->options[j].is_here == false)
        {
            option_with_arg_check(tab->arg[i + 1], tab->options[j], *tab);
            tab->options[j].is_here = true;
        }
        else
        {
            if (tab->options[j].type != BOOL)
            {
                printf("Mulitple definition of the option : %s/%s\n", tab->options[j].opt, tab->options[j].fullname_opt);
                arg_end(*tab);
            }
        }
    }
    else
    {
        int j;
        for(j = 0; j < tab->nb_options; j++)
        {
            if (ft_strcmp(tab->arg[i], tab->options[j].opt) == 0)
                break ;
        }
        if(j == tab->nb_options)
        {
            if (is_multiple_flags(tab->arg, i, *tab))
                return;
            (valid)++;
        }
        if (tab->options[j].is_here == false)
        {
            option_with_arg_check(tab->arg[i + 1], tab->options[j], *tab);
            tab->options[j].is_here = true;
        }
        else
        {
            if (tab->options[j].type != BOOL)
            {
                printf("Multiple definition of the option : %s/%s\n", tab->options[j].opt, tab->options[j].fullname_opt);
                arg_end(*tab);
            }
        }
    }
}

bool    not_an_option_arg(char **arg, int i, arg_opt *tab)
{
    if(i == 0)
        return true;
    i--;
    if (arg[i][0] == '-')
    {
        int j;
        for (j = 0; j < tab->nb_options; j++)
        {
            int x = ft_strlen(arg[i]);
            if (arg[i][x - 1] == tab->options[j].opt[1])
                    break;
        }
        if (tab->options[j].type != BOOL)
            return false;
    }
    return true;
}

char    **arg_without_opt(char **arg, arg_opt *tab)
{
    int j = 0, size = 1;
    char    **rst = malloc(size * sizeof(char*));
    size++;
    for(int i = 0; arg[i]; i++)
    {
        if (arg[i][0] != '-')
        {
            if (not_an_option_arg(arg, i, tab))
            {
                rst = realloc_char(rst, (sizeof(char*) * size));
                rst[j++] = arg[i];
                size++;
            }
        }
    }
    rst[j] = 0;
    return rst;
}