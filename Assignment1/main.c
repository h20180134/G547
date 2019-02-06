#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include <linux/types.h>
#include <linux/random.h>
#include <linux/uaccess.h>

static dev_t first;
dev_t x;
dev_t y;
dev_t z;
int major,minor;


static struct cdev xc_dev;
static struct cdev yc_dev;
static struct cdev zc_dev;

static struct class *cls;

uint16_t val;

static int permission(struct device* dev,struct kobj_uevent_env* env)
{
  add_uevent_var(env,"DEVMODE=%#o",0666);
  return 0;
}

static int x_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "x_axis: open()\n");
	return 0;
}
static int x_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "x_axis: close()\n");
	return 0;
}
static ssize_t x_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{

	uint16_t rand;
	get_random_bytes(&rand, sizeof(rand));
	val=rand&0x03FF;
	copy_to_user(buf,&val,sizeof(rand));

	printk(KERN_INFO "x_axis: read()\n");
    	return 0;

}


static int y_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "y_axis: open()\n");
	return 0;
}
static int y_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "y_axis: close()\n");
	return 0;
}
static ssize_t y_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	
	uint16_t rand;
	get_random_bytes(&rand, sizeof(rand));
	val=rand&0x03FF;
	copy_to_user(buf,&val,sizeof(rand));

	printk(KERN_INFO "y_axis: read()\n");
    	return 0;
}


static int z_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "z_axis: open()\n");
	return 0;
}
static int z_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "z_axis: close()\n");
	return 0;
}
static ssize_t z_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	
	uint16_t rand;
	get_random_bytes(&rand, sizeof(rand));
	val=rand&0x03FF;
	copy_to_user(buf,&val,sizeof(rand));

	printk(KERN_INFO "z_axis: read()\n");
    	return 0;
}


static struct file_operations xops =
				{
					.owner = THIS_MODULE,
					.open = x_open,
					.release = x_close,
					.read = x_read
				};

static struct file_operations yops =
				{
					.owner = THIS_MODULE,
					.open = y_open,
					.release = y_close,
					.read = y_read
				};
static struct file_operations zops =
				{
					.owner = THIS_MODULE,
					.open = z_open,
					.release = z_close,
					.read = z_read
				};


static __init int accel_init(void)
{
	printk(KERN_INFO "Accelerometer Registered");



	//step 1: reserve <major, minor>
	if ((alloc_chrdev_region(&first, 0, 3, "Accelerometer")) < 0)
	{
		return -1;
	}

	major=MAJOR(first);
	minor=MINOR(first);
	x=MKDEV(major,minor);
	y=MKDEV(major,minor+1);
	z=MKDEV(major,minor+2);

	//step 2: creation of device file
	if ((cls=class_create(THIS_MODULE, "accelerometer"))==NULL)
	{
		unregister_chrdev_region(first,3);
		return -1;
	}

	cls->dev_uevent = permission;

	if((device_create(cls, NULL, x, NULL, "adxl_x"))==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}
	if((device_create(cls, NULL, y, NULL, "adxl_y"))==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}
	if((device_create(cls, NULL, z, NULL, "adxl_z"))==NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}

	//step 3: link fops and cdev to device node
	cdev_init(&xc_dev, &xops);
	if(cdev_add(&xc_dev, x, 1)== -1)
	{
		device_destroy(cls, x);
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}
	cdev_init(&yc_dev, &yops);
	if(cdev_add(&yc_dev, y, 1)== -1)
	{
		device_destroy(cls, x);
		device_destroy(cls, y);
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}
	cdev_init(&zc_dev, &zops);
	if(cdev_add(&zc_dev, z, 1)== -1)
	{
		device_destroy(cls, x);
		device_destroy(cls, y);
		device_destroy(cls, z);
		class_destroy(cls);
		unregister_chrdev_region(first,3);
		return -1;
	}

	return 0;
}

static __exit void accel_exit(void)
{
	
	cdev_del(&xc_dev);
	cdev_del(&yc_dev);
	cdev_del(&zc_dev);
	device_destroy(cls, x);
	device_destroy(cls, y);
	device_destroy(cls, z);
	class_destroy(cls);
	unregister_chrdev_region(first,3);
	printk(KERN_INFO "Accelerometer unregistered\n\n");
	
}

module_init(accel_init);
module_exit(accel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sukrut Tamhankar");

