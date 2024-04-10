#ifndef MAIN_H
# define MAIN_H

#include "argparse/arg.h"

typedef struct  tr
{
    void*   help;
    char*   arg;
}               tr;

tr      init_struct_tr();
char*   get_arg(char **arg);
void    help_options(arg_opt options, void* help);

#endif