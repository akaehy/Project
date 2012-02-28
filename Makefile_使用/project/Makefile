src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = 

all:$(targets)
$(targets):%:%.c
	$(CC) $(CFLAGS) $< -o $@

project:
	make -C test
project-clean:
	make -C test clean
clean:
	@echo "clean"
	-rm -rf $(targets)

.PHONY:clean all
