obj-m = virtual_device1.o
TARGET = virtual_device_app1

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default : ${TARGET}
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
CC := /usr/bin/gcc
%.c%:
	${CC} -o $@ $^
clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf *.*.cmd
	rm -rf *.o
	
