CC = gcc
CFLAGS = -pthread -Iinclude

SRC = src/threadlib.c src/threadpool.c src/sync.c

all: examples

examples: $(SRC)
	$(CC) $(CFLAGS) -o example_basic examples/example_basic_threads.c $(SRC)
	$(CC) $(CFLAGS) -o example_pool examples/example_threadpool.c $(SRC)

test:
	$(CC) $(CFLAGS) -o test_pool tests/test_threadpool_stress.c $(SRC)

clean:
	rm -f example_basic example_pool test_pool
