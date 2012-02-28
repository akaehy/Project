src = $(wildcard ./src/*.c)

src_obj = $(subst ./src, ./obj, $(src))
all_obj = $(patsubst %.c, %.o, $(src_obj))
no_include = ./obj/main.o
objs = $(filter-out $(no_include), $(all_obj))

libfile = lib/libstr.a

CC = gcc
CPPFLAGS = -I./include
CFLAGS = -Wall -g -c
LDFLAGS = -L./lib -lstr


all:main
main: obj/main.o $(libfile)
	$(CC) $^ $(LDFLAGS) -o $@
$(libfile):$(objs)
	ar rs $@ $^
$(all_obj):./obj/%.o:./src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -c -o $@

show:
	@echo $(objs)
clean:
	-rm -rf $(all_obj) $(libfile) main
.PHONY:all clean show


