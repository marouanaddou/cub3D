/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:20 by maddou            #+#    #+#             */
/*   Updated: 2023/08/26 16:32:08 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cont(t_cub *cub, int *bol, char *line)
{
	if ((line[0] != ' ' && line[0] != '1') && *bol == 0)
		cub->par.cnt_elmt++;
	else
	{
		*bol = 1;
		cub->par.cnt_map++;
	}
}

void	initialisation_varible(t_cub *cub, int *bol, int *fd)
{
	*bol = 0;
	cub->par.cnt_elmt = 0;
	cub->par.cnt_map = 0;
	*fd = 0;
	cub->mlx.height = 0;
	cub->mlx.width = 0;
	cub->i = 0;
	cub->j = 0;
}

void	map_len(char *map, t_cub *cub)
{
	int		fd;
	int		bol;
	char	*line;

	initialisation_varible(cub, &bol, &fd);
	fd = open_file(map, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (cub->mlx.width < (int)ft_strlen(line))
			cub->mlx.width = ft_strlen(line);
		cont(cub, &bol, line);
		free(line);
	}
	if (cub->par.cnt_elmt == 0 || cub->par.cnt_map == 0)
	{
		close(fd);
		print_error("ERROR: not complet information");
	}
	cub->mlx.width--;
	close(fd);
}
