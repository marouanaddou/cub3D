/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:25:29 by mel-gand          #+#    #+#             */
/*   Updated: 2023/08/30 16:25:50 by mel-gand         ###   ########.fr       */
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

void	left_right_direction(t_cub *cub, int i, bool *check)
{
	*check = true;
	cub->point[i].view = LEFT_RIGHT;
	if (cos(cub->point[i].angle) >= 0)
		cub->point[i].direction = RIGHT;
	else
		cub->point[i].direction = LEFT;
}

void	top_bottom_direction(t_cub *cub, int i)
{
	cub->point[i].view = TOP_BOTTOM;
	if (sin(cub->point[i].angle) >= 0)
		cub->point[i].direction = TOP;
	else
		cub->point[i].direction = BOTTOM;
}
void	cast_rays_utils(t_cub *cub, int i, bool check)
{
	cub->ray.x_hor += cub->ray.x_inc;
	cub->point[i].x_end = cub->ray.x_hor;
	if (cub->par.map[(int)floor(cub->point[i].y_end) / 30][(int)floor(cub->point[i].x_end) / 30] == '1')
		left_right_direction(cub, i, &check);
	cub->ray.y_ver += cub->ray.y_inc;
	cub->point[i].y_end = cub->ray.y_ver;
	if (cub->par.map[(int)floor(cub->point[i].y_end )/ 30][(int)floor(cub->point[i].x_end) / 30] == '1' 
			&& check == false)
		top_bottom_direction(cub, i);
}