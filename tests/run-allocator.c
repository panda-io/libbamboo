#include <bamboo.h>
#include <assert.h>

int main() {
    char buffer[1024];
    struct bamboo_allocator allocator;

    bamboo_allocator_init(&allocator, buffer, sizeof(buffer));
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer));

    void* ptr1 = bamboo_allocator_alloc(&allocator, 256);
    assert(ptr1 != NULL);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - 256);

    void* ptr2 = bamboo_allocator_alloc(&allocator, 512);
    assert(ptr2 != NULL);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - 768);

    void* ptr3 = bamboo_allocator_alloc(&allocator, 300); // Should fail
    assert(ptr3 == NULL);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - 768);

    bamboo_allocator_reset(&allocator);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer));

    void* ptr4 = bamboo_allocator_alloc(&allocator, 1024);
    assert(ptr4 != NULL);
    assert(bamboo_allocator_remaining(&allocator) == 0);

    void* ptr5 = bamboo_allocator_alloc(&allocator, 1); // Should fail
    assert(ptr5 == NULL);
    assert(bamboo_allocator_remaining(&allocator) == 0);

    return 0;
}