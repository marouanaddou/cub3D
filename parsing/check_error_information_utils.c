/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_information_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:52:57 by maddou            #+#    #+#             */
/*   Updated: 2023/09/01 13:13:10 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_argument(char **color, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (color[i] != NULL)
	{
		j = 0;
		while (color[i][j] != '\0')
		{
			if (ft_isdigit(color[i][j]) != 1)
			{
				free_double_pointer(cub->par.element);
				free_double_pointer(cub->par.map);
				free_double_pointer(color);
				free_element(cub->par.elm);
				print_error("ERROR: color2\n");
			}
			j++;
		}
		i++;
	}
}

void	check_rgb(char **color, t_cub *cub, int atoi)
{
	cub->j = 0;
	atoi = 0;
	check_argument(color, cub);
	while (color[cub->j] != NULL)
	{
		atoi = ft_atoi(color[cub->j]);
		if (atoi < 0 || atoi > 255)
		{
			free_double_pointer(cub->par.map);
			free_double_pointer(cub->par.element);
			free_element(cub->par.elm);
			free_double_pointer(color);
			print_error("ERROR: color3\n");
		}
		cub->j++;
	}
}

void	check_double(t_cub *cub, int i)
{
	cub->j = 0;
	while (cub->j < cub->par.cnt_elmt)
	{
		i = cub->j + 1;
		while (i < cub->par.cnt_elmt)
		{
			if (ft_strcmp(cub->par.elm[cub->j].direction, 
					cub->par.elm[i].direction) == 0)
			{
				free_double_pointer(cub->par.map);
				free_double_pointer(cub->par.element);
				free_element(cub->par.elm);
				print_error("ERROR: double information\n");
			}
			i++;
		}
		cub->j++;
	}
	cub->j = 0;
}

void	check_double_coma(t_cub *cub, char *color)
{
	cub->i = 0;
	if (color[0] == '\0' || color[0] == ',' 
		|| color[ft_strlen(color) - 1] == ',')
	{
		free_double_pointer(cub->par.element);
		free_double_pointer(cub->par.map);
		free_element(cub->par.elm);
		print_error("ERROR: color4\n");
	}
	while (color[cub->i] != '\0')
	{
		if (color[cub->i] == ',' && color[cub->i + 1] == ',')
		{
			free_double_pointer(cub->par.element);
			free_double_pointer(cub->par.map);
			free_element(cub->par.elm);
			print_error("ERROR: color5\n");
		}
		cub->i++;
	}
}
