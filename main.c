#include "main.h"

int main(int argc, char** argv)
{
    tr       struc = init_struct_tr();
    arg_opt     options = arg_init(argc, argv);
    
    init_options(&options, 'h', "help", BOOL);
    arg_start(&options);
    if (find_options(&options, "help"))
        struc.help = true;
    if ( struc.help == true)
        help_options();
    arg_end(options);
    return 0;
}