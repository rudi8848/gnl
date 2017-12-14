NAME = get_next_line
SRC = get_next_line.c main.c
OBJ = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	gcc -Wall -Wextra -Werror -L. $(OBJ) $(LIBFT) $(SRC) -o $(NAME) 

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

