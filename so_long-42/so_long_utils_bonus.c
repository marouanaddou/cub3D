/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:18:31 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:19:04 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	exit_play(int keycode, t_long *l)
{
	if (l->x == l->w && l->y == l->s)
		game_over(l);
	if (keycode == 13 && l->matrix[l->x][l->y] != '1')
	{
		if (l->matrix[l->x][l->y] == 'E')
		{
			l->cont_move++;
			put_nbr(l->cont_move);
			write(1, "\n", 1);
			game_over(l);
		}
	}
	else if (keycode == 2 && l->matrix[l->x][l->y] != '1')
	{
		if (l->matrix[l->x][l->y] == 'E')
		{
			l->cont_move++;
			put_nbr(l->cont_move);
			write(1, "\n", 1);
			game_over(l);
		}
	}
	check_exit_player(keycode, l);
}

int	key_hok(int keycode, t_long *l)
{
	t_mlx	mlx;

	if (keycode == 13 && l->matrix[l->x - 1][l->y] != '1')
		move_top(l, &mlx);
	else if (keycode == 2 && l->matrix[l->x][l->y + 1] != '1')
		move_right(l, &mlx);
	else if (keycode == 1 && l->matrix[l->x + 1][l->y] != '1')
		move_bottom(l, &mlx);
	else if (keycode == 0 && l->matrix[l->x][l->y - 1] != '1')
		move_left(l, &mlx);
	else if (keycode == 53)
		game_over(l);
	if ((check_coins(l) == 1 && l->matrix[l->x][l->y] == 'E') ||
		(l->x == l->w && l->y == l->s))
		exit_play(keycode, l);
	return (0);
}

void	put_image(t_long *l, t_mlx *mlx)
{
	mlx_function(l, mlx);
	while (l->matrix[l->i] != NULL)
	{
		l->j = 0;
		while (l->matrix[l->i][l->j] != '\0')
		{
			if (l->matrix[l->i][l->j] == '1')
				mlx_put_image_to_window(l->mx_init, l->mx_window,
					l->xpm_image[0], l->j * 63, l->i * 63);
			else if (l->matrix[l->i][l->j] == 'C')
				mlx_put_image_to_window(l->mx_init, l->mx_window,
					l->xpm_image[2], l->j * 63, l->i * 63);
			else if (l->matrix[l->i][l->j] == 'E')
				mlx_put_image_to_window(l->mx_init, l->mx_window,
					l->xpm_image[3], l->j * 63, l->i * 63);
			l->j++;
		}
		l->i++;
	}
	put_ep(l);
}
