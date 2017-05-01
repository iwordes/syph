NAME  = libtp.a

CC   := gcc
CF   += -Wall -Wextra -Werror
CF   += -I include

HEAD := $(addprefix include/,libtp.h libtp_.h)

SRC  := bzero.c kill_thread.c work_loop.c zalloc.c
SRC  += create.c exec_queue_add.c wait_for_queue.c
SRC  += get_nbr_proc.c
SRC  += destroy.c evfire.c evwait.c lock.c locked.c unlock.c ncpu.c
SRC  += qpop.c qpush.c qwait.c
OBJ  := $(addprefix build/,$(SRC:.c=.o))
SRC  := $(addprefix src/,$(SRC))

# ------------------------------------------------------------------------------

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

# ------------------------------------------------------------------------------

$(NAME): $(OBJ)
	libtool -static -o $@ $^

build/%.o: src/%.c $(HEAD)
	@mkdir -p $(@D)
	$(CC) $(CF) -c -o $@ $<
