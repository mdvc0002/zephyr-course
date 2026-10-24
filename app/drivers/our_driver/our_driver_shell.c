#include <zephyr/shell/shell.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

#include <our_driver.h>

static const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

static int cmd_channel_fetch_handler(const struct shell *sh, int argc, char **argv){
    int ret;
    shell_info(sh, "Hello from fetch command");

    ret = sensor_sample_fetch_chan(driver, SENSOR_CHAN_AMBIENT_TEMP);
	if (ret < 0) {
		shell_error(sh, "fetch failed (%d)", ret);
		return ret;
	}
    shell_info(sh, "LED is ON");
    return 0;
}

static int cmd_channel_get_handler(const struct shell *sh, int argc, char **argv){
    struct sensor_value val;

    shell_info(sh, "Hello from get command");

    sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_print(sh, "Sensor value: %d.%06d", val.val1, val.val2);
    shell_info(sh, "LED is OFF");
    return 0;
}

static int cmd_channel_info_handler(const struct shell *sh, int argc, char **argv){
    shell_info(sh, "Hello from info command");
    shell_print(sh, "Device name: %s", driver->name);
    shell_print(sh, "Device ready: %s", device_is_ready(driver) ? "true" : "false");
    return 0;
}

static int cmd_channel_set_handler(const struct shell *sh, int argc, char **argv){
    
    shell_info(sh, "Hello from set command");
    shell_print(sh, "argc = %d, argv[1] = %s",
            argc, argv[1]);
    if(argc < 2){
        shell_error(sh, "Please provide a value to set");
        return -EINVAL;
    }else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 100){
        shell_error(sh, "Please provide a valid value (0-100)");
        return -EINVAL;
    }else{
        int value = atoi(argv[1]);
        int value1 = my_extension_api(driver); // Call the extension API
        
        shell_print(sh, "Setting value to: %d", value);
        shell_print(sh, "Current counter value: %d", value1);
    }
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(fetch, NULL, "Fetch channel of my/our driver", cmd_channel_fetch_handler, 1, 0),
    SHELL_CMD_ARG(read, NULL, "Get channel of my/our driver", cmd_channel_get_handler, 1, 0),
    SHELL_CMD_ARG(info, NULL, "Device name and ready state", cmd_channel_info_handler, 1, 0),
    SHELL_CMD_ARG(set, NULL, "Set value of my/our driver", cmd_channel_set_handler, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmd, "Our driver set of commands", NULL);