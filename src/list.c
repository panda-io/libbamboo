#include "../include/bamboo.h"
#include <string.h>

struct bamboo_list* bamboo_list_create(struct bamboo_allocator* allocator, size_t elem_size, size_t capacity) {
    struct bamboo_list* list = (struct bamboo_list*)bamboo_allocator_alloc(allocator, sizeof(struct bamboo_list));
    if (!list) {
        return NULL; // Allocation failed
    }
    list->data = bamboo_allocator_alloc(allocator, elem_size * capacity);
    if (!list->data) {
        return NULL; // Allocation failed
    }
    list->elem_size = elem_size;
    list->capacity = capacity;
    list->cursor = 0;
    return list;
}

void* bamboo_list_get(const struct bamboo_list* list, size_t index) {
    if (index >= list->cursor) {
        return NULL; // Out of bounds
    }
    return (char*)list->data + (index * list->elem_size);
}

bamboo_result_t bamboo_list_set(struct bamboo_list* list, size_t index, void* value) {
    if (index >= list->cursor) {
        return BAMBOO_INDEX_OUT_OF_BOUNDS; // Out of bounds
    }
    memcpy((char*)list->data + (index * list->elem_size), value, list->elem_size);
    return BAMBOO_SUCCESS;
}

void* bamboo_list_allocate_next(struct bamboo_list* list) {
    if (list->cursor >= list->capacity) {
        return NULL; // Out of capacity
    }
    void* ptr = (char*)list->data + (list->cursor * list->elem_size);
    list->cursor++;
    return ptr;
}

bamboo_result_t bamboo_list_insert_at(struct bamboo_list* list, size_t index, void* value) {
    if (list->cursor >= list->capacity) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    if (index > list->cursor) {
        return BAMBOO_INDEX_OUT_OF_BOUNDS; // Out of bounds
    }
    memmove((char*)list->data + ((index + 1) * list->elem_size), (char*)list->data + (index * list->elem_size), (list->cursor - index) * list->elem_size);
    memcpy((char*)list->data + (index * list->elem_size), value, list->elem_size);
    list->cursor++;
    return BAMBOO_SUCCESS;
}

bamboo_result_t bamboo_list_append(struct bamboo_list* list, void* value) {
    if (list->cursor >= list->capacity) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    memcpy((char*)list->data + (list->cursor * list->elem_size), value, list->elem_size);
    list->cursor++;
    return BAMBOO_SUCCESS;
}

bamboo_result_t bamboo_list_remove_at(struct bamboo_list* list, size_t index) {
    if (index >= list->cursor) {
        return BAMBOO_INDEX_OUT_OF_BOUNDS; // Out of bounds
    }
    memmove((char*)list->data + (index * list->elem_size), (char*)list->data + ((index + 1) * list->elem_size), (list->cursor - index - 1) * list->elem_size);
    list->cursor--;
    return BAMBOO_SUCCESS;
}

void bamboo_list_clear(struct bamboo_list* list) {
    list->cursor = 0;
}