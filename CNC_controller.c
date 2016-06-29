//CNC_controller.c
#include "axis_controller/axis_controller.h"

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ivo Stratev (NoHomey)");
MODULE_DESCRIPTION("CNC Controller");

static int return_value;
static struct axis_controller test;

static enum hrtimer_restart my_callback(struct hrtimer *timer) {
  return axis_controller_change_state(&test);
}

static struct axis_controller test2;

static enum hrtimer_restart my_callback2(struct hrtimer *timer) {
  return axis_controller_change_state(&test2);
}

static int __init on_load(void) {
  printk("on_load\n");
  axis_controller_init(&test, my_callback);
  axis_controller_init(&test2, my_callback2);
  axis_controller_add_interval(&test, 0, 100000000);
  axis_controller_add_interval(&test, 1, 10000000);
  axis_controller_add_interval(&test, 0, 1000000);
  axis_controller_add_interval(&test, 1, 100000);
  axis_controller_add_interval(&test, 0, 10000);
  axis_controller_add_interval(&test, 2, 1000);
  axis_controller_add_interval(&test, 0, 100);
  axis_controller_add_interval(&test, 2, 10);
  axis_controller_add_interval(&test, 0, 1);
  axis_controller_add_interval(&test, 3, 10);
  axis_controller_add_interval(&test, 0, 100);
  axis_controller_add_interval(&test, 2, 1000);
  axis_controller_add_interval(&test, 0, 10000);
  axis_controller_add_interval(&test, 2, 100000);
  axis_controller_add_interval(&test, 0, 1000000);
  axis_controller_add_interval(&test, 1, 10000000);
  axis_controller_add_interval(&test, 0, 100000000);
  axis_controller_add_interval(&test2, 1, 100000000);
  axis_controller_add_interval(&test2, 0, 10000000);
  axis_controller_add_interval(&test2, 2, 1000000);
  axis_controller_add_interval(&test2, 0, 100000);
  axis_controller_add_interval(&test2, 2, 10000);
  axis_controller_add_interval(&test2, 0, 1000);
  axis_controller_add_interval(&test2, 3, 100);
  axis_controller_add_interval(&test2, 0, 10);
  axis_controller_add_interval(&test2, 2, 1);
  axis_controller_add_interval(&test2, 0, 10);
  axis_controller_add_interval(&test2, 2, 100);
  axis_controller_add_interval(&test2, 0, 1000);
  axis_controller_add_interval(&test2, 1, 10000);
  axis_controller_add_interval(&test2, 0, 100000);
  axis_controller_add_interval(&test2, 1, 1000000);
  axis_controller_add_interval(&test2, 0, 10000000);
  axis_controller_add_interval(&test2, 1, 100000000);
  axis_controller_controll(&test);
  axis_controller_controll(&test2);
  return 0;
}

static void on_unload(void) {
  printk("on_unload\n");
  return_value = axis_controller_clean(&test);
  if(return_value) {
    printk(KERN_INFO "Error from: axis_controller_clean(&test)\n");
  }
  return;
}

module_init(on_load);
module_exit(on_unload);