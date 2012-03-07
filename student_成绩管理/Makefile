src 	= $(wildcard *.c)
target 	= $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS 	= -Wall -g
LDFLAGS = -lm

all: $(target)

clean:
	-rm -f $(target)

.PHINY: all clean

