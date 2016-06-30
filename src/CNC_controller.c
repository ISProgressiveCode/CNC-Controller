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

static struct axis_controller test2;

static enum hrtimer_restart my_callback2(struct hrtimer *timer) {
  return axis_controller_change_state(&test2);
}

static struct axis_controller test3;

static enum hrtimer_restart my_callback3(struct hrtimer *timer) {
  return axis_controller_change_state(&test3);
}

static struct axis_controller test4;

static enum hrtimer_restart my_callback4(struct hrtimer *timer) {
  return axis_controller_change_state(&test4);
}

static struct axis_controller test5;

static enum hrtimer_restart my_callback5(struct hrtimer *timer) {
  return axis_controller_change_state(&test5);
}

static struct axis_controller test6;

static enum hrtimer_restart my_callback6(struct hrtimer *timer) {
  return axis_controller_change_state(&test6);
}

static struct axis_controller test7;

static enum hrtimer_restart my_callback7(struct hrtimer *timer) {
  return axis_controller_change_state(&test7);
}

static struct axis_controller test8;

static enum hrtimer_restart my_callback8(struct hrtimer *timer) {
  return axis_controller_change_state(&test8);
}

static struct axis_controller test9;

static enum hrtimer_restart my_callback9(struct hrtimer *timer) {
  return axis_controller_change_state(&test9);
}

static struct axis_controller test10;

static enum hrtimer_restart my_callback10(struct hrtimer *timer) {
  return axis_controller_change_state(&test10);
}

static int __init on_load(void) {
  printk("on_load\n");

  axis_controller_init(&test, my_callback);
  axis_controller_init(&test2, my_callback2);
  axis_controller_init(&test3, my_callback3);
  axis_controller_init(&test4, my_callback4);
  axis_controller_init(&test5, my_callback5);
  axis_controller_init(&test6, my_callback6);
  axis_controller_init(&test7, my_callback7);
  axis_controller_init(&test8, my_callback8);
  axis_controller_init(&test9, my_callback9);
  axis_controller_init(&test10, my_callback10);

  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);
  axis_controller_add_interval(&test, 0, 2);

  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);
  axis_controller_add_interval(&test2, 0, 2);

  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);
  axis_controller_add_interval(&test3, 0, 2);

  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);
  axis_controller_add_interval(&test4, 0, 2);

  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);
  axis_controller_add_interval(&test5, 0, 2);

  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);
  axis_controller_add_interval(&test6, 0, 2);

  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);
  axis_controller_add_interval(&test7, 0, 2);

  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);
  axis_controller_add_interval(&test8, 0, 2);

  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);
  axis_controller_add_interval(&test9, 0, 2);

  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);
  axis_controller_add_interval(&test10, 0, 2);

  axis_controller_controll(&test);
  axis_controller_controll(&test2);
  axis_controller_controll(&test3);
  axis_controller_controll(&test4);
  axis_controller_controll(&test5);
  axis_controller_controll(&test6);
  axis_controller_controll(&test7);
  axis_controller_controll(&test8);
  axis_controller_controll(&test9);
  axis_controller_controll(&test10);

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