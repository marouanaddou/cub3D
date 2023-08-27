/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:01:19 by maddou            #+#    #+#             */
/*   Updated: 2023/08/26 12:43:09 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_ad(t_cub *cub, int sign)
{
	if (sign == 0)
	{
		cub->par.x += cos(cub->ray.first_angle - (M_PI / 2));
		cub->par.y += sin(cub->ray.first_angle - (M_PI / 2));
	}
	else
	{
		cub->par.x -= cos(cub->ray.first_angle - (M_PI / 2));
		cub->par.y -= sin(cub->ray.first_angle - (M_PI / 2));
	}
	draw_fc(cub);
	draw_view(cub);
}

void	key_ws(t_cub *cub, int sign)
{
	if (sign == 0)
	{
		cub->par.x += cos(cub->ray.first_angle);
		cub->par.y += sin(cub->ray.first_angle);
	}
	else
	{
		cub->par.x -= cos(cub->ray.first_angle);
		cub->par.y -= sin(cub->ray.first_angle);
	}
	draw_fc(cub);
	draw_view(cub);
}

void	key_lr(t_cub *cub, int sign)
{
	if (sign == 0)
		cub->ray.first_angle -= 0.10;
	else
		cub->ray.first_angle += 0.10;
	if (cub->ray.first_angle > 2 * M_PI)
		cub->ray.first_angle -= 2 * M_PI;
	if (cub->ray.first_angle < 0)
		cub->ray.first_angle += 2 * M_PI;
	draw_fc(cub);
	draw_view(cub);
}

void	key_right_escape(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx.init_ptr, MLX_KEY_RIGHT))
		key_lr(cub, 1);
	if (mlx_is_key_down(cub->mlx.init_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx.init_ptr);
}

void	loop_hook(void *cub)
{
	t_cub	*cu;

	cu = (t_cub *)cub;
	if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_A)
		&& check_wall(cub, cu->par.x + cos(cu->ray.first_angle - (M_PI / 2)),
			cu->par.y + sin(cu->ray.first_angle - (M_PI / 2))) != 0)
		key_ad(cu, 0);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_W) 
		&& check_wall(cub, cu->par.x + cos(cu->ray.first_angle), cu->par.y
			+ sin(cu->ray.first_angle)) != 0)
		key_ws(cu, 0);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_D)
		&& check_wall(cub, cu->par.x - cos(cu->ray.first_angle - (M_PI
					/ 2)), cu->par.y - sin(cu->ray.first_angle
				- (M_PI / 2))) != 0)
		key_ad(cu, 1);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_S) 
		&& check_wall(cub, cu->par.x - cos(cu->ray.first_angle), cu->par.y
			- sin(cu->ray.first_angle)) != 0)
		key_ws(cu, 1);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_LEFT))
		key_lr(cu, 0);
	key_right_escape(cub);
}
