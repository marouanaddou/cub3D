/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_information.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:45:49 by maddou            #+#    #+#             */
/*   Updated: 2023/08/27 13:07:38 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// hna khasna free .....!
void	comparaison(char *direction)
{
	if (ft_strcmp(direction, "NO") != 0 && ft_strcmp(direction, "WE") != 0
		&& ft_strcmp(direction, "SO") != 0 && ft_strcmp(direction, "EA") != 0
		&& ft_strcmp(direction, "F") != 0 && ft_strcmp(direction, "C") != 0)
	{
		printf("ERROR: information\n");
		exit(1);
	}
}

void	tream_path(t_cub *cub, int i)
{
	char	*tream;
	
	if (cub->par.elm[i].path[0] != '\0')
	{
		tream = ft_strdup(ft_strtrim(cub->par.elm[i].path, "\n"));
		free(cub->par.elm[i].path);
		cub->par.elm[i].path = ft_strdup(tream);
		free(tream);
	}
	if (cub->par.elm[i].path[0] != '\0')
	{
		tream = ft_strdup(ft_strtrim(cub->par.elm[i].path, " "));
		free(cub->par.elm[i].path);
		cub->par.elm[i].path = ft_strdup(tream);
		free(tream);
	}
}

void	check_color(t_cub *cub, int i)
{
	char	**color;
	char	*tream;
	int		atoi;

	atoi = 0;
	tream = NULL;
	check_double_coma(cub, cub->par.elm[i].path);
	color = ft_split(cub->par.elm[i].path, ',');
	check_rgb(color, cub, atoi);
	if (cub->j != 3)
	{
		printf("ERROR: color\n");
		exit(1);
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
}

void	check_error_information(t_cub *cub)
{
	int		i;
	char	**color;

	i = 0;
	cub->j = 0;
	color = NULL;
	while (i < cub->par.cnt_elmt)
	{
		comparaison(cub->par.elm[i].direction);
		check_double(cub, i);
		if (ft_strcmp(cub->par.elm[i].direction, "F") == 0
			|| ft_strcmp(cub->par.elm[i].direction, "C") == 0)
		{
			tream_path(cub, i);
			check_color(cub, i);
			fill_color(cub, color, i);
		}
		else
			tream_path(cub, i);
		i++;
	}
}
