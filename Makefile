CFILES = pipex.c 


OFILES = $(CFILES:.c=.o)

CC = clang
NAME = pipex
CFLAGS = -Wall -Werror -Wextra

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME)
$(NAME): $(OFILES)
	@ $(CC) $(CFLAGS) $(OFILES) ../libft/libft.a -o $(NAME)


libft:
	@ make -C ../libft/

clean:
	@ rm -f $(OFILES)
	@ make -C libft/ clean

fclean: clean
	@ rm -f $(NAME)
	@ make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re libft
