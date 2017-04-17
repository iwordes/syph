NAME  = syph

CC    = gcc
CF   += -Wall -Wextra -Werror

SRC   = main.c

# -----------------------------------------------------------------------------

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -f ft_db

.PHONY: re
re: fclean all

#

$(NAME): include/db.h $(SRC)
	$(CC) $(CF) -o $@ $(SRC)

