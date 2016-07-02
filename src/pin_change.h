#ifndef _PIN_CHANGE_H
#define _PIN_CHANGE_H

#include "uint_queue.h"

MODULE_LICENSE("GPL v2");

struct pin_change {
    int pin;
    int state;
    struct uint_queue queue;
};

static inline struct uint_queue* __pin_change_get_queue(struct pin_change* pin_change) {
    return &(pin_change->queue);
}

static inline void pin_change_reset_state(struct pin_change* pin_change) {
    pin_change->state = 0;
}

static inline void pin_change_init(struct pin_change* pin_change, int pin) {
    pin_change->pin = pin;
    pin_change_reset_state(pin_change);
    uint_queue_init(__pin_change_get_queue(pin_change));
}

static inline void pin_change_clean(struct pin_change* pin_change) {
    pin_change->state = 0;
    while(!uint_queue_dequeue(__pin_change_get_queue(pin_change)));
}

static inline void pin_change_change_state(struct pin_change* pin_change) {
    pin_change->state = !pin_change->state;
    if(pin_change->state) {
        printk("ON: pin %d\n", pin_change->pin);
    } else {
        printk("OFF: pin %d\n", pin_change->pin);
    }
}

static inline int pin_change_add_change(struct pin_change* pin_change, unsigned long data) {
    return uint_queue_enqueue(__pin_change_get_queue(pin_change), data);
}

static inline unsigned long pin_change_extract_data(struct pin_change* pin_change) {
    struct uint_queue* queue = __pin_change_get_queue(pin_change);
    return uint_queue_not_empty(queue) ? uint_queue_first_data(queue) : 0;
}

static inline void pin_change_remove_data(struct pin_change* pin_change) {
    if(pin_change_extract_data(pin_change)) {
        uint_queue_dequeue(__pin_change_get_queue(pin_change));
    }
}

static inline unsigned long pin_change_take_data(struct pin_change* pin_change) {
    unsigned long data = pin_change_extract_data(pin_change);
    pin_change_remove_data(pin_change);
    return data;
}

#endif