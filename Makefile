NAME    = syphd
VERSION = 0.1.0

CC    = gcc
CF   += -Wall -Wextra -Werror

include src.mk

# ==============================================================================

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

# ==============================================================================

$(NAME): $(SRC)
	$(CC) $(CF) -o $@ $(SRC)
