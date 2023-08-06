/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:08:03 by maddou            #+#    #+#             */
/*   Updated: 2023/03/31 17:54:52 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "mlx/mlx.h"
#include "so_long.h"

void	free_image(t_long *l)
{
	int	i;

	i = 0;
	mlx_destroy_window(l->mx_init, l->mx_window);
	while (i <= 3)
	{
		if (l->xpm_image[i] != NULL)
			free(l->xpm_image[i]);
		i++;
	}
	free_split(l->matrix);
}
