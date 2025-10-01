#ifndef BAMBOO_H
#define BAMBOO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/* allocator declarations */

struct bamboo_allocator {
    void* data;
    size_t size;
    size_t cursor;
};

void bamboo_allocator_init(struct bamboo_allocator* allocator, void* data, size_t size);

void* bamboo_allocator_alloc(struct bamboo_allocator* allocator, size_t size);

void bamboo_allocator_reset(struct bamboo_allocator* allocator);

size_t bamboo_allocator_remaining(const struct bamboo_allocator* allocator);

/* array declarations */

struct bamboo_array {
    bamboo_allocator allocator;
    size_t elem_size;
    size_t length;
};

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BAMBOO_H */