NAME    = syphd
VERSION = 0.1.0

LIBS   := arg tp

CC      = gcc
CF     += -Wall -Wextra -Werror
CF     += -I include -I lib/arg -I lib/tp/include
CF     += $(foreach lib,$(LIBS),-L lib/$(lib) -l$(lib))

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

LIBS := $(addsuffix .a,$(LIB))

$(NAME): $(SRC) $(LIBS)
	$(CC) $(CF) -o $@ $(SRC)

%.a:
	make -C $(@D)
