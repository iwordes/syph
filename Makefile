NAME  = ft_db

#

.PHONY: all
all: ft_db

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

