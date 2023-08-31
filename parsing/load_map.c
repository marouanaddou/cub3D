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

void	initialisation_fa(char *line, t_cub *cub, int i)
{
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N')
			cub->ray.first_angle = -(M_PI / 2);
		else if (line[i] == 'W')
			cub->ray.first_angle = M_PI;
		else if (line[i] == 'S')
			cub->ray.first_angle = (M_PI / 2);
		else if (line[i] == 'E')
			cub->ray.first_angle = 0;
		if (line[i] == 'N' || line[i] == 'W' || line[i] == 'S'
			|| line[i] == 'E')
		{
			cub->par.x = (i * 30) + CENTER;
			cub->par.y = (cub->j * 30) + CENTER;
		}
		i++;
	}
}

void	check_line(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		print_error("ERROR");
	initialisation_fa(line, cub, i);
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
		if (cub->par.file[0] == NULL)
			print_error("ERROR");
		if (cub->i < cub->par.cnt_elmt)
			cub->par.element[cub->i] = ft_strdup(cub->par.file[cub->i]);
		else if (cub->j < cub->par.cnt_map)
		{
			check_line(cub->par.file[cub->i], cub);
			fill_line(cub);
		}
		if (cub->par.file[cub->i] == NULL)
			break ;
		cub->i++;
	}
	cub->par.map[cub->j] = NULL;
	cub->par.element[cub->par.cnt_elmt] = NULL;
	close(fd);
	free_double_pointer(cub->par.file);
}
