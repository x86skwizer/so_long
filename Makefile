SRC = main.c ft_nbr_base.c ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_split.c get_next_line_utils.c get_next_line.c so_long_utils.c 
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