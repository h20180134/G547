Block Device Driver

>Download the main.c and Makefile

>Go to the directory in which code is downloaded and give the command $ make all

>insert the module using command sudo insmod main.ko

>Check the partition info using command sudo fdisk -l

>we have created 2 primary partitions of the Device as /dev/mydisk1 and /dev/mydisk2

>Take root access using command sudo -s

>To write into disk use command cat > /dev/mydisk1 or cat > /dev/mydisk2 , type something (ctrl+c to exit)

>To read back from the disk on command line use command xxd /dev/mydisk1 | less or xxd /dev/mydisk2 | less (ctrl+z to exit)

>To check MBR details (MBR signature will be seen in last column as 55aa) use command xxd /dev/mydisk | less
(ctrl+z to exit) 

>Remove the module using sudo rmmod main.ko



