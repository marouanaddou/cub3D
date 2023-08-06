CC = gcc
FLAGC = -Wall  -Wextra -Werror -fsanitize=address -I./libft
SRC = cub3D.c parsing/check_file.c parsing/check_map.c \
	libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_calloc.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_strnstr.c\

OBJ = $(SRC:.c=.o)
NAME = cub3D

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGC) $(SRC) -o $(NAME)

%.o:%.c 
	$(CC) $(FLAGC) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean	
	rm -rf $(NAME)
re: fclean all