src = $(wildcard *.c)
objs = $(patsubst %.c, %.o, $(src))

CC = gcc 
CFLAGS = -Wall -g -c

all:$(objs)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) $< -o $@
clean:
	-rm -rf $(objs) main
.PHONY:clean all
