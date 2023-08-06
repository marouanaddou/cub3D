/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:22:22 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:11:01 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	game_over(t_long *l)
{
	free_image(l);
	exit(0);
}

int	check_coins(t_long *l)
{
	int	i;
	int	j;

	i = 0;
	while (l->matrix[i] != NULL)
	{
		j = 0;
		while (l->matrix[i][j] != '\0')
		{
			if (l->matrix[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	mlx_function(t_long *l, t_mlx *mlx)
{
	l->xpm_image[0] = mlx_xpm_file_to_image(l->mx_init, "textures/wall.xpm",
			&mlx->width, &mlx->height);
	l->xpm_image[1] = mlx_xpm_file_to_image(l->mx_init, "textures/player.xpm",
			&mlx->width, &mlx->height);
	l->xpm_image[2] = mlx_xpm_file_to_image(l->mx_init, "textures/coins1.xpm",
			&mlx->width, &mlx->height);
	l->xpm_image[3] = mlx_xpm_file_to_image(l->mx_init, "textures/exit-3.xpm",
			&mlx->width, &mlx->height);
	l->xpm_image[4] = mlx_xpm_file_to_image(l->mx_init, "textures/enemy_so.xpm",
			&mlx->width, &mlx->height);
	if (l->xpm_image[0] == NULL || l->xpm_image[1] == NULL
		|| l->xpm_image[2] == NULL || l->xpm_image[3] == NULL
		|| l->xpm_image[4] == NULL)
	{
		free_image(l);
		exit(1);
	}
}

void	calcul_element(t_long *l)
{
	l->u = 0;
	while (l->matrix[l->u] != NULL)
	{
		l->v = 0;
		while (l->matrix[l->u][l->v] != '\0')
			l->v++;
		l->u++;
	}
}

void	check_exit_player(int keycode, t_long *l)
{
	if (keycode == 1 && l->matrix[l->x][l->y] != '1')
	{
		if (l->matrix[l->x][l->y] == 'E')
		{
			l->cont_move++;
			put_nbr(l->cont_move);
			write(1, "\n", 1);
			game_over(l);
		}
	}
	else if (keycode == 0 && l->matrix[l->x][l->y] != '1')
	{
		if (l->matrix[l->x][l->y] == 'E')
		{
			l->cont_move++;
			put_nbr(l->cont_move);
			write(1, "\n", 1);
			game_over(l);
		}
	}
}
