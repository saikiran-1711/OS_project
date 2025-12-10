#include "../include/sync.h"

void tl_mutex_init(tl_mutex_t *m) { pthread_mutex_init(m, NULL); }
void tl_mutex_lock(tl_mutex_t *m) { pthread_mutex_lock(m); }
void tl_mutex_unlock(tl_mutex_t *m) { pthread_mutex_unlock(m); }
void tl_mutex_destroy(tl_mutex_t *m) { pthread_mutex_destroy(m); }

void tl_cond_init(tl_cond_t *c) { pthread_cond_init(c, NULL); }
void tl_cond_wait(tl_cond_t *c, tl_mutex_t *m) { pthread_cond_wait(c, m); }
void tl_cond_signal(tl_cond_t *c) { pthread_cond_signal(c); }
void tl_cond_broadcast(tl_cond_t *c) { pthread_cond_broadcast(c); }
void tl_cond_destroy(tl_cond_t *c) { pthread_cond_destroy(c); }
