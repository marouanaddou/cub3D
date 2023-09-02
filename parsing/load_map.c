/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:16:36 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 17:02:27 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_file(char *map, int fd)
{
	fd = open(map, O_RDWR);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}

void	initialisation_fa( t_cub *cub, int i, int j)
{
	i = 0;
	while (i < cub->par.cnt_map)
	{
		j = 0;
		while (cub->par.map[i][j] != '\0')
		{
			if (cub->par.map[i][j] == 'N')
				cub->ray.first_angle = -(M_PI / 2);
			else if (cub->par.map[i][j] == 'W')
				cub->ray.first_angle = M_PI;
			else if (cub->par.map[i][j] == 'S')
				cub->ray.first_angle = (M_PI / 2);
			else if (cub->par.map[i][j] == 'E')
				cub->ray.first_angle = 0;
			if (cub->par.map[i][j] == 'N' || cub->par.map[i][j] == 'W' 
				|| cub->par.map[i][j] == 'S' || cub->par.map[i][j] == 'E')
			{
				cub->par.x = (j * 30) + CENTER;
				cub->par.y = (i * 30) + CENTER;
			}
			j++;
		}
		i++;
	}
}

void	check_line(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	if (cub->par.check_line != 0)
	{
		free_double_pointer(cub->par.element);
		free_double_pointer(cub->par.file);
		free_double_pointer(cub->par.map);
		print_error("ERROR");
	}
	i = 0;
	j = 0;
	initialisation_fa(cub, i, j);
}

void	fill_line(t_cub *cub)
{
	int	j;

	j = 0;
	cub->par.map[cub->j] = NULL;
	while (cub->par.file[cub->i][j] != '\0')
	{
		if (j != (int)ft_strlen(cub->par.file[cub->i]) - 1)
			cub->par.map[cub->j] = ft_copier(cub->par.file[cub->i][j],
					cub->par.map[cub->j]);
		else if (cub->par.file[cub->i]
			[(int)ft_strlen(cub->par.file[cub->i]) - 1] != '\n')
			cub->par.map[cub->j] = ft_copier(cub->par.file[cub->i][j],
					cub->par.map[cub->j]);
		j++;
	}
	while (j < cub->mlx.width)
	{
		cub->par.map[cub->j] = ft_copier(' ', cub->par.map[cub->j]);
		j++;
	}
	cub->j++;
}

void	load_map(char *map, t_cub *cub)
{
	int	fd;

	fd = 0;
	fd = open_file(map, fd);
	while (1)
	{
		cub->par.file[cub->i] = get_next_line(fd);
		if (cub->i < cub->par.cnt_elmt)
			cub->par.element[cub->i] = ft_strdup(cub->par.file[cub->i]);
		else if (cub->j < cub->par.cnt_map)
		{
			if (cub->par.file[cub->i][0] == '\n')
				cub->par.check_line += 1;
			cub->par.element[cub->par.cnt_elmt] = NULL;
			fill_line(cub);
		}
		if (cub->par.file[cub->i] == NULL)
			break ;
		cub->i++;
	}
	cub->par.map[cub->j] = NULL;
	check_line(cub);
	free_double_pointer(cub->par.file);
	close(fd);
}
