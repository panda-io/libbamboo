#include <bamboo.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct struct_with_string {
    struct bamboo_string str;
};

int main() {
    char buffer[1024];
    struct bamboo_allocator allocator;
    bamboo_allocator_init(&allocator, buffer, sizeof(buffer));

    /* test string in a struct */
    struct struct_with_string* s = bamboo_allocator_alloc(&allocator, sizeof(struct struct_with_string));
    assert(s != NULL);
    bamboo_string_init(&s->str, &allocator, 10);
    assert(s->str.length == 0);
    assert(s->str.capacity == 10);
    assert(bamboo_string_append_c_str(&s->str, "Hello") == BAMBOO_SUCCESS);
    assert(s->str.length == 5);
    assert(s->str.capacity == 10);
    assert(strncmp(s->str.data, "Hello", s->str.length) == 0);
    assert(bamboo_string_append_c_str(&s->str, " World") == BAMBOO_OUT_OF_CAPACITY);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct struct_with_string) - 10);

    return 0;
}