#include "zephyr/device.h"
#include "zephyr/drivers/sensor.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "our_driver.h"

/* The devicetree node identifier for the "led0" alias. */
//#define LED_NODE DT_ALIAS(app_led)

//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
    void test(){
        const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        auto ret1 = sensor_sample_fetch_chan(driver, SENSOR_CHAN_AMBIENT_TEMP);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        auto ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        
        while (1) {
        auto ret2 = my_extension_api(driver);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        //LOG_INF("Counter: %d", ret2);
        }
    }
}
int main(void)
{
    test();
    /*bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }*/
    return 0;
}
