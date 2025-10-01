#ifndef BAMBOO_H
#define BAMBOO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/* operation result declarations */

typedef enum {
    BAMBOO_SUCCESS = 0,
    BAMBOO_INDEX_OUT_OF_BOUNDS
} bamboo_result_t;

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
    void* data;
    size_t elem_size;
    size_t length;
};

struct bamboo_array* bamboo_array_create(struct bamboo_allocator* allocator, size_t elem_size, size_t length);

void* bamboo_array_get(const struct bamboo_array* array, size_t index);

bamboo_result_t bamboo_array_set(struct bamboo_array* array, size_t index, void* value);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BAMBOO_H */