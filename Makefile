SRC = main.c ./includes/ft_nbr_base.c ./includes/ft_printf.c ./includes/ft_putchar.c ./includes/ft_putnbr.c ./includes/ft_putstr.c ./includes/ft_split.c ./includes/get_next_line_utils.c ./includes/get_next_line.c so_long_utils.c move.c map.c
NAME = so_long
CC = gcc
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -g3 -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) -fsanitize=address

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all