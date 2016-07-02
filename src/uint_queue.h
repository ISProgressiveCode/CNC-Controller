#ifndef _UINT_QUEUE_H
#define  _UINT_QUEUE_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL v2");

struct uint_queue {
    unsigned long data;
    struct list_head list;
};

static inline struct list_head* __uint_queue_get_list(struct uint_queue* uint_queue) {
    return &(uint_queue->list);
}

static inline void uint_queue_init(struct uint_queue* uint_queue) {
    INIT_LIST_HEAD(__uint_queue_get_list(uint_queue));
}

static inline int uint_queue_enqueue(struct uint_queue* uint_queue, unsigned long data) {
    struct uint_queue* new_uint_queue = kmalloc(sizeof(*uint_queue), GFP_KERNEL);
    if(!new_uint_queue) {
        return 1;
    }
    new_uint_queue->data = data;
    uint_queue_init(new_uint_queue);
    list_add_tail(__uint_queue_get_list(new_uint_queue), __uint_queue_get_list(uint_queue));
    return 0;
}

static inline int uint_queue_not_empty(struct uint_queue* uint_queue) {
    return !list_empty(__uint_queue_get_list(uint_queue));
}

static inline struct uint_queue* uint_queue_first(struct uint_queue* uint_queue) {
    return list_first_entry(__uint_queue_get_list(uint_queue), struct uint_queue, list);
}

static inline unsigned long uint_queue_first_data(struct uint_queue* uint_queue) {
    return (uint_queue_first(uint_queue))->data;
}

static inline int uint_queue_dequeue(struct uint_queue* uint_queue) {
    int not_empty = uint_queue_not_empty(uint_queue);
    if(not_empty) {
        struct uint_queue* old_uint_queue = uint_queue_first(uint_queue);
        list_del(__uint_queue_get_list(old_uint_queue));
        kfree(old_uint_queue);
    }
    return !not_empty;
}

#endif