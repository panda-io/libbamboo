#include <bamboo.h>
#include <assert.h>
#include <string.h>

int main() {
    char buffer[1024];
    struct bamboo_allocator allocator;

    bamboo_allocator_init(&allocator, buffer, sizeof(buffer));
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer));

    struct bamboo_string* str1 = bamboo_string_create(&allocator, 10);
    assert(str1 != NULL);
    assert(str1->length == 0);
    assert(str1->capacity == 10);
    assert(bamboo_allocator_remaining(&allocator) == sizeof(buffer) - sizeof(struct bamboo_string) - 10);
    assert(bamboo_string_append_c_str(str1, "Hello") == BAMBOO_SUCCESS);
    assert(str1->length == 5);
    assert(str1->capacity == 10);
    assert(strncmp(str1->data, "Hello", str1->length) == 0);
    assert(bamboo_string_append_c_str(str1, " World") == BAMBOO_OUT_OF_CAPACITY);
    assert(str1->length == 5);
    assert(str1->capacity == 10);
    assert(strncmp(str1->data, "Hello", str1->length) == 0);
    assert(bamboo_string_append_c_str(str1, "!!!") == BAMBOO_SUCCESS);
    assert(str1->length == 8);
    assert(str1->capacity == 10);
    assert(strncmp(str1->data, "Hello!!!", str1->length) == 0);
    assert(bamboo_string_append_c_str(str1, "") == BAMBOO_SUCCESS);
    assert(str1->length == 8);
    assert(str1->capacity == 10);

    struct bamboo_string* str2 = bamboo_string_create(&allocator, 5);
    assert(str2 != NULL);
    assert(str2->length == 0);
    assert(str2->capacity == 5);
    assert(bamboo_string_copy_from_c_str(str2, "Hi") == BAMBOO_SUCCESS);
    assert(str2->length == 2);
    assert(str2->capacity == 5);
    assert(strncmp(str2->data, "Hi", str2->length) == 0);
    assert(bamboo_string_copy_from_c_str(str2, "Hello") == BAMBOO_SUCCESS);
    assert(str2->length == 5);
    assert(str2->capacity == 5);
    assert(strncmp(str2->data, "Hello", str2->length) == 0);
    assert(bamboo_string_copy_from_c_str(str2, "Hello World") == BAMBOO_OUT_OF_CAPACITY);
    assert(str2->length == 5);
    assert(str2->capacity == 5);
    assert(strncmp(str2->data, "Hello", str2->length) == 0);

    struct bamboo_string* str3 = bamboo_string_create(&allocator, 15);
    assert(str3 != NULL);
    assert(str3->length == 0);
    assert(str3->capacity == 15);
    assert(bamboo_string_copy_from(str3, str1) == BAMBOO_SUCCESS);
    assert(str3->length == str1->length);
    assert(str3->capacity == 15);
    assert(strncmp(str3->data, str1->data, str3->length) == 0);
    assert(bamboo_string_copy_from(str3, str2) == BAMBOO_SUCCESS);
    assert(str3->length == str2->length);
    assert(str3->capacity == 15);
    assert(strncmp(str3->data, str1->data, str3->length) == 0);
    bamboo_string_clear(str3);
    assert(bamboo_string_append(str3, str1) == BAMBOO_SUCCESS);
    assert(str3->length == str1->length);
    assert(str3->capacity == 15);
    assert(strncmp(str3->data, str1->data, str3->length) == 0);
    assert(bamboo_string_append(str3, str2) == BAMBOO_SUCCESS);
    assert(str3->length == str1->length + str2->length);
    assert(str3->capacity == 15);
    assert(strncmp(str3->data, "Hello!!!Hello", str3->length) == 0);
    assert(bamboo_string_append(str3, str2) == BAMBOO_OUT_OF_CAPACITY);
    assert(str3->length == str1->length + str2->length);
    assert(str3->capacity == 15);
    assert(strncmp(str3->data, "Hello!!!Hello", str3->length) == 0);
    char out[20];
    assert(bamboo_string_copy_to_c_str(str3, out, sizeof(out)) == BAMBOO_SUCCESS);
    assert(strcmp(out, "Hello!!!Hello") == 0);
    assert(bamboo_string_copy_to_c_str(str3, out, 5) == BAMBOO_OUT_OF_CAPACITY);
    assert(strcmp(out, "Hello!!!Hello") == 0);
    bamboo_string_clear(str3);
    assert(bamboo_string_append_c_str(str3, "") == BAMBOO_SUCCESS);
    assert(str3->length == 0);
    assert(str3->capacity == 15);
    assert(strncmp(str3->data, "Hello!!!Hello", str3->length) == 0);

    return 0;
}