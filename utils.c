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