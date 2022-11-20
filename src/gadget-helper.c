#include <errno.h>
#include <stdio.h>

#include <linux/usb/ch9.h>

#include <usbg/usbg.h>
#include <usbg/function/ms.h>

#include "gadget-helper.h"

#define LUGX_CALL(c) \
{ \
    int usbg_ret; \
    usbg_ret = c; \
    if (usbg_ret != USBG_SUCCESS) { \
        fprintf(stderr, "In: %s (Function: %s)\n", #c, __func__); \
        fprintf(stderr, "Error: %s : %s\n", usbg_error_name(usbg_ret), \
                usbg_strerror(usbg_ret)); \
        return usbg_ret; \
    } \
}

static usbg_state *state = NULL;

/* Templates */
#include "mass-storage.h"

int network_gadget(void) {
    usbg_gadget *g;
    usbg_function *f_rndis;
    usbg_config *c;

    /* TODO: Proper values for identifiers and names */
    /* TODO: Test macro fail path */
    /* TODO: Support multiple templates ? */
    /* TODO: Nokia pid/vid */
    /* TODO: g_attrs is currently shared */
    LUGX_CALL(usbg_create_gadget(state, "g1", &g_attrs, &g_strs, &g));
    LUGX_CALL(usbg_create_function(g, USBG_F_RNDIS, "usb0", NULL, &f_rndis));
    LUGX_CALL(usbg_create_config(g, 1, "The only one", NULL, &c_strs, &c));
    LUGX_CALL(usbg_add_config_function(c, "some_name_here", f_rndis));
    LUGX_CALL(usbg_enable_gadget(g, DEFAULT_UDC));

    return 0;
}

int mass_storage_gadget(void) {
    usbg_gadget *g;
    usbg_function *f_ms;
    usbg_config *c;

    /* TODO: Proper values for identifiers and names */
    /* TODO: Test macro fail path */
    /* TODO: Support multiple templates ? */
    /* TODO: Nokia pid/vid */
    LUGX_CALL(usbg_create_gadget(state, "g1", &g_attrs, &g_strs, &g));
    LUGX_CALL(usbg_create_function(g, USBG_F_MASS_STORAGE, "my_reader",
                    &f_attrs, &f_ms));
    LUGX_CALL(usbg_create_config(g, 1, "The only one", NULL, &c_strs, &c));
    LUGX_CALL(usbg_add_config_function(c, "some_name_here", f_ms));
    LUGX_CALL(usbg_enable_gadget(g, DEFAULT_UDC));

    return 0;
}

/* TODO: Function(s) to get current active gadget */

int remove_gadget(usbg_gadget *g) {
    usbg_udc *u;

    u = usbg_get_gadget_udc(g);
    if (u)
        LUGX_CALL(usbg_disable_gadget(g));

    LUGX_CALL(usbg_rm_gadget(g, USBG_RM_RECURSE));

    return 0;
}

int remove_all_gadgets(void) {
    usbg_gadget *g;

    g = usbg_get_first_gadget(state);
    while (g != NULL) {
        usbg_gadget *next = usbg_get_next_gadget(g);
        LUGX_CALL(remove_gadget(g));
        g = next;
    }

    return 0;
}

int gadget_init(void)
{
    LUGX_CALL(usbg_init("/sys/kernel/config", &state));

    return 0;
}

int gadget_destroy(void) {
    /* TODO */
    return 0;
}
