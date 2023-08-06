/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:29:11 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 15:29:46 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_ep(t_long *l)
{
	if (l->matrix[l->x][l->y] == 'P')
		mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[1], l->y
			* 63, l->x * 63);
	if (l->matrix[l->w][l->s] == 'N')
		mlx_put_image_to_window(l->mx_init, l->mx_window, l->xpm_image[4], l->s
			* 63, l->w * 63);
}
