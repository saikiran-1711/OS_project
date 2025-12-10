#include "../include/threadpool.h"
#include <stdio.h>
#include <stdlib.h>

void task(void *arg) {
    int *x = arg;
    printf("Task executed: %d\n", *x);
}

int main() {
    tl_threadpool_t *pool = tl_pool_create(4);

    for (int i = 0; i < 20; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        tl_pool_submit(pool, task, val);
    }

    tl_pool_destroy(pool);
    return 0;
}
