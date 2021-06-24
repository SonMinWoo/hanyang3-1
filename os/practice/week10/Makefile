CC=gcc
CFLAGS=-g -o
TARGETS=semaphore producer_consumer
all: $(TARGETS)
.PHONY: all
%:
	$(CC) $(CFLAGS) $@ $@.c -lpthread

clean:
	rm $(TARGETS)
