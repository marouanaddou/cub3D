NAME = cub3D
NAME_B = cub3D_bonus
CC = cc
FLAGC = -Wall  -Wextra -Werror -I./libft
SRC = mandatory_part/cub3D.c mandatory_part/raycasting.c mandatory_part/raycasting_utils.c mandatory_part/textels.c mandatory_part/draw_minimap_fc.c mandatory_part/key_hook.c mandatory_part/free_all.c parsing/valid_map.c parsing/check_file.c parsing/load_map.c parsing/check_information.c parsing/check_map.c parsing/map_len.c parsing/check_error_information.c parsing/check_error_information_utils.c parsing/split_newline_information.c \
	libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_isdigit.c\
	libft/ft_calloc.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_strnstr.c libft/ft_strtrim.c libft/ft_strcmp.c libft/ft_atoi.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

BONUS = bonus_part/cub3D_bonus.c bonus_part/raycasting_bonus.c bonus_part/raycasting_utils_bonus.c bonus_part/textels_bonus.c bonus_part/draw_minimap_fc_bonus.c bonus_part/key_hook_bonus.c bonus_part/free_all_bonus.c parsing/valid_map.c parsing/check_file.c parsing/load_map.c parsing/check_information.c parsing/check_map.c parsing/map_len.c parsing/check_error_information.c parsing/check_error_information_utils.c parsing/split_newline_information.c \
	libft/ft_split.c libft/ft_substr.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_isdigit.c\
	libft/ft_calloc.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_strnstr.c libft/ft_strtrim.c libft/ft_strcmp.c libft/ft_atoi.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

all:  $(NAME) 
bonus :  $(NAME_B)


$(NAME):$(OBJ)
	$(CC) $(FLAGC) -framework Cocoa -framework OpenGL -framework IOKit $(SRC) mlx42/libmlx42.a ~/lib/libglfw3.a -o $(NAME) 
$(NAME_B):$(OBJ_BONUS)
	$(CC) $(FLAGC) -framework Cocoa -framework OpenGL -framework IOKit $(BONUS) mlx42/libmlx42.a ~/lib/libglfw3.a -o $(NAME_B)
%.o:%.c cub3d.h
	$(CC) $(FLAGC) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean: clean
	rm -rf $(NAME) $(NAME_B)
re: fclean all