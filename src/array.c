#include "../include/bamboo.h"
#include <string.h>

struct bamboo_array* bamboo_array_create(struct bamboo_allocator* allocator, size_t elem_size, size_t length) {
    struct bamboo_array* array = (struct bamboo_array*)bamboo_allocator_alloc(allocator, sizeof(struct bamboo_array));
    if (!array) {
        return NULL; // Allocation failed
    }
    array->data = bamboo_allocator_alloc(allocator, elem_size * length);
    if (!array->data) {
        return NULL; // Allocation failed
    }
    array->elem_size = elem_size;
    array->length = length;
    return array;
}

void* bamboo_array_get(const struct bamboo_array* array, size_t index) {
    if (index >= array->length) {
        return NULL; // Out of bounds
    }
    return (char*)array->data + index * array->elem_size;
}

bamboo_result_t bamboo_array_set(struct bamboo_array* array, size_t index, void* value) {
    if (index >= array->length) {
        return BAMBOO_INDEX_OUT_OF_BOUNDS; // Out of bounds
    }
    void* dest = (char*)array->data + index * array->elem_size;
    memcpy(dest, value, array->elem_size);
    return BAMBOO_SUCCESS;
}