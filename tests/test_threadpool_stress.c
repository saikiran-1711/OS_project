#include "../include/threadpool.h"
#include <stdio.h>
#include <stdlib.h>

void heavy(void *arg) {
    int *x = arg;
    printf("Running task: %d\n", *x);
}

int main() {
    tl_threadpool_t *pool = tl_pool_create(8);

    for (int i = 0; i < 10000; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        tl_pool_submit(pool, heavy, val);
    }

    tl_pool_destroy(pool);
    return 0;
}
