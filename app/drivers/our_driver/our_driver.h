#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#include "zephyr/device.h"

//Struct to define the dynamic data of our_driver
struct our_driver_data{
    int counter;
};

#ifdef __cplusplus
extern "C" {
#endif

int my_extension_api(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif /* OUR_DRIVER_H */