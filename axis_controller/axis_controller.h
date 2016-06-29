#ifndef _AXIS_CONTROLLER_H
#define _AXIS_CONTROLLER_H

#include "time_interval/time_interval.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

struct axis_controller {
    struct hrtimer timer;
    struct time_interval interval;
    int state;
};

inline struct hrtimer* __axis_controller_get_timer(struct axis_controller* axis_controller);

inline struct time_interval* axis_controller_get_interval(struct axis_controller* axis_controller);

inline void __axis_controller_reset_state(struct axis_controller* axis_controller);

inline void axis_controller_init(struct axis_controller* axis_controller, enum hrtimer_restart (*function)(struct hrtimer *));

inline int axis_controller_clean(struct axis_controller* axis_controller);

inline void axis_controller_change_state(struct axis_controller* axis_controller, unsigned long sec, unsigned long nano_sec);

inline void axis_controller_controll(struct axis_controller* axis_controller);

#endif