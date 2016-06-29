//CNC_controller.c
#include "axis_controller/axis_controller.h"

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ivo Stratev (NoHomey)");
MODULE_DESCRIPTION("CNC Controller");

static int return_value;
static struct axis_controller test;

static enum hrtimer_restart my_callback(struct hrtimer *timer) {
  printk("my_hrtimer_callback called\n");
  return HRTIMER_NORESTART;
}

static int __init on_load(void) {
  printk("on_load\n");
  axis_controller_init(&test, my_callback);

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