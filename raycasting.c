/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:42:13 by mel-gand          #+#    #+#             */
/*   Updated: 2023/08/30 16:27:01 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void calculate_slope(int i, t_cub *cub) 
{
	float dx;
    float dy;
    int step;

    dx = cub->point[i].x_end;
    dy = cub->point[i].y_end;
    step = (int)(fabs(dx) + fabs(dy));
	cub->ray.x_inc = dx / step;
	cub->ray.y_inc = dy / step;
}

void cast_rays(t_cub *cub)
{
	int i;
	bool check;

	i = 0;
	while (i < WIDTH)
	{
		calculate_slope(i, cub);
		cub->ray.x_hor = cub->par.x;
		cub->ray.y_ver = cub->par.y;
		while (1) 
		{
			check = false;
			if (check_holes(cub, cub->ray.x_hor - cub->ray.x_inc,
											cub->ray.y_ver - cub->ray.y_inc) == 1)
				break;
			mlx_put_pixel(cub->mlx.img_ptr, MINIMAP_SCALE_FACTOR * cub->ray.x_hor,
						MINIMAP_SCALE_FACTOR * cub->ray.y_ver, 0xAA4A44);
			cast_rays_utils(cub, i, check);
		}
		i++;
	}
}

void find_point(t_cub *cub) {
	int i;

	i = 0;
	cub->point = malloc(sizeof(t_point) * WIDTH);
	double angle = 0;
	while (i < WIDTH)
	{
		cub->point[i].x_end = cos(angle + (cub->ray.first_angle - (DEGREE / 2)));
		cub->point[i].y_end = sin(angle + (cub->ray.first_angle - (DEGREE / 2)));
		cub->point[i].angle = angle + cub->ray.first_angle - (DEGREE / 2);
		angle += ANGLE_INCREMENT;
		i++;
	}
}