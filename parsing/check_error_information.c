/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_information.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:45:49 by maddou            #+#    #+#             */
/*   Updated: 2023/08/31 22:42:48 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	comparaison(char *direction, t_cub *cub)
{
	if (ft_strcmp(direction, "NO") != 0 && ft_strcmp(direction, "WE") != 0
		&& ft_strcmp(direction, "SO") != 0 && ft_strcmp(direction, "EA") != 0
		&& ft_strcmp(direction, "F") != 0 && ft_strcmp(direction, "C") != 0)
	{
		free_double_pointer(cub->par.element);
		free_double_pointer(cub->par.map);
		free_element(cub->par.elm);
		print_error("ERROR: information\n");
	}
}

void	trim_path(t_cub *cub, int i)
{
	char	*trim;
	char	*tr;
	
	if (cub->par.elm[i].path[0] != '\0')
	{
		tr = ft_strtrim(cub->par.elm[i].path, "\n");
		trim = ft_strdup(tr);
		free(cub->par.elm[i].path);
		cub->par.elm[i].path = ft_strdup(trim);
		free(trim);
		free(tr);
	}
	if (cub->par.elm[i].path[0] != '\0')
	{
		tr = ft_strtrim(cub->par.elm[i].path, " ");
		trim = ft_strdup(tr);
		free(cub->par.elm[i].path);
		cub->par.elm[i].path = ft_strdup(trim);
		free(trim);
		free(tr);
	}
}

void	check_color(t_cub *cub, int i)
{
	char	**color;
	char	*trim;
	int		atoi;

	atoi = 0;
	trim = NULL;
	check_double_coma(cub, cub->par.elm[i].path);
	color = ft_split(cub->par.elm[i].path, ',');
	check_rgb(color, cub, atoi);
	if (cub->j != 3)
	{
		free_double_pointer(cub->par.element);
		free_double_pointer(cub->par.map);
		free_double_pointer(color);
		free_element(cub->par.elm);
		print_error("ERROR: color\n");
	}
	free_double_pointer(color);
	cub->j = 0;
}

void	fill_color(t_cub *cub, char **color, int i)
{
	if (ft_strcmp(cub->par.elm[i].direction, "F") == 0)
	{
		color = ft_split(cub->par.elm[i].path, ',');
		cub->par.floor = (atoi(color[0]) << 24 | atoi(color[1]) << 16
				| atoi(color[2]) >> 8 | 255);
	}
	else
	{
		color = ft_split(cub->par.elm[i].path, ',');
		cub->par.ceiling = (atoi(color[0]) << 24 | atoi(color[1]) << 16 
				| atoi(color[2]) << 8 | 255);
	}
	free_double_pointer(color);
}

void	check_error_information(t_cub *cub)
{
	int		i;
	char	**color;

	i = 0;
	cub->j = 0;
	color = NULL;
	check_double(cub, i);
	while (i < cub->par.cnt_elmt)
	{
		comparaison(cub->par.elm[i].direction, cub);
		if (ft_strcmp(cub->par.elm[i].direction, "F") == 0
			|| ft_strcmp(cub->par.elm[i].direction, "C") == 0)
		{
			trim_path(cub, i);
			check_color(cub, i);
			fill_color(cub, color, i);
		}
		else
			trim_path(cub, i);
		i++;
	}
}
