/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_fc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:45:31 by maddou            #+#    #+#             */
/*   Updated: 2023/08/29 20:47:25 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(t_cub *cub)
{
	cub->i = 0;
	cub->j = 0;
	while (cub->i < WIDTH)
	{
		cub->j = 0;
		while (cub->j < HEIGHT)
		{
			if (cub->j < HEIGHT / 2)
				mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j,
					cub->par.ceiling);
			else
				mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j, cub->par.floor);
			cub->j++;
		}
		cub->i++;
	}
	cub->i = 0;
	cub->j = 0;
}

void	draw_wall(t_cub *cub)
{
	int	put1;
	int	put2;

	put1 = 0;
	while (put1 < 30)
	{
		put2 = 0;
		while (put2 < 30)
		{
			mlx_put_pixel(cub->mlx.img_ptr,
				MINIMAP_SCALE_FACTOR * ((cub->j * 30) + put1),
				MINIMAP_SCALE_FACTOR * ((cub->i * 30) + put2),
				0x6a);
			put2++;
		}
		put1++;
	}
}

void	wall_in_image(t_cub *cub)
{
	while (cub->par.map[cub->i] != NULL)
	{
		cub->j = 0;
		while (cub->par.map[cub->i][cub->j] != '\0')
		{
			if (cub->par.map[cub->i][cub->j] == '1')
				draw_wall(cub);
			cub->j++;
		}
		cub->i++;
	}
}

void	draw_white_in_image(t_cub *cub)
{
	cub->i = 0;
	cub->j = 0;
	while (cub->i < (cub->mlx.width * 30  * MINIMAP_SCALE_FACTOR))
	{
		cub->j = 0;
		while (cub->j < (cub->mlx.height * 30 * MINIMAP_SCALE_FACTOR))
		{
			mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j, 0xffffffff);
			cub->j++;
		}
		cub->i++;
	}
	cub->i = 0;
	cub->j = 0;
}

void	draw_minimap(void *cub)
{
	t_cub	*cu;

	cu = (t_cub *)cub;
	draw_white_in_image(cu);
	wall_in_image(cu);
	find_point(cu);
	cast_rays(cu);
	mlx_put_pixel(cu->mlx.img_ptr, MINIMAP_SCALE_FACTOR * (cu->par.x),
		MINIMAP_SCALE_FACTOR * (cu->par.y), 0xC41E3A);
}
