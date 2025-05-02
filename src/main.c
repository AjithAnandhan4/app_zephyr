/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <stdio.h>
 #include <zephyr/kernel.h>
 #include <zephyr/drivers/gpio.h>
 
 /* 1000 msec = 1 sec */
 #define SLEEP_TIME_MS   500
 
 /* The devicetree node identifiers for the LEDs */
 #define LED0_NODE DT_ALIAS(led0)
 #define LED1_NODE DT_ALIAS(led1)
 
 static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
 static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
 
 int main(void)
 {
     int ret;
     bool led0_state = true;
     bool led1_state = false;
 
     /* Initialize LED0 (LD4) */
     if (!gpio_is_ready_dt(&led0)) {
         printf("Error: LED0 not ready\n");
         return 0;
     }
     ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
     if (ret < 0) {
         printf("Error: LED0 config failed: %d\n", ret);
         return 0;
     }
 
     /* Initialize LED1 (LD3) */
     if (!gpio_is_ready_dt(&led1)) {
         printf("Error: LED1 not ready\n");
         return 0;
     }
     ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
     if (ret < 0) {
         printf("Error: LED1 config failed: %d\n", ret);
         return 0;
     }
 
     while (1) {
         /* Toggle LED0 */
         ret = gpio_pin_set_dt(&led0, led0_state);
         if (ret < 0) {
             printf("Error: LED0 set failed: %d\n", ret);
             return 0;
         }
 
         /* Toggle LED1 (opposite state) */
         ret = gpio_pin_set_dt(&led1, led1_state);
         if (ret < 0) {
             printf("Error: LED1 set failed: %d\n", ret);
             return 0;
         }
 
         led0_state = !led0_state;
         led1_state = !led1_state;
         printf("LED0: %s, LED1: %s\n", led0_state ? "ON" : "OFF", led1_state ? "ON" : "OFF");
         k_msleep(SLEEP_TIME_MS);
     }
     return 0;
 }