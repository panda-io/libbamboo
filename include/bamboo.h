#ifndef BAMBOO_H
#define BAMBOO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/* operation result declarations */

typedef enum {
    BAMBOO_SUCCESS = 0,
    BAMBOO_INDEX_OUT_OF_BOUNDS,
    BAMBOO_OUT_OF_CAPACITY
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

/* list declarations */

struct bamboo_list {
    void* data;
    size_t elem_size;
    size_t capacity;
    size_t cursor;
};

struct bamboo_list* bamboo_list_create(struct bamboo_allocator* allocator, size_t elem_size, size_t capacity);

void* bamboo_list_get(const struct bamboo_list* list, size_t index);

bamboo_result_t bamboo_list_set(struct bamboo_list* list, size_t index, void* value);

void* bamboo_list_allocate_next(struct bamboo_list* list);

bamboo_result_t bamboo_list_append(struct bamboo_list* list, void* value);

bamboo_result_t bamboo_list_insert_at(struct bamboo_list* list, size_t index, void* value);

bamboo_result_t bamboo_list_remove_at(struct bamboo_list* list, size_t index);

void bamboo_list_clear(struct bamboo_list* list);

/* string declarations */

struct bamboo_string {
    char* data;
    size_t length;
    size_t capacity;
};

struct bamboo_string* bamboo_string_create(struct bamboo_allocator* allocator, size_t capacity);

bamboo_result_t bamboo_string_append_c_str(struct bamboo_string* string, const char* str);

bamboo_result_t bamboo_string_copy_to_c_str(const struct bamboo_string* string, char* out, size_t out_size);

void bamboo_string_clear(struct bamboo_string* string);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BAMBOO_H */