#include "../include/threadlib.h"
#include <stdio.h>

void *run(void *arg) {
    int *x = arg;
    printf("Hello from thread %d\n", *x);
    return NULL;
}

int main() {
    tl_thread_t t[5];
    int values[] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++)
        tl_thread_create(&t[i], run, &values[i]);

    for (int i = 0; i < 5; i++)
        tl_thread_join(&t[i], NULL);

    return 0;
}
