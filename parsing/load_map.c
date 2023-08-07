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

void cont(t_cub *cub, int *bol, char *line)
{
    if ((line[0] != ' ' && line[0] != '1') && *bol == 0)
    {
        cub->par.cnt_elmt++;
    }
    else 
    { 
        *bol = 1;
        cub->par.cnt_map++;
    }
}

int open_file(char *map, int fd)
{
    fd = open(map, O_RDWR);
	if (fd  == -1)
	{
		perror("Error opening file");
		exit(1);
	}
    return(fd);
}

void	map_len(char *map, t_cub *cub)
{
	int		fd;
    int     bol;
	char	*line;

    bol = 0;
    cub->par.cnt_elmt = 0;
    cub->par.cnt_map = 0;
    fd = 0;
	fd = open_file(map, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
        cont(cub, &bol, line);
		free(line);
	}
	close(fd);
}

void	load_map(char *map ,t_cub *cub)
{
    int fd;

	cub->i = 0;
    cub->j = 0;
    fd = 0;
	fd = open_file(map, fd);
	while (1)
	{
        cub->par.file[cub->i] = get_next_line(fd);
        if (cub->i < cub->par.cnt_elmt)
            cub->par.element[cub->i] = ft_strdup(cub->par.file[cub->i]);
        // printf ("%s", cub->par.element[cub->i]);
        else if (cub->j < cub->par.cnt_map)
        {
            cub->par.element[cub->par.cnt_elmt] = NULL;
            cub->par.map[cub->j++] = ft_strdup(cub->par.file[cub->i]);
        }
		if (cub->par.file[cub->i] == NULL)
			break ;
        cub->i++;
	}
    cub->par.map[cub->j] = NULL;
	close(fd);
}