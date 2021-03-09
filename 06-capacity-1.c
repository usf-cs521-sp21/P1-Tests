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

int sum_elist(struct elist *list)
{
    int total = 0;
    for (int i = 0; i < elist_size(list); ++i) {
        int *num = elist_get(list, i);
        total += *num;
    }
    return total;
}

struct elist {
    size_t capacity;
    size_t size;
    size_t item_sz;
    void *element_storage;
};

test_start("Tests the set_capacity function");

subtest("",

    struct elist *list = elist_create(1, sizeof(int));
    elist_set_capacity(list, 1000000);
    for (int i = 0; i < 1000000; ++i) {
        elist_add(list, &i);
    }

    int total = sum_elist(list);
    test_assert(total == 1783293664);
    test_printf("%d", total);

    elist_set_capacity(list, 1000);
    total = sum_elist(list);
    test_assert(total == 499500);
    test_printf("%d", total);

    elist_set_capacity(list, 10);
    total = sum_elist(list);
    test_assert(total == 45);
    test_printf("%d", total);

    elist_set_capacity(list, 100);
    total = sum_elist(list);
    test_assert(total == 45);
    test_printf("%d", total);

    int x = 6;
    elist_set_capacity(list, 0);
    elist_add(list, &x);

    elist_set_capacity(list, 1);
    x = 5;
    elist_add(list, &x);
    total = sum_elist(list);
    test_assert(total == 11); /* 5 + 6 */
    size_t size = elist_size(list);
    test_assert(size == 2);

    elist_destroy(list);
);

test_end
