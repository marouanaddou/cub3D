/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:42:13 by mel-gand          #+#    #+#             */
/*   Updated: 2023/08/30 00:48:12 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"


int check_holes(t_cub *cub, float prev_x, float prev_y)
{
	if ((cub->par.map[((int)(cub->ray.y_ver / 30))][(int)prev_x / 30] == '1' &&
			 cub->par.map[(int)prev_y / 30][(int)(cub->ray.x_hor / 30)] == '1') ||
			cub->par.map[(int)floor(cub->ray.y_ver) / 30]
									[(int)floor(cub->ray.x_hor) / 30] == '1')
		return (1);
	return (0);
}
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

void cast_rays(t_cub *cub) {
	int i;
	bool check;

	i = 0;
	while (i < WIDTH) {
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
			cub->ray.x_hor += cub->ray.x_inc;
			cub->point[i].x_end = cub->ray.x_hor;
			if (cub->par.map[(int)floor(cub->point[i].y_end) / 30][(int)floor(cub->point[i].x_end) / 30] == '1')
			{
				check = true;
				cub->point[i].view = LEFT_RIGHT;
				if (cos(cub->point[i].angle) >= 0)
					cub->point[i].direction = RIGHT;
				else
					cub->point[i].direction = LEFT;
			}
			cub->ray.y_ver += cub->ray.y_inc;
			cub->point[i].y_end = cub->ray.y_ver;
			if (cub->par.map[(int)floor(cub->point[i].y_end )/ 30][(int)floor(cub->point[i].x_end) / 30] == '1' && check == false)
			{
				cub->point[i].view = TOP_BOTTOM;
				if (sin(cub->point[i].angle) >= 0)
					cub->point[i].direction = TOP;
				else
					cub->point[i].direction = BOTTOM;
			}
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