#include <bamboo.h>
#include <assert.h>

int main() {
    char buffer[1024];
    struct bamboo_allocator allocator;

    bamboo_allocator_init(&allocator, buffer, sizeof(buffer));
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer));

    struct bamboo_list* list = bamboo_list_create(&allocator, sizeof(int), 5);
    assert(list != NULL);
    assert(list->elem_size == sizeof(int));
    assert(list->capacity == 5);
    assert(list->cursor == 0);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct bamboo_list) - sizeof(int) * 5);
    assert(bamboo_list_get(list, 0) == NULL);

    for (int i = 0; i < 5; i++) {
        int value = i * 10;
        assert(bamboo_list_append(list, &value) == BAMBOO_SUCCESS);
        assert(list->cursor == (size_t)(i + 1));
    }
    assert(bamboo_list_append(list, &(int){50}) == BAMBOO_OUT_OF_CAPACITY);
    assert(bamboo_list_get(list, 5) == NULL);
    assert(bamboo_list_set(list, 5, &(int){100}) == BAMBOO_INDEX_OUT_OF_BOUNDS);
    assert(list->cursor == 5);
    for (size_t i = 0; i < list->cursor; i++) {
        int* value = (int*)bamboo_list_get(list, i);
        assert(value != NULL);
        assert(*value == (int)(i * 10));
        int new_value = (int)(i * 20);
        assert(bamboo_list_set(list, i, &new_value) == BAMBOO_SUCCESS);
    }
    for (size_t i = 0; i < list->cursor; i++) {
        int* value = (int*)bamboo_list_get(list, i);
        assert(value != NULL);
        assert(*value == (int)(i * 20));
    }

    return 0;
}