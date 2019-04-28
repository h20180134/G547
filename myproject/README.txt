Linux kernel driver for BH1750 sensor
########################################################

This is kernel driver for BH1750 Ambient light
sensor along with a module for instantiating i2c.

Raspberry Pi how-to
########################################################
$ sudo apt-get install raspberrypi-kernel-headers

*Build
#####################
$ make all
$ sudo make install 
$ sudo depmod -a
$ sudo insmod i2c.ko

NOTE: 1. Kernel versions above 3.16 i2c should be enabled
through raspi-config -> advanced 
 
$ sudo nano /etc/modules 
Add lines as follow
sensor
i2c

*Test:
######################
$ sudo modprobe sensor
$ cat /sys/bus/iio/devices/iio:device0/in_illuminance_raw

##########################################################