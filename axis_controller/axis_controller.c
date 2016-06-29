//axis_controller.c
#include "axis_controller.h"

MODULE_LICENSE("GPL v2");

struct hrtimer* __axis_controller_get_timer(struct axis_controller* axis_controller) {
    return &(axis_controller->timer);
}

struct time_interval* axis_controller_get_interval(struct axis_controller* axis_controller) {
    return &(axis_controller->interval);
}

void __axis_controller_reset_state(struct axis_controller* axis_controller) {
    axis_controller->state = 0;
}

void axis_controller_init(struct axis_controller* axis_controller, enum hrtimer_restart (*function)(struct hrtimer *)) {
    hrtimer_init(__axis_controller_get_timer(axis_controller), CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    axis_controller->timer.function = function;
    time_interval_init(axis_controller_get_interval(axis_controller));
    __axis_controller_reset_state(axis_controller);
}

int axis_controller_clean(struct axis_controller* axis_controller) {
    while(!time_interval_dequeue(axis_controller_get_interval(axis_controller)));
    return hrtimer_try_to_cancel(__axis_controller_get_timer(axis_controller));
}

enum hrtimer_restart axis_controller_change_state(struct axis_controller* axis_controller) {
    struct time_interval* interval = axis_controller_get_interval(axis_controller);
    if(time_interval_not_empty(interval)) {
        axis_controller->state = !axis_controller->state;
        if(axis_controller->state) {
            printk("ON\n");
        } else {
            printk("OFF\n");
        }
        hrtimer_start(__axis_controller_get_timer(axis_controller), ktime_set(interval->sec, interval->nano_sec), HRTIMER_MODE_REL);
        time_interval_dequeue(interval);
    }
    return HRTIMER_NORESTART;
}

void axis_controller_controll(struct axis_controller* axis_controller) {
    __axis_controller_reset_state(axis_controller);
    axis_controller->timer.function(__axis_controller_get_timer(axis_controller));
}