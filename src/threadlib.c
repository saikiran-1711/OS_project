#include "../include/threadlib.h"
#include <pthread.h>

int tl_thread_create(tl_thread_t *thread, void *(*fn)(void *), void *arg) {
    return pthread_create(&thread->handle, NULL, fn, arg);
}

int tl_thread_join(tl_thread_t *thread, void **retval) {
    return pthread_join(thread->handle, retval);
}

int tl_thread_detach(tl_thread_t *thread) {
    return pthread_detach(thread->handle);
}

void tl_thread_exit(void *retval) {
    pthread_exit(retval);
}
