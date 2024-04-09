#include "argparse.h"

arg_opt arg_init(int argc, char **argv)
{
    arg_opt new;
    new.options = NULL;
    new.nb_options = 0;
    new.arg = malloc(argc * sizeof(char *));
    int i = 0;
    for(int j = 1; j < argc; j++)
        new.arg[i++] = ft_strdup(argv[j]);
    new.arg[i] = 0;
    new.nb_arg = argc - 1;
    new.clean_arg = NULL;
    return new;
}


void    arg_start(arg_opt *tab)
{
    for(int i = 0; tab->arg[i]; i++)
    {
        int valid = 0;
        if (tab->arg[i][0] == '-' && (tab->arg[i][1] == '-' || ft_isalpha(tab->arg[i][1]) > 0 || tab->arg[i][1] == '?'))
            multiple_definition(tab, i, &valid);
        if (valid == 1)
        {

            printf("Unknown flag : '%s'\n", tab->arg[i]);
            arg_end(*tab);
        }
    }
    tab->clean_arg = arg_without_opt(tab->arg, tab);
}

void	arg_end(arg_opt tab)
{
    for (int i = 0; i < tab.nb_options; i++)
    {
        free(tab.options[i].opt);
        free(tab.options[i].fullname_opt);
    }
    free(tab.options);
    for(int i = 0; tab.arg[i]; i++)
        free(tab.arg[i]);
    if (tab.clean_arg != NULL)
        free(tab.clean_arg);
    free(tab.arg);
    exit(0);
}
