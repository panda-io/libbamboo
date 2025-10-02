#include <bamboo.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct struct_with_string {
    struct bamboo_string* str;
};

struct struct_with_list {
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

    /* test i32 list in a struct */
    bamboo_allocator_reset(&allocator);
    struct struct_with_list* l = bamboo_allocator_alloc(&allocator, sizeof(struct struct_with_list));
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
    assert(bamboo_list_append(l->list, &(int32_t){5}) == BAMBOO_OUT_OF_CAPACITY);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct struct_with_list) - sizeof(struct bamboo_list) - sizeof(int32_t) * 5);

    /* test string list in a struct */
    bamboo_allocator_reset(&allocator);
    struct struct_with_list* sl = bamboo_allocator_alloc(&allocator, sizeof(struct struct_with_list));
    assert(sl != NULL);
    sl->list = bamboo_list_create(&allocator, sizeof(struct bamboo_string*), 3);
    assert(sl->list != NULL);
    assert(sl->list->elem_size == sizeof(struct bamboo_string*));
    assert(sl->list->capacity == 3);
    assert(sl->list->cursor == 0);
    for (int i = 0; i < 3; i++) {
        struct bamboo_string* str = bamboo_string_create(&allocator, 10);
        assert(str != NULL);
        char temp[10];
        snprintf(temp, sizeof(temp), "Str%d", i);
        assert(bamboo_string_append_c_str(str, temp) == BAMBOO_SUCCESS);
        assert(bamboo_list_append(sl->list, &str) == BAMBOO_SUCCESS);
        assert(sl->list->cursor == i + 1);
        struct bamboo_string** val = (struct bamboo_string**)bamboo_list_get(sl->list, i);
        assert(val != NULL);
        assert((*val)->length == strlen(temp));
        assert(strncmp((*val)->data, temp, (*val)->length) == 0);
    }
    assert(bamboo_list_append(sl->list, &(struct bamboo_string*){NULL}) == BAMBOO_OUT_OF_CAPACITY);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct struct_with_list) - sizeof(struct bamboo_list) - sizeof(struct bamboo_string*) * 3 - sizeof(struct bamboo_string) * 3 - 10 * 3);

    /* test nested list in a struct */
    bamboo_allocator_reset(&allocator);
    struct struct_with_list* nl = bamboo_allocator_alloc(&allocator, sizeof(struct struct_with_list));
    assert(nl != NULL);
    nl->list = bamboo_list_create(&allocator, sizeof(struct bamboo_list*), 2);
    assert(nl->list != NULL);
    assert(nl->list->elem_size == sizeof(struct bamboo_list*));
    assert(nl->list->capacity == 2);
    assert(nl->list->cursor == 0);
    for (int i = 0; i < 2; i++) {
        struct bamboo_list* inner_list = bamboo_list_create(&allocator, sizeof(int32_t), 4);
        assert(inner_list != NULL);
        for (int32_t j = 0; j < 4; j++) {
            assert(bamboo_list_append(inner_list, &j) == BAMBOO_SUCCESS);
        }
        assert(bamboo_list_append(nl->list, &inner_list) == BAMBOO_SUCCESS);
        assert(nl->list->cursor == i + 1);
        struct bamboo_list** val = (struct bamboo_list**)bamboo_list_get(nl->list, i);
        assert(val != NULL);
        assert((*val)->elem_size == sizeof(int32_t));
        assert((*val)->capacity == 4);
        assert((*val)->cursor == 4);
        for (int32_t j = 0; j < 4; j++) {
            int32_t* inner_val = (int32_t*)bamboo_list_get(*val, j);
            assert(inner_val != NULL);
            assert(*inner_val == j);
        }
    }
    assert(bamboo_list_append(nl->list, &(struct bamboo_list*){NULL}) == BAMBOO_OUT_OF_CAPACITY);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct struct_with_list) - sizeof(struct bamboo_list) - sizeof(struct bamboo_list*) * 2 - (sizeof(struct bamboo_list) + sizeof(int32_t) * 4) * 2);

    return 0;
}