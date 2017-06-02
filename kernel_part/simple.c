#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/uio_driver.h>
#include <linux/slab.h>
/*
test uio driver kernel part
*/
struct uio_info kpart_info = {
    .name = "kpart",
    .version = "0.1",
    .irq = UIO_IRQ_NONE,
};

static int drv_kpart_probe(struct device *dev);
static int drv_kpart_remove(struct device *dev);
static struct device_driver uio_dummy_driver = {
    .name = "kpart",
    .bus = &platform_bus_type,
    .probe = drv_kpart_probe,
    .remove = drv_kpart_remove,
};

static int drv_kpart_probe(struct device *dev){
    printk("drv_kpart_probe( %p)\n", dev);
    kpart_info.mem[0].addr = (unsigned long)kmalloc(1024,GFP_KERNEL);//alloc memory for device from kernel and set head address

    if(kpart_info.mem[0].addr==0)//memory alloc fail
        return -ENOMEM;
    kpart_info.mem[0].memtype = UIO_MEM_LOGICAL;//set mem type
    kpart_info.mem[0].size = 1024;//set mem size

    if( uio_register_device(dev, &kpart_info) )//register device
        return -ENODEV;
    return 0;
}

static int drv_kpart_remove(struct device *dev){
    uio_unregister_device(&kpart_info);
    return 0;
}

static struct platform_device * uio_dummy_device;

static int __init uio_kpart_init(void){
    uio_dummy_device = platform_device_register_simple("kpart", -1, NULL, 0);
    return driver_register(&uio_dummy_driver);
}

static void __exit uio_kpart_exit(void){
    platform_device_unregister(uio_dummy_device);
    driver_unregister(&uio_dummy_driver);
}

module_init(uio_kpart_init);
module_exit(uio_kpart_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("permission");
MODULE_DESCRIPTION("test uio dummy dirver");


