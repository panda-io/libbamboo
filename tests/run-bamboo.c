#include <bamboo.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct struct_with_string {
    struct bamboo_string* str;
};

struct struct_with_i32_list {
    struct bamboo_list* list;
};

int main() {
    char buffer[1024];
    struct bamboo_allocator allocator;
    bamboo_allocator_init(&allocator, buffer, sizeof(buffer));

    /* test string in a struct */
    struct struct_with_string* s = bamboo_allocator_alloc(&allocator, sizeof(struct struct_with_string));
    assert(s != NULL);
    s->str = bamboo_string_create(&allocator, 10);
    assert(s->str->length == 0);
    assert(s->str->capacity == 10);
    assert(bamboo_string_append_c_str(s->str, "Hello") == BAMBOO_SUCCESS);
    assert(s->str->length == 5);
    assert(s->str->capacity == 10);
    assert(strncmp(s->str->data, "Hello", s->str->length) == 0);
    assert(bamboo_string_append_c_str(s->str, " World") == BAMBOO_OUT_OF_CAPACITY);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct struct_with_string) - sizeof(struct bamboo_string) - 10);

    /* test list in a struct */
    bamboo_allocator_reset(&allocator);
    struct struct_with_i32_list* l = bamboo_allocator_alloc(&allocator, sizeof(struct struct_with_i32_list));
    assert(l != NULL);
    l->list = bamboo_list_create(&allocator, sizeof(int32_t), 5);
    assert(l->list != NULL);
    assert(l->list->elem_size == sizeof(int32_t));
    assert(l->list->capacity == 5);
    assert(l->list->cursor == 0);
    for (int32_t i = 0; i < 5; i++) {
        assert(bamboo_list_append(l->list, &i) == BAMBOO_SUCCESS);
        assert(l->list->cursor == i + 1);
        int32_t* val = (int32_t*)bamboo_list_get(l->list, i);
        assert(val != NULL);
        assert(*val == i);
    }

    return 0;
}