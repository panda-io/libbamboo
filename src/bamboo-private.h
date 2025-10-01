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