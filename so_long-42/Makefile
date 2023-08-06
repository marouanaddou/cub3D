NAME = so_long
NAME_BONUS = so_long_bonus
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf
SRC = so_long.c libft.c checkmap.c checkvalidpath.c so_long_utils.c \
		move_player.c so_long_utils1.c so_long_free.c
SRC_BONUS = so_long_bonus.c libft_bonus.c checkmap_bonus.c checkvalidpath_bonus.c so_long_utils_bonus.c \
		move_player_bonus.c so_long_utils1_bonus.c so_long_free_bonus.c sreach_enemy_bonus.c \
		put_ep_bonus.c ft_itoa.c put_move_bonus.c 
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ)  -lmlx -framework OpenGL -framework AppKit -o $@
%.o : %.c so_long.h 
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS)  -lmlx -framework OpenGL -framework AppKit -o $@
%.o : %.c so_long_bonus.h 
	@$(CC) $(CFLAGS) -c $< -o $@
clean :
	@$(RM) $(OBJ) $(OBJ_BONUS)
fclean : clean
	@$(RM) $(NAME) $(NAME_BONUS)
re : fclean all
.PHONY : all fclean clean re 