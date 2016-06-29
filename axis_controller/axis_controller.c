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
void axis_controller_change_state(struct axis_controller* axis_controller, unsigned long sec, unsigned long nano_sec) {
    axis_controller->state = !axis_controller->state;
    hrtimer_start(__axis_controller_get_timer(axis_controller), ktime_set(sec, nano_sec), HRTIMER_MODE_REL);
}
void axis_controller_controll(struct axis_controller* axis_controller) {
    __axis_controller_reset_state(axis_controller);
    axis_controller->timer.function(__axis_controller_get_timer(axis_controller));
}