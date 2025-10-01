#include "bamboo-private.h"

void bamboo_allocator_init(struct bamboo_allocator* allocator, void* data, size_t size) {
    allocator->data = data;
    allocator->size = size;
    allocator->cursor = 0;
}

void* bamboo_allocator_alloc(struct bamboo_allocator* allocator, size_t size) {
    if (allocator->cursor + size > allocator->size) {
        return NULL; // Not enough space
    }
    void* ptr = (char*)allocator->data + allocator->cursor;
    allocator->cursor += size;
    return ptr;
}

void bamboo_allocator_reset(struct bamboo_allocator* allocator) {
    allocator->cursor = 0;
}

size_t bamboo_allocator_remaining(const struct bamboo_allocator* allocator) {
    return allocator->size - allocator->cursor;
}