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
#include <unistd.h>

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
    cub->mlx.height = 0;
	fd = open_file(map, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
        cont(cub, &bol, line);
		free(line);
	}
    if (cub->par.cnt_elmt == 0 || cub->par.cnt_map == 0)
    {
        close(fd);
        print_error("ERROR: not complet information");
    }
	close(fd);
}

void    check_line(char *line, t_cub *cub)
{
    int i;
    (void)cub;

    i = 0;
    if (line[i] == '\n')
        print_error("ERROR");
    while(line[i] != '\0' && line[i] == ' ')
    {
        if(line[i + 1] == '\n' || line[i + 1] == '\0')
            print_error("ERROR"); //freee ......!!!!
        i++;
    }
    i = 0;
    while(line[i] != '\0')
    {
        if (line[i] == 'N' || line[i] == 'W' || line[i] == 'S' || line[i] == 'E')
        {
            cub->par.x = (i * 30);
            cub->par.y = (cub->j * 30);
        }
        i++;
    }
}

void	load_map(char *map ,t_cub *cub)
{
    int fd;

	cub->i = 0;
    cub->j = 0;
    fd = 0;
	fd = open_file(map, fd);
    cub->mlx.height = 0;
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
            cub->par.map[cub->j++] = ft_strdup(cub->par.file[cub->i]);
            cub->mlx.height++;
        }
		if (cub->par.file[cub->i] == NULL)
			break ;
        cub->i++;
	}
    cub->par.map[cub->j] = NULL;
    cub->par.element[cub->par.cnt_elmt] = NULL;
	close(fd);
}