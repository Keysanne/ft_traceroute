#include "argparse.h"

void    *value(int j, int type, arg_opt *options)
{
    switch(type)
    {
        case BOOL:;
             bool *x = malloc(sizeof(bool));
            *x = true;
            return x;
        case CHAR:;
            char    *y = ft_strdup(options->arg[j + 1]);
            return y;
        case INT:;
            int *z = malloc(sizeof(int));
            *z = ft_atoi(options->arg[j + 1]);
            return z;                  
        case FLOAT:;
            float *a = malloc(sizeof(int));
            *a = atof(options->arg[j + 1]);
            return a;
    }
    return NULL;
}

void    *find_options(arg_opt *tab, char *fullname_opt)
{
    int i;
    char *tmp = ft_strjoin("--", fullname_opt);
    for(i = 0; i < tab->nb_options; i++)
    {
        if(ft_strcmp(tab->options[i].fullname_opt, tmp) == 0)
            break ;
    }
    free(tmp);
    if(i == tab->nb_options)
        return NULL;
    int j;
    if (tab->options[i].is_here == true)
    {
        for(j = 0; tab->arg[j]; j++)
        {
            if(ft_strcmp(tab->arg[j], tab->options[i].opt) == 0 || ft_strcmp(tab->arg[j], tab->options[i].fullname_opt) == 0)
                return value(j, tab->options[i].type, tab);
            else if(multiple_flags(tab->options[i], tab->arg[j], tab))
                return value(j, tab->options[i].type, tab);
        }
    }
    return NULL;
}

bool    multiple_flags(options opt, char *arg, arg_opt *tab)
{
    if (arg[0] != '-')
        return false;
    if (opt.type == BOOL)
    {
        for (int i = 1; arg[i]; i++)
        {
            if(arg[i] == opt.opt[1])
                return true;
        }
    }
    else
    {
        int i;
        for (i = 1; arg[i]; i++)
        {
            if(arg[i] == opt.opt[1] && arg[i + 1] == opt.opt[2])
                return true;
        }
    }
    return false;
}

void    already_defined(char opt, char *fullname, arg_opt *tab)
{
    for(int i = 0; i < tab->nb_options; i++)
    {
        if (opt == tab->options[i].opt[1])
        {
            printf("Another options already have this name : %c\n", opt);
            arg_end(*tab);
        }
        else if (ft_strcmp(fullname, &(tab->options[i].fullname_opt[2])) == 0)
        {
            printf("Another options already have this fullname : %s\n", fullname);
            arg_end(*tab);
        }
    }
}

bool    add_to_options(arg_opt *tab, options opt)
{
    tab->options = realloc_struc(tab->options, tab->nb_options);
    if (tab->options == NULL)
        return false;
    tab->options[tab->nb_options] = opt;
    tab->nb_options += 1;
    return true;
}

bool init_options(arg_opt *tab, char opt, char *fullname_opt, int type)
{
    options new;
    if (ft_isalpha(opt) == 0 && opt != '?')
        return false;
    already_defined(opt, fullname_opt, tab);
    if (type != BOOL && type != INT && type != CHAR && type != FLOAT)
        return false;
    new.type = type;
    char    *op = to_str(opt);
    new.opt = ft_strjoin("-", op);
    free(op);
    if (fullname_opt != NULL)
        new.fullname_opt = ft_strjoin("--", fullname_opt);
    new.is_here = false;
    if (!add_to_options(tab, new))
        return false;
    return true;
}
