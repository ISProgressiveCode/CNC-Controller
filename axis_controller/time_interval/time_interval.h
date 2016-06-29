#ifndef _TIME_INTERVAL_H
#define  _TIME_INTERVAL_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

struct time_interval {
    unsigned long sec;
    unsigned long nano_sec;
    struct list_head list;
};

inline void time_interval_init(struct time_interval* time_interval);

inline int time_interval_enqueue(struct time_interval* time_interval, unsigned long sec, unsigned long nano_sec);

inline int time_interval_not_empty(struct time_interval* time_interval);

inline int time_interval_dequeue(struct time_interval* time_interval);

#endif