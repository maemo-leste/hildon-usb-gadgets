#include "gadget-helper.h"

/* TODO: Exit codes */

int main()
{
    gadget_init();

    remove_all_gadgets();
    network_gadget();

    return 0;
}
