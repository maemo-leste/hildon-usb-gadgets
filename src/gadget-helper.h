#ifndef __GADGET_HELPER_H__
#define __GADGET_HELPER_H__
int gadget_init(void);
int gadget_destroy(void);
int remove_all_gadgets(void);

/* TODO: Make this nicer/better/composable/configurable */
int mass_storage_gadget(void);
int network_gadget(void);
#endif /* __GADGET_HELPER_H__ */
