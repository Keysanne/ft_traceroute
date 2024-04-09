#include "main.h"

int main(int argc, char** argv)
{
    tr       struc = init_struct_tr();
    arg_opt     options = arg_init(argc, argv);
    
    init_options(&options, '?', "help", BOOL);
    arg_start(&options);
    struc.help = find_options(&options, "help");
    if ((bool)struc.help == true)
    {
        help_options(options);
        free(struc.help);
        arg_end(options);
    }
    arg_end(options);
    return 0;
}