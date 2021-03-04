#if 0
    source "${TEST_DIR}/lib/crunner" -lelist
#endif

#include <stddef.h>
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

test_start("Tests adding and retrieving elements.");

subtest("Adding and retrieving a large amount of integers",
{
    struct elist *list = elist_create(10, sizeof(int) * 5);
    test_assert(list != NULL);

    /* Add 100,000 elements. */
    for (int i = 0; i <= 100000; ++i) {
        /* Each element is an array of 5 ints.
         * The first 4 ints are random numbers, and
         * the last int contains the sum of the first
         * four numbers (allowing us to verify
         * correctness) */
        int nums[5];
        int total = 0;
        for (int j = 0; j < 4; ++j) {
            nums[j] = random() % 100;
            total += nums[j];
        }
        nums[4] = total;
        elist_add(list, nums);
    }

    for (int i = 0; i < 100000; ++i) {
        int *nums = elist_get(list, i);
        int total = 0;
        for (int j = 0; j < 4; ++j) {
            total += nums[j];
        }
        /* Sorry for spamming the output... */
        test_printf("%d\n", total);
        test_assert(total == nums[4]);
    }

    elist_destroy(list);
});

subtest("Testing add_new",
{
    struct elist *list = elist_create(5, 22222);
    test_assert(list != NULL);

    void *a = elist_add_new(list);
    void *b = elist_add_new(list);
    void *c = elist_add_new(list);
    void *d = elist_add_new(list);
    void *e = elist_add_new(list);

    ptrdiff_t ba_diff = b - a;
    test_assert(ba_diff == 22222);

    ptrdiff_t cb_diff = c - b;
    test_assert(cb_diff == 22222);

    ptrdiff_t dc_diff = d - c;
    test_assert(dc_diff == 22222);

    ptrdiff_t ea_diff = e - a;
    test_assert(ea_diff == 88888);

    void *f = elist_add_new(list);
    /* Retrieve e again because list may have been realloc'd */
    e = elist_get(list, 4);

    ptrdiff_t fe_diff = f - e;
    test_assert(fe_diff == 22222);

    /* Make sure we can actually use the memory */
    a = elist_get(list, 0);
    ptrdiff_t fa_diff = f - a;
    memset(a, 0xAA, fa_diff);
    puts("\n");

    unsigned char *test = elist_get(list, 0);
    test_printf("%d (0xAA = 170 (unsigned))", *test);
    test_assert(*test == 0xAA);

    elist_destroy(list);
});

test_end
