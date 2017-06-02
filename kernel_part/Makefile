obj-m := simple.o
KERNELDIR ?= /lib/modules/`uname -r`/build
PWD := $(shell pwd)
modules:
		make -C $(KERNELDIR) M=$(PWD) modules
modules_install:
		make -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *~ core .depend  .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order