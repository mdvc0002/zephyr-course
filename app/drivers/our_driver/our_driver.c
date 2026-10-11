#include "zephyr/device.h"
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <errno.h>

#define DT_DRV_COMPAT our_driver

#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static int channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val){
    LOG_INF("Hello From Channel Get, channel %d", chan);
    //return 0;
    return gpio_pin_set_dt(&led, 0);
}
static int sample_fetch_my_impl(const struct device *dev,
				     enum sensor_channel chan){
    LOG_INF("Hello From Sample Fetch, channel %d", chan);
    //return 0;
    return gpio_pin_set_dt(&led, 1);
}

static DEVICE_API(sensor, api_iomico_lecture) = {
    .channel_get = channel_get_my_impl,
    .sample_fetch = sample_fetch_my_impl,
};

// Init fn
static int init(const struct device *dev){
   LOG_INF("Device Initialized!"); 
    
   if (!gpio_is_ready_dt(&led)) {
        return -ENODEV;
    }

    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    //return 0;
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);

