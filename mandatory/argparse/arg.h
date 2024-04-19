#ifndef ARG_H
# define ARG_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BOOL 0
#define INT 1
#define CHAR 2
#define FLOAT 3

typedef struct  arg_opt
{
    struct options  *options;
    int             nb_options;
    char            **arg;
    int             nb_arg;
    char            **clean_arg;
}   arg_opt;

typedef struct  options
{
    char    *opt;
    char    *fullname_opt;
    int     type;
    bool    is_here;
}   options;

arg_opt arg_init(int argc, char **argv);
bool    init_options(arg_opt *tab, char opt, char *fullname_opt, int type);


void    arg_start(arg_opt *tab);
void    *find_options(arg_opt *tab, char *opt);


void	arg_end(arg_opt tab);

#endif