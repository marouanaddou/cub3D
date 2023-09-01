/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textels.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:41 by mel-gand          #+#    #+#             */
/*   Updated: 2023/09/01 12:46:54 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	fill_texture_colors(t_cub *cub, uint32_t **texture, uint32_t *x,
		uint32_t *y)
{
	texture[*x][(*y)++] = ft_pixel(cub->txt->pixels[cub->i],
			cub->txt->pixels[cub->i + 1], cub->txt->pixels[cub->i + 2],
			cub->txt->pixels[cub->i + 3]);
	if (*y == cub->txt->width)
	{
		(*x)++;
		*y = 0;
	}
}

uint32_t	**fill_in_texture(t_cub *cub, uint32_t **texture)
{
	uint32_t	x;
	uint32_t	y;

	cub->i = 0;
	x = 0;
	y = 0;
	texture = malloc(sizeof(uint32_t *) * cub->txt->height);
	if (!texture)
		return (0);
	while (cub->i < (int)cub->txt->height)
	{
		texture[cub->i] = malloc(sizeof(uint32_t) * cub->txt->width);
		if (!texture[cub->i])
			return (0);
		cub->i++;
	}
	cub->i = 0;
	while (cub->i < (int)(cub->txt->height * cub->txt->width
		* cub->txt->bytes_per_pixel))
	{
		fill_texture_colors(cub, texture, &x, &y);
		cub->i += 4;
	}
	return (texture);
}

void	left_right_textures(t_cub *cub)
{
	cub->txt = mlx_load_png(cub->par.texture_path[3]/*"textures/BRICK_1A.PNG"*/);
	if (!cub->txt)
		exit(1);
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		exit(1);
	cub->right_texture = fill_in_texture(cub, cub->right_texture);
	cub->txt = mlx_load_png(cub->par.texture_path[2]/*"textures/BRICK_2B.PNG"*/);
	if (!cub->txt)
		exit(1);
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		exit(1);
	cub->left_texture = fill_in_texture(cub, cub->left_texture);
}

void	load_texture(t_cub *cub, int i, char c)
{
	cub->txt = mlx_load_png(cub->par.texture_path[i]/*"textures/BRICK_3B.PNG"*/);
	if (!cub->txt)
	{
		free_double_pointer(cub->par.map);
		free_double_pointer(cub->par.element);
		free_element(cub->par.elm);
		exit (1);
	}
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return ;
	if (c == )
}

void	load_textures(t_cub *cub)
{
	left_right_textures(cub);
	cub->txt = mlx_load_png(cub->par.texture_path[1]/*"textures/BRICK_3B.PNG"*/);
	if (!cub->txt)
	{
		free_double_pointer(cub->par.map);
		free_double_pointer(cub->par.element);
		free_element(cub->par.elm);
		return ;
	}
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return ;
	cub->top_texture = fill_in_texture(cub, cub->top_texture);
	cub->txt = mlx_load_png(cub->par.texture_path[0]/*"textures/BRICK_3D.PNG"*/);
	if (!cub->txt)
		return ;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return ;
	cub->bottom_texture = fill_in_texture(cub, cub->bottom_texture);
}
// }
