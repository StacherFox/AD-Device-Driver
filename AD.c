#include <linux/i2c.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>
#include <linux/module.h>

MODULE_AUTHOR("Cleisson Fernandes");
MODULE_DESCRIPTION("Device Driver AD");
//MODULE_LICENCE("GPL v2");

struct AD_info {
	int number;
};

struct AD_data {
	struct i2c_client *client;
	struct mutex lock;
	const struct AD_info *info;
};


static int AD_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int * val, int * val2, long mask)
{
	return 0;
};

static int AD_write_raw(struct iio_dev *indio_dev,
                        struct iio_chan_spec const *chan,
                        int val, int val2, long mask)
{
	return 0;
};

static const struct iio_info AD_info = {
	.read_raw = AD_read_raw,
	.write_raw = AD_write_raw,
};


static int AD_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct AD_data *data;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	
	printk(KERN_DEBUG "AD_probe");

	return 0;
};

static int AD_remove(struct i2c_client *client)
{
	return 0;
};

static const struct i2c_device_id AD_id[] = {
	{ "AD", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, AD_id);

static struct i2c_driver AD_driver ={
	.driver = {
		.name = "AD",
	},
	.probe = AD_probe,
	.remove = AD_remove,
	.id_table = AD_id,
};
//module_i2c_driver(AD_driver);

module_init(AD_probe);
//module_exit(AD_remove);
