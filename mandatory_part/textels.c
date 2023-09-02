/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textels.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:41 by mel-gand          #+#    #+#             */
/*   Updated: 2023/09/02 10:27:09 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	fill_texture_colors(t_cub *cub, uint32_t **texture,
	mlx_texture_t *txt, uint32_t *x)
{
	static uint32_t	y;

	texture[*x][(y)++] = ft_pixel(txt->pixels[cub->i],
			txt->pixels[cub->i + 1], txt->pixels[cub->i + 2],
			txt->pixels[cub->i + 3]);
	if (y == txt->width)
	{
		(*x)++;
		y = 0;
	}
}

uint32_t	**fill_in_texture(mlx_texture_t *txt, uint32_t **texture,
	t_cub *cub)
{
	uint32_t	x;

	cub->i = 0;
	x = 0;
	texture = NULL;
	texture = malloc(sizeof(uint32_t *) * txt->height);
	if (!texture)
		return (0);
	while (cub->i < (int)txt->height)
	{
		texture[cub->i] = malloc(sizeof(uint32_t) * txt->width);
		if (!texture[cub->i])
			return (0);
		cub->i++;
	}
	cub->i = 0;
	while (cub->i < (int)(txt->height * txt->width
		* txt->bytes_per_pixel))
	{
		fill_texture_colors(cub, texture, txt, &x);
		cub->i += 4;
	}
	return (texture);
}

void	load_texture(t_cub *cub)
{
	cub->top_texture = fill_in_texture(cub->txt[1], cub->top_texture, cub);
	cub->bottom_texture = fill_in_texture(cub->txt[0],
			cub->bottom_texture, cub);
	cub->right_texture = fill_in_texture(cub->txt[3], cub->right_texture, cub);
	cub->left_texture = fill_in_texture(cub->txt[2], cub->left_texture, cub);
	cub->i = 0;
	cub->j = 0;
}

void	load_textures(t_cub *cub)
{
	cub->i = 0;
	cub->j = 0;
	while (cub->i < 4)
	{
		cub->txt[cub->i] = mlx_load_png(cub->par.texture_path[cub->i]);
		if (!cub->txt[cub->i])
		{
			free_double_pointer(cub->par.map);
			free_double_pointer(cub->par.element);
			free_element(cub->par.elm);
			print_error("ERROR: textures\n");
		}
		cub->img[cub->i] = mlx_texture_to_image(cub->mlx.init_ptr,
				cub->txt[cub->i]);
		if (!cub->img[cub->i])
		{
			free_double_pointer(cub->par.map);
			free_double_pointer(cub->par.element);
			free_element(cub->par.elm);
			print_error("ERROR: textures\n");
		}
		cub->i++;
	}
	load_texture(cub);
}
