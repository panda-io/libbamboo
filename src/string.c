#include "../include/bamboo.h"
#include <string.h>

struct bamboo_string* bamboo_string_create(struct bamboo_allocator* allocator, size_t capacity) {
    struct bamboo_string* string = (struct bamboo_string*)bamboo_allocator_alloc(allocator, sizeof(struct bamboo_string));
    if (!string) {
        return NULL; // Allocation failed
    }
    string->data = (char*)bamboo_allocator_alloc(allocator, capacity);
    if (!string->data) {
        return NULL; // Allocation failed
    }
    string->length = 0;
    string->capacity = capacity;
    return string;
}

bamboo_result_t bamboo_string_append(struct bamboo_string* to, struct bamboo_string* from) {
    if (to->length + from->length > to->capacity) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    memcpy(to->data + to->length, from->data, from->length);
    to->length += from->length;
    return BAMBOO_SUCCESS;
}

bamboo_result_t bamboo_string_append_c_str(struct bamboo_string* string, const char* str) {
    size_t str_len = strlen(str);
    if (string->length + str_len > string->capacity) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    memcpy(string->data + string->length, str, str_len);
    string->length += str_len;
    return BAMBOO_SUCCESS;
}

bamboo_result_t bamboo_string_copy_from(struct bamboo_string* to, struct bamboo_string* from) {
    if (from->length > to->capacity) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    memcpy(to->data, from->data, from->length);
    to->length = from->length;
    return BAMBOO_SUCCESS;
}

bamboo_result_t bamboo_string_copy_from_c_str(struct bamboo_string* string, const char* str) {
    size_t str_len = strlen(str);
    if (str_len > string->capacity) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    memcpy(string->data, str, str_len);
    string->length = str_len;
    return BAMBOO_SUCCESS;
}

bamboo_result_t bamboo_string_copy_to_c_str(const struct bamboo_string* string, char* out, size_t out_size) {
    if (string->length + 1 > out_size) {
        return BAMBOO_OUT_OF_CAPACITY; // Out of capacity
    }
    memcpy(out, string->data, string->length);
    out[string->length] = '\0';
    return BAMBOO_SUCCESS;
}

void bamboo_string_clear(struct bamboo_string* string) {
    string->length = 0;
}