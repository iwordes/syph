NAME = libsyph.a

CC   = gcc
CF   = -Wall -Wextra -Werror -I include

SRC  = connect.c create.c delete.c insert.c select.c types.c update.c
SRC += z_connit.c z_read.c

OBJ := $(addprefix build/,$(SRC:.c=.o))
SRC := $(addprefix src/,$(SRC))

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

$(NAME): $(OBJ)
	libtool -static -o $@ $^

build/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CF) -c -o $@ $<
