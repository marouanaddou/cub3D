/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:20 by maddou            #+#    #+#             */
/*   Updated: 2023/09/01 13:17:04 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	count(t_cub *cub, int *bol, char *line)
{
	if ((line[0] != ' ' && line[0] != '1') && *bol == 0)
		cub->par.cnt_elmt++;
	else
	{
		*bol = 1;
		if (cub->mlx.width < (int)ft_strlen(line))
			cub->mlx.width = ft_strlen(line);
		cub->par.cnt_map++;
	}
	free(line);
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
	cub->par.check_line = 0;
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
		count(cub, &bol, line);
	}
	if (cub->par.cnt_elmt == 0 || cub->par.cnt_map == 0)
	{
		close(fd);
		print_error("ERROR: incomplete information");
	}
	cub->mlx.width--;
	close(fd);
}

void	allocation_map(t_cub *cub, char *map)
{
	map_len(map, cub);
	cub->par.element = malloc(sizeof(char *) * (cub->par.cnt_elmt + 1));
	if (!cub->par.element)
		exit(1);
	cub->par.map = malloc(sizeof(char *) * (cub->par.cnt_map + 1));
	if (!cub->par.map)
	{
		free(cub->par.element);
		exit(1);
	}
	cub->par.file = malloc(sizeof(char *)
			* (cub->par.cnt_map + 1 + cub->par.cnt_elmt));
	if (!cub->par.file)
	{
		free(cub->par.element);
		free(cub->par.map);
		exit(1);
	}
}
