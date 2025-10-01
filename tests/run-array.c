#include <bamboo.h>
#include <assert.h>

int main() {
    char buffer[1024];
    struct bamboo_allocator allocator;

    bamboo_allocator_init(&allocator, buffer, sizeof(buffer));
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer));

    struct bamboo_array* array = bamboo_array_create(&allocator, sizeof(int), 10);
    assert(array != NULL);
    assert(array->elem_size == sizeof(int));
    assert(array->length == 10);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct bamboo_array) - sizeof(int) * 10);

    for (size_t i = 0; i < array->length; i++) {
        int value = (int)(i * 10);
        assert(bamboo_array_set(array, i, &value) == BAMBOO_SUCCESS);
    }

    for (size_t i = 0; i < array->length; i++) {
        int* value = (int*)bamboo_array_get(array, i);
        assert(value != NULL);
        assert(*value == (int)(i * 10));
    }

    // Test out of bounds access
    assert(bamboo_array_get(array, 10) == NULL); // Out of bounds
    int val = 100;
    assert(bamboo_array_set(array, 10, &val) == BAMBOO_INDEX_OUT_OF_BOUNDS); // Out of bounds

    return 0;
}