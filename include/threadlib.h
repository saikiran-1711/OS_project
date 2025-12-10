#ifndef THREADLIB_H
#define THREADLIB_H

#include <pthread.h>

typedef struct {
    pthread_t handle;
} tl_thread_t;

int tl_thread_create(tl_thread_t *thread, void *(*fn)(void *), void *arg);
int tl_thread_join(tl_thread_t *thread, void **retval);
int tl_thread_detach(tl_thread_t *thread);
void tl_thread_exit(void *retval);

#endif
