NAME    = syphd
VERSION = 0.1.0

LIBS   := arg

CC      = gcc
CF     += -Wall -Wextra -Werror
CF     += -I include
CF     += $(foreach lib,$(LIBS),-I lib/$(lib)/include -L lib/$(lib) -l$(lib))

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
