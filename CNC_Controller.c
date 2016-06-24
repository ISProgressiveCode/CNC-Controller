#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ivo Stratev (NoHomey)");
MODULE_DESCRIPTION("CNC Controller");

static struct hrtimer hr_timer;

enum hrtimer_restart my_hrtimer_callback(struct hrtimer *timer) {
  printk("my_hrtimer_callback called\n");
  return HRTIMER_NORESTART;
}

int __init on_load(void) {
  printk("HR Timer module installing\n");
  hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  hr_timer.function = &my_hrtimer_callback;
  hrtimer_start(&hr_timer, ktime_set(0, 1000), HRTIMER_MODE_REL);
  return 0;
}

void on_unload(void) {
  if(hrtimer_cancel(&hr_timer)) {
    printk("The timer was still in use...\n");
  }
  printk("HR Timer module uninstalling\n");
  return;
}

module_init(on_load);
module_exit(on_unload);