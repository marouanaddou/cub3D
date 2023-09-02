/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 12:01:19 by maddou            #+#    #+#             */
/*   Updated: 2023/09/02 11:47:44 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	key_right_escape(t_cub *cub, int x)
{
	if (mlx_is_key_down(cub->mlx.init_ptr, MLX_KEY_RIGHT) || x > cub->mouse_x)
	{
		key_lr(cub, 1);
		cub->mouse_x = x;
	}
	else if (mlx_is_key_down(cub->mlx.init_ptr, MLX_KEY_LEFT)
		|| x < cub->mouse_x)
	{
		key_lr(cub, 0);
		cub->mouse_x = x;
	}
	if (mlx_is_key_down(cub->mlx.init_ptr, MLX_KEY_ESCAPE))
	{
		free_double_pointer(cub->par.map);
		free_double_pointer(cub->par.element);
		free_element(cub->par.elm);
		mlx_close_window(cub->mlx.init_ptr);
	}
}

void	loop_hook(void *cub)
{
	t_cub	*cu;
	int		x;

	cu = (t_cub *)cub;
	mlx_get_mouse_pos(cu->mlx.init_ptr, &x, &cu->mouse_y);
	if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_A) && check_wall(cub,
			(cu->par.y + (sin(cu->ray.first_angle - (M_PI / 2)) * 10)) / 30,
			((cu->par.x + (cos(cu->ray.first_angle - (M_PI / 2)) * 10))
				/ 30)) != 0)
		key_ad(cu, 0);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_W) && check_wall(cu,
			(cu->par.y + (sin(cu->ray.first_angle) * 10)) / 30, ((cu->par.x
					+ (cos(cu->ray.first_angle) * 10)) / 30)) != 0)
		key_ws(cu, 0);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_D) && check_wall(cub,
			(cu->par.y - (sin(cu->ray.first_angle - (M_PI / 2)) * 10)) / 30,
			((cu->par.x - (cos(cu->ray.first_angle - (M_PI / 2)) * 10))
				/ 30)) != 0)
		key_ad(cu, 1);
	else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_S) && check_wall(cub,
			(cu->par.y - (sin(cu->ray.first_angle) * 10)) / 30, (cu->par.x
				- (cos(cu->ray.first_angle) * 10)) / 30) != 0)
		key_ws(cu, 1);
	key_right_escape(cub, x);
}
