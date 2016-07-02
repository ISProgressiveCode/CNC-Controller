//CNC_controller.c
#include "axis_controller.h"

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
  axis_controller_init(&test, 1, 1000000, my_callback);
  printk("adding dir: %d\n", axis_controller_add_dir_change(&test, 3));
  printk("adding dir: %d\n", axis_controller_add_dir_change(&test, 2));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
  printk("adding pulse: %d\n", axis_controller_add_pulse_change(&test, 10));
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