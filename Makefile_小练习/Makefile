src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall -g

all:$(targets)
$(targets):%:%.c 
	$(CC) $(CFLAGS) $< -o $@	

clean:
	-rm -rf $(targets)
.PHONY:clean all
