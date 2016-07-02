#ifndef _AXIS_CONTROLLER_H
#define _AXIS_CONTROLLER_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include "pin_change.h"

#define PULSE_WIDTH 10

MODULE_LICENSE("GPL v2");

typedef enum hrtimer_restart (*axis_controller_function)(struct hrtimer*);

struct axis_controller {
    struct hrtimer timer;
    struct pin_change pulse;
    struct pin_change dir;
    unsigned long counter;
};

static inline struct hrtimer* __axis_controller_get_timer(struct axis_controller* axis_controller) {
    return &(axis_controller->timer);
}

static inline struct pin_change* __axis_controller_get_pulse(struct axis_controller* axis_controller) {
    return &(axis_controller->pulse);
}

static inline struct pin_change* __axis_controller_get_dir(struct axis_controller* axis_controller) {
    return &(axis_controller->dir);
}

static inline void axis_controller_init(struct axis_controller* axis_controller, int pulse, int dir, axis_controller_function function) {
    hrtimer_init(__axis_controller_get_timer(axis_controller), CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    axis_controller->timer.function = function;
    pin_change_init(__axis_controller_get_pulse(axis_controller), pulse, 0);
    pin_change_init(__axis_controller_get_dir(axis_controller), dir, 1);
    axis_controller->counter = 0;
}

static inline int axis_controller_clean(struct axis_controller* axis_controller) {
    pin_change_clean(__axis_controller_get_pulse(axis_controller));
    pin_change_clean(__axis_controller_get_dir(axis_controller));
    return hrtimer_try_to_cancel(__axis_controller_get_timer(axis_controller));
}

static inline void axis_controller_begin(struct axis_controller* axis_controller) {
    axis_controller->counter = 0;
}

static inline void axis_controller_count(struct axis_controller* axis_controller) {
    ++axis_controller->counter;
}

static inline int __axis_controller_pulse_change(struct axis_controller* axis_controller, unsigned long width) {
    axis_controller_count(axis_controller);
    return pin_change_add_change(__axis_controller_get_pulse(axis_controller), width * 1000);
}

static inline int axis_controller_add_pulse_change(struct axis_controller* axis_controller, unsigned long count, unsigned long width) {
    unsigned long i;
    for(i = 0; i < count; ++i) {
        if(__axis_controller_pulse_change(axis_controller, PULSE_WIDTH) || __axis_controller_pulse_change(axis_controller, width)) {
            return 1;
        }
    }
    return 0;
}

static inline int axis_controller_add_dir_change(struct axis_controller* axis_controller) {
    int change = pin_change_add_change(__axis_controller_get_dir(axis_controller), axis_controller->counter);
    axis_controller_begin(axis_controller);
    return change;
}

static inline void axis_controller_controll(struct axis_controller* axis_controller) {
    pin_change_reset_state(__axis_controller_get_pulse(axis_controller));
    pin_change_reset_state(__axis_controller_get_dir(axis_controller));
    axis_controller_begin(axis_controller);
    axis_controller->timer.function(__axis_controller_get_timer(axis_controller));
}

static inline enum hrtimer_restart axis_controller_change_state(struct axis_controller* axis_controller) {
    struct pin_change* pulse = __axis_controller_get_pulse(axis_controller);
    struct pin_change* dir = __axis_controller_get_dir(axis_controller);
    unsigned long timeout = pin_change_take_data(pulse);
    if(axis_controller->counter && (axis_controller->counter == pin_change_extract_data(dir))) {
        pin_change_remove_data(dir);
        pin_change_change_state(dir);
        axis_controller_begin(axis_controller);
    }
    if(timeout) {
        pin_change_change_state(pulse);
        axis_controller_count(axis_controller);
        hrtimer_start(__axis_controller_get_timer(axis_controller), ktime_set(0, timeout), HRTIMER_MODE_REL);
    }
    return HRTIMER_NORESTART;
}

#endif