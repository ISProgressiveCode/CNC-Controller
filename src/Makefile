#Makefile
__name__ = cnc_controller
__major__ = 243
__ioctl_header__ = /usr/include/$(__name__)_ioctl.h
make_module_action = make -C /lib/modules/$(shell uname -r)/build M=$(PWD)
obj-m := $(__name__).o

all: clean
	$(make_module_action) modules

clean:
	$(make_module_action) clean

load:
	dmesg -c
	clear
	insmod $(__name__).ko

unload:
	rmmod -f $(__name__)

device:
	mknod /dev/$(__name__) c $(__major__) 0
	chmod 777 /dev/$(__name__)

remove:
	rm -f /dev/$(__name__)

header:
	rm -f $(__ioctl_header__)
	cp $(__name__).h $(__ioctl_header__)
	chmod 555 $(__ioctl_header__)