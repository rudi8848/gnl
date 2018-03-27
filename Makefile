NAME = gnl
LIB = libft/libft.a
SRC = get_next_line.c main.c
OBJ = get_next_line.o main.o

all: $(NAME) $(LIB)

$(NAME): $(LIB)
	gcc -o $(NAME) $(SRC) -g3 -L. $(LIB)

$(LIB):
	make -C libft
