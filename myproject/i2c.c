// Kernel module to i2c device by bus id.
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/i2c.h>

/*bh1750 probing addreses */
static const unsigned short probe_i2c_addrs[] = I2C_ADDRS(0x23, 0x5c);
//   7-bit I2C slave addresses:
//   0x23 (ADDR pin low)
//   0x5C (ADDR pin high)
static struct i2c_board_info bh1750_i2c_info[] = {

	{ I2C_BOARD_INFO("bh1750", 0x23), }
};

static int __init bh1750_probe_init(void)
{
	int nr;
	printk(KERN_ALERT "%s probing bus\n",__FUNCTION__);
	for(nr =0; nr < 4; nr++) {
		struct i2c_adapter * adap = i2c_get_adapter(nr);
		//To that i2c_adapter it will probe the new device.
		if(adap) {
			i2c_new_probed_device(adap, bh1750_i2c_info, probe_i2c_addrs, NULL);
		}
	}

	return 0;
}

static void __exit bh1750_probe_exit(void)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
}

module_init(bh1750_probe_init);
module_exit(bh1750_probe_exit);

MODULE_AUTHOR("Owner");
MODULE_DESCRIPTION("I2C Instantiation");
MODULE_LICENSE("GPL");