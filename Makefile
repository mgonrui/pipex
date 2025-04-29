CFILES = 	pipex.c \
			utils2.c \
			helper_funcs.c

OFILES = $(CFILES:.c=.o)

CC = gcc 
NAME = pipex
CFLAGS = -Wall -Wextra

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME) pipex.h
$(NAME): $(OFILES)
	@ $(CC) $(CFLAGS) $(OFILES) libft/libft.a -o $(NAME)


libft:
	@ make -C libft/

clean:
	@ rm -f $(OFILES)
	@ make -C libft/ clean

fclean: clean
	@ rm -f $(NAME)
	@ make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re libft
