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

static int __init on_load(void) {
  printk("on_load\n");
  axis_controller_init(&test, my_callback);
  axis_controller_add_interval(&test, 0, 100000000);
  axis_controller_add_interval(&test, 0, 10000000);
  axis_controller_add_interval(&test, 0, 1000000);
  axis_controller_add_interval(&test, 0, 100000);
  axis_controller_add_interval(&test, 0, 10000);
  axis_controller_add_interval(&test, 0, 1000);
  axis_controller_add_interval(&test, 0, 100);
  axis_controller_add_interval(&test, 0, 10);
  axis_controller_add_interval(&test, 0, 1);
  axis_controller_add_interval(&test, 0, 10);
  axis_controller_add_interval(&test, 0, 100);
  axis_controller_add_interval(&test, 0, 1000);
  axis_controller_add_interval(&test, 0, 10000);
  axis_controller_add_interval(&test, 0, 100000);
  axis_controller_add_interval(&test, 0, 1000000);
  axis_controller_add_interval(&test, 0, 10000000);
  axis_controller_add_interval(&test, 0, 100000000);
  axis_controller_controll(&test);
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