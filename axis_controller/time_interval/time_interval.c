#include "time_interval.h"
#include <linux/slab.h>

MODULE_LICENSE("GPL v2");

struct list_head* __time_interval_get_list(struct time_interval* time_interval) {
    return &(time_interval->list);
}

void time_interval_init(struct time_interval* time_interval) {
    INIT_LIST_HEAD(__time_interval_get_list(time_interval));
}

int time_interval_enqueue(struct time_interval* time_interval, unsigned long sec, unsigned long nano_sec) {
    struct time_interval* new_time_interval = kmalloc(sizeof(*time_interval), GFP_KERNEL);
    if(!new_time_interval) {
        return 1;
    }
    new_time_interval->sec = sec;
    new_time_interval->nano_sec = nano_sec;
    time_interval_init(new_time_interval);
    list_add_tail(__time_interval_get_list(new_time_interval), __time_interval_get_list(time_interval));
    return 0;
}

int time_interval_not_empty(struct time_interval* time_interval) {
    return !list_empty(__time_interval_get_list(time_interval));
}

int time_interval_dequeue(struct time_interval* time_interval) {
    int not_empty = time_interval_not_empty(time_interval);
    if(not_empty) {
        struct time_interval* interval = list_first_entry(__time_interval_get_list(time_interval), struct time_interval, list);
        list_del(__time_interval_get_list(interval));
        kfree(interval);
    }
    return !not_empty;
}