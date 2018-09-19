#include "gadget-helper.h"

/* TODO: Exit codes */

int main()
{
    gadget_init();

    remove_all_gadgets();
    mass_storage_gadget();

    return 0;
}
