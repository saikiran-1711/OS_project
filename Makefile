CC = gcc
CFLAGS = -pthread -Iinclude -Wall -Wextra

SRCS = src/threadlib.c src/threadpool.c src/sync.c

all: example_basic example_pool

example_basic: $(SRCS) examples/example_basic_threads.c
	$(CC) $(CFLAGS) -o example_basic examples/example_basic_threads.c $(SRCS)

example_pool: $(SRCS) examples/example_threadpool.c
	$(CC) $(CFLAGS) -o example_pool examples/example_threadpool.c $(SRCS)

test:
	$(CC) $(CFLAGS) -o test_pool tests/test_threadpool_stress.c $(SRCS)

clean:
	rm -f example_basic example_pool test_pool

