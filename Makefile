NAME = cub3D
CC = cc
FLAGC = -Wall  -Wextra -Werror -I./libft -fsanitize=address -g -O3
SRC = cub3D.c raycasting.c textels.c draw_minimap_fc.c key_hook.c free_all.c parsing/valid_map.c parsing/check_file.c parsing/load_map.c parsing/check_information.c parsing/check_map.c parsing/map_len.c parsing/check_error_information.c parsing/check_error_information_utils.c parsing/split_newline_information.c \
	libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_isdigit.c\
	libft/ft_calloc.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_strnstr.c libft/ft_strtrim.c libft/ft_strcmp.c libft/ft_atoi.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 
OBJ = $(SRC:.c=.o)

all: mlx $(NAME)
mlx:
	make -C mlx42

$(NAME):$(OBJ)
	$(CC) $(FLAGC) -framework Cocoa -framework OpenGL -framework IOKit $(SRC) ./mlx42/libmlx42.a ~/lib/libglfw3.a -o $(NAME) 

%.o:%.c cub3d.h
	$(CC) $(FLAGC) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME) ./mlx42/libmlx42.a
re: fclean all