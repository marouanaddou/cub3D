/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:15:17 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:16:00 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_nbr(int nb)
{
	int		i;
	char	c;

	i = 0;
	if (nb > 9)
	{
		put_nbr(nb / 10);
		put_nbr(nb % 10);
	}
	if (nb >= 0 && nb <= 9)
	{
		c = nb + 48;
		write(1, &c, 1);
	}
}

void	move_top(t_long *l, t_mlx *mlx)
{
	l->cont_move++;
	put_nbr(l->cont_move);
	write(1, "\n", 1);
	if (l->x - 1 == l->w && l->y == l->s)
		game_over(l);
	mlx_clear_window(l->mx_init, l->mx_window);
	l->x -= 1;
	if (l->matrix[l->w + 1][l->s] != '1')
		l->w += 1;
	l->i = 0;
	l->j = 0;
	if (l->matrix[l->x][l->y] == 'C')
		l->matrix[l->x][l->y] = '0';
	put_image(l, mlx);
	mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[1], l->y
		* 63, l->x * 63);
	if (l->matrix[l->w][l->s] != '1')
		mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[4], l->s
			* 63, l->w * 63);
	put_cont(l);
}

void	move_right(t_long *l, t_mlx *mlx)
{
	l->cont_move++;
	put_nbr(l->cont_move);
	write(1, "\n", 1);
	if (l->x == l->w && l->y + 1 == l->s)
		game_over(l);
	mlx_clear_window(l->mx_init, l->mx_window);
	l->y += 1;
	if (l->matrix[l->w][l->s - 1] != '1')
		l->s -= 1;
	l->i = 0;
	l->j = 0;
	if (l->matrix[l->x][l->y] == 'C')
		l->matrix[l->x][l->y] = '0';
	put_image(l, mlx);
	mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[1], l->y
		* 63, l->x * 63);
	if (l->matrix[l->w][l->s] != '1')
		mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[4], l->s
			* 63, l->w * 63);
	put_cont(l);
}

void	move_bottom(t_long *l, t_mlx *mlx)
{
	l->cont_move++;
	put_nbr(l->cont_move);
	write(1, "\n", 1);
	if (l->x + 1 == l->w && l->y == l->s)
		game_over(l);
	mlx_clear_window(l->mx_init, l->mx_window);
	l->x += 1;
	if (l->matrix[l->w - 1][l->s] != '1')
		l->w -= 1;
	l->i = 0;
	l->j = 0;
	if (l->matrix[l->x][l->y] == 'C')
		l->matrix[l->x][l->y] = '0';
	put_image(l, mlx);
	mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[1], l->y
		* 63, l->x * 63);
	if (l->matrix[l->w][l->s] != '1')
		mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[4], l->s
			* 63, l->w * 63);
	put_cont(l);
}

void	move_left(t_long *l, t_mlx *mlx)
{
	l->cont_move++;
	put_nbr(l->cont_move);
	write(1, "\n", 1);
	if (l->x == l->w && l->y - 1 == l->s)
		game_over(l);
	mlx_clear_window(l->mx_init, l->mx_window);
	l->y -= 1;
	if (l->matrix[l->w][l->s + 1] != '1')
		l->s += 1;
	l->i = 0;
	l->j = 0;
	if (l->matrix[l->x][l->y] == 'C')
		l->matrix[l->x][l->y] = '0';
	put_image(l, mlx);
	mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[1], l->y
		* 63, l->x * 63);
	if (l->matrix[l->w][l->s] != '1')
		mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[4], l->s
			* 63, l->w * 63);
	put_cont(l);
}
