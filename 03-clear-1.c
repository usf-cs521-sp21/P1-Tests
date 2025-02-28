#if 0
    source "${TEST_DIR}/lib/crunner" -lelist
#endif

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>

#include "elist.h"

struct elist {
    size_t capacity;
    size_t size;
    size_t item_sz;
    void *element_storage;
};

test_start("Ensures clear() works correctly by checking the list size and accessibility of cleared elements (requires size() to be implemented)");

subtest("clear",
{
    struct elist *list = elist_create(100, sizeof(int));
    test_assert(list != NULL);

    int i;
    for (i = 1; i <= 100; ++i) {
        elist_add(list, &i);
    }

    size_t size = elist_size(list);
    test_assert(size == 100);

    elist_clear(list);

    size = elist_size(list);
    test_assert(size == 0);

    elist_add(list, &i);
    size = elist_size(list);
    test_assert(size == 1);

    void *result = elist_get(list, 1);
    test_assert(result == NULL);

    result = elist_get(list, 50);
    test_assert(result == NULL);

    result = elist_get(list, 0);
    test_assert(result != NULL);

    elist_destroy(list);
});

subtest("clear_mem",
{
    struct elist *list = elist_create(1000, sizeof(int));
    test_assert(list != NULL);

    int i;
    for (i = 1; i <= 1000; ++i) {
        elist_add(list, &i);
    }

    size_t size = elist_size(list);
    test_assert(size == 1000);

    elist_clear_mem(list);

    size = elist_size(list);
    test_assert(size == 0);

    elist_add(list, &i);
    size = elist_size(list);
    test_assert(size == 1);

    void *result = elist_get(list, 1);
    test_assert(result == NULL);

    result = elist_get(list, 50);
    test_assert(result == NULL);

    result = elist_get(list, 0);
    test_assert(result != NULL);

    /* Find the location of the first int and then access
     * the rest of the memory locations */
    int total = 0;
    int *elements = (int *) list->element_storage;
    for (int j = 0; j < 1000; ++j) {
        total += elements[j];
    }

    test_assert(total == 1001);
    test_printf("%d", total);

    elist_destroy(list);
});

test_end
