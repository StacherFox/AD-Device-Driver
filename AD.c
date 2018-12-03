#include <linux/i2c.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>
#include <linux/module.h>

MODULE_AUTHOR("Cleisson Fernandes");
MODULE_DESCRIPTION("Device Driver AD");
MODULE_LICENSE("GPL v2");

#define SCALE 4822 // in uV/raw

struct AD_data {
	struct i2c_client *client;
	int scale;
	const struct AD_informations *informations;
}; 

static int AD_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int * val, int * val2, long mask)
{
	int ret;
	struct AD_data *data = iio_priv(indio_dev);
	int raw = 0;
	char buffer[4];

	switch (mask) {
		case IIO_CHAN_INFO_RAW:
			switch (chan->channel) {
				case 0:
					ret = i2c_master_recv(data->client, buffer, sizeof(buffer));
					if (ret < 0)
						return ret;
					
					raw = buffer[0];
					raw = (raw << 8) | buffer[1];
					*val = raw;
				break;

				case 1:
					ret = i2c_master_recv(data->client, buffer, sizeof(buffer));
					if (ret < 0)
						return ret;
					
					raw = buffer[2];
					raw = (raw << 8) | buffer[3];
					*val = raw;
				break;

			}
		break;

		case IIO_CHAN_INFO_SCALE:

		*val = (data->scale)/1000;
		*val2 = ((data->scale)%1000)*1000;
		return IIO_VAL_INT_PLUS_MICRO;

		break;
	}

	printk(KERN_INFO "AD_read_raw\n");
	return IIO_VAL_INT;
};

static int AD_write_raw(struct iio_dev *indio_dev,
                        struct iio_chan_spec const *chan,
                        int val, int val2, long mask)
{
	printk(KERN_INFO "AD_write_raw\n");
	return 0;
};

static const struct iio_chan_spec AD_channels[] = {
	{
	    .type = IIO_VOLTAGE,
	    .indexed = 1,         
	    .channel = 0,
	    .info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE)
	},
	{
	    .type = IIO_VOLTAGE,
	    .indexed = 1,         
	    .channel = 1,
	    .info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE)
	},
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

	printk(KERN_INFO "AD_probe\n");

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->scale = SCALE;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &AD_info;
	indio_dev->name = id->name;
	indio_dev->channels = AD_channels;
	indio_dev->num_channels = ARRAY_SIZE(AD_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;
	
	return iio_device_register(indio_dev);
};

static int AD_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev;

	printk(KERN_INFO "AD_remove\n");

	indio_dev = i2c_get_clientdata(client);

	iio_device_unregister(indio_dev);

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
module_i2c_driver(AD_driver);

