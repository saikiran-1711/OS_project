#include "../include/threadpool.h"
#include <stdlib.h>
#include <pthread.h>

static void *worker_thread(void *arg) {
    tl_threadpool_t *pool = arg;

    while (1) {
        pthread_mutex_lock(&pool->lock);

        while (pool->task_head == NULL && !pool->stop)
            pthread_cond_wait(&pool->cond, &pool->lock);

        if (pool->stop) {
            pthread_mutex_unlock(&pool->lock);
            pthread_exit(NULL);
        }

        tl_task_t *task = pool->task_head;
        pool->task_head = task->next;
        if (pool->task_head == NULL) pool->task_tail = NULL;

        pthread_mutex_unlock(&pool->lock);

        task->fn(task->arg);
        free(task);
    }
}

tl_threadpool_t *tl_pool_create(int num_threads) {
    tl_threadpool_t *pool = malloc(sizeof(tl_threadpool_t));
    pool->num_threads = num_threads;
    pool->workers = malloc(sizeof(pthread_t) * num_threads);
    pool->task_head = pool->task_tail = NULL;
    pool->stop = 0;

    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);

    for (int i = 0; i < num_threads; i++)
        pthread_create(&pool->workers[i], NULL, worker_thread, pool);

    return pool;
}

void tl_pool_submit(tl_threadpool_t *pool, void (*fn)(void *), void *arg) {
    tl_task_t *task = malloc(sizeof(tl_task_t));
    task->fn = fn;
    task->arg = arg;
    task->next = NULL;

    pthread_mutex_lock(&pool->lock);

    if (pool->task_tail == NULL)
        pool->task_head = pool->task_tail = task;
    else {
        pool->task_tail->next = task;
        pool->task_tail = task;
    }

    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->lock);
}

void tl_pool_destroy(tl_threadpool_t *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->lock);

    for (int i = 0; i < pool->num_threads; i++)
        pthread_join(pool->workers[i], NULL);

    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cond);

    free(pool->workers);
    free(pool);
}
