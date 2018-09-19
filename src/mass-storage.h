#define VENDOR    0x1d6b
#define PRODUCT    0x0104

/* TODO: Rename */
/* TODO: Give sensible values */
/* TODO: Note libusbgx examples used */
static struct usbg_gadget_attrs g_attrs = {
    .bcdUSB = 0x0200,
    .bDeviceClass =    USB_CLASS_PER_INTERFACE,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = 64, /* Max allowed ep0 packet size */
    .idVendor = VENDOR,
    .idProduct = PRODUCT,
    .bcdDevice = 0x0001, /* Verson of device */
};

static struct usbg_gadget_strs g_strs = {
    .serial = "0123456789", /* Serial number */
    .manufacturer = "Foo Inc.", /* Manufacturer */
    .product = "Bar Gadget" /* Product string */
};

static struct usbg_f_ms_lun_attrs f_ms_luns_array[] = {
    {
        .id = -1, /* allows to place in any position */
        .cdrom = 0,
        .ro = 0,
        .nofua = 0,
        .removable = 1,
        .file = "/dev/mmcblk1",
    },
};

static struct usbg_f_ms_lun_attrs *f_ms_luns[] = {
    /*
     * When id in lun structure is below 0 we can place it in any
     * arbitrary position
     */
    &f_ms_luns_array[0],
    NULL,
};

static struct usbg_f_ms_attrs f_attrs = {
    .stall = 0,
    .nluns = 1,
    .luns = f_ms_luns,
};

static struct usbg_config_strs c_strs = {
        "1xMass Storage"
};

