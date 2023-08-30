/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textels.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:41 by mel-gand          #+#    #+#             */
/*   Updated: 2023/08/30 18:10:32 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include <stdint.h>

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	fill_texture_colors(t_cub *cub, uint32_t **texture, uint32_t *x, uint32_t *y)
{
	texture[*x][(*y)++] = ft_pixel(cub->txt->pixels[cub->i], cub->txt->pixels[cub->i + 1]
			, cub->txt->pixels[cub->i + 2], cub->txt->pixels[cub->i + 3]);		
	if (*y == cub->txt->width)
	{
		(*x)++;
		*y = 0;
	}
}
uint32_t	**fill_in_texture(t_cub *cub, uint32_t **texture)
{
	uint32_t x;
	uint32_t y;
	
	cub->i = 0;
	x = 0;
	y = 0;
	texture = malloc(sizeof(uint32_t *) * cub->txt->height);
	if (!texture)
		return(0);
	while(cub->i < (int)cub->txt->height)
	{
			texture[cub->i] = malloc(sizeof(uint32_t) * cub->txt->width);
			if (!texture[cub->i]) //free || !!!!!!?
				return(0);
			cub->i++;
	}
	cub->i = 0;
	while(cub->i < (int)(cub->txt->height * cub->txt->width * cub->txt->bytes_per_pixel))
	{
		fill_texture_colors(cub, texture, &x, &y);
		cub->i += 4;
	}
	return(texture);
}

void	left_right_textures(t_cub *cub)
{
	cub->txt = mlx_load_png("textures/BRICK_1A.PNG");
	if (!cub->txt)
		exit(1);
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->right_texture = fill_in_texture(cub, cub->right_texture);
	cub->txt = mlx_load_png("textures/BRICK_2B.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->left_texture = fill_in_texture(cub, cub->left_texture);
}

void load_textures(t_cub *cub) 
{
	left_right_textures(cub);
	cub->txt = mlx_load_png("textures/BRICK_3B.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->top_texture = fill_in_texture(cub, cub->top_texture);
	cub->txt = mlx_load_png("textures/BRICK_3D.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->bottom_texture = fill_in_texture(cub, cub->bottom_texture);
}
