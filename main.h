#ifndef MAIN_H
# define MAIN_H

#include "argparse/arg.h"

typedef struct  tr
{
    void*    help;
}               tr;

tr      init_struct_tr();
void    help_options();

#endif