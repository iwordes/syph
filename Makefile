NAME    = syphd
VERSION = 0.9.0

CC      = gcc
CF     += -Wall -Wextra -Werror
CF     += -I include -I lib/tp/include
CF     += -L lib/tp -ltp

include src.mk

# ==============================================================================

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -rf build
	make -C lib/tp fclean

.PHONY: fclean
fclean: clean
	rm -f syphd

.PHONY: re
re: fclean all

# ==============================================================================

LIBS := $(addsuffix .a,$(LIB))

$(NAME): $(SRC) lib/tp/libtp.a
	$(CC) $(CF) -g -o $@ $(SRC)

%.a:
	make -C $(@D)
