/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:16:36 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 15:07:00 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_len(char *map)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(map, O_RDWR);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

void	load_map(char *map ,t_cub *cub)
{
	int	i;
    int fd;

	i = 0;
	fd = open(map, O_RDWR);
	if (fd  == -1)
	{
		perror("Error opening file");
		exit(1);
	}
    
	while (1)
	{
		cub->par.file[i] = get_next_line(fd );
        
		if (cub->par.file[i++] == NULL)
			break ;
	}
    i = 0;
    while(cub->par.file[i] != NULL)
    {
        printf("%s", cub->par.file[i]);
        i++;
    }
	close(fd);
}