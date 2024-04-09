#ifndef MAIN_H
# define MAIN_H

#include "argparse_C/arg.h"

typedef struct  tr
{
    bool    help;
}               tr;

tr      init_struct_tr();
void    help_options();

#endif