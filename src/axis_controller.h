#ifndef _AXIS_CONTROLLER_H
#define _AXIS_CONTROLLER_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include "time_interval.h"

MODULE_LICENSE("GPL v2");

struct axis_controller {
    struct hrtimer timer;
    struct time_interval interval;
    int state;
};

static inline struct hrtimer* __axis_controller_get_timer(struct axis_controller* axis_controller) {
    return &(axis_controller->timer);
}

static inline struct time_interval* axis_controller_get_interval(struct axis_controller* axis_controller) {
    return &(axis_controller->interval);
}

static inline void __axis_controller_reset_state(struct axis_controller* axis_controller) {
    axis_controller->state = 0;
}

static inline void axis_controller_init(struct axis_controller* axis_controller, enum hrtimer_restart (*function)(struct hrtimer *)) {
    hrtimer_init(__axis_controller_get_timer(axis_controller), CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    axis_controller->timer.function = function;
    time_interval_init(axis_controller_get_interval(axis_controller));
    __axis_controller_reset_state(axis_controller);
}

static inline int axis_controller_clean(struct axis_controller* axis_controller) {
    while(!time_interval_dequeue(axis_controller_get_interval(axis_controller)));
    return hrtimer_try_to_cancel(__axis_controller_get_timer(axis_controller));
}

static inline enum hrtimer_restart axis_controller_change_state(struct axis_controller* axis_controller) {
    struct time_interval* interval = axis_controller_get_interval(axis_controller);
    axis_controller->state = !axis_controller->state;
    if(axis_controller->state) {
        printk("ON\n");
    } else {
        printk("OFF\n");
    }
    if(time_interval_not_empty(interval)) {
        hrtimer_start(__axis_controller_get_timer(axis_controller), ktime_set(interval->sec, interval->nano_sec), HRTIMER_MODE_REL);
        time_interval_dequeue(interval);
    }
    return HRTIMER_NORESTART;
}

static inline void axis_controller_controll(struct axis_controller* axis_controller) {
    __axis_controller_reset_state(axis_controller);
    axis_controller->timer.function(__axis_controller_get_timer(axis_controller));
}

static inline int axis_controller_add_interval(struct axis_controller* axis_controller, unsigned long sec, unsigned long nano_sec) {
    return time_interval_enqueue(axis_controller_get_interval(axis_controller), sec, nano_sec);
}

#endif