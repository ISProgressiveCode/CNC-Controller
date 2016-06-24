__name__ = CNC_Controller
__major__ = 243
obj-m := $(__name__).o


all: clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load:
	insmod $(__name__).ko

unload:
	rmmod -f $(__name__)

device:
	mknod /dev/$(__name__) c $(__major__) 0
	chmod 777 /dev/$(__name__)

remove:
	rm -f /dev/$(__name__)

header:
	rm -f /usr/include/$(__name__)_ioctl.h
	cp $(__name__).h /usr/include/$(__name__)_ioctl.h
	chmod 555 /usr/include/$(__name__)_ioctl.h