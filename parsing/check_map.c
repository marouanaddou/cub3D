/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:16:36 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 14:12:48 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void map_number(t_cub *cub)
{
    int i;
    int j;
    char **x;

}

void    check_map(char *map, t_cub *cub)
{
    int	i;
	char buffer[100000];

	i = 0;
	cub->par.fd = open(map, O_RDWR);
	if (cub->par.fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	read(cub->par.fd, buffer, 100000);
	cub->par.map = ft_split(buffer, '\n');
	if (!cub->par.map)
	{
		close(cub->par.fd);
		perror("Error loading Map\n");
		exit(1);
	}
    i = 0;
    map_number(cub);
	close(cub->par.fd);
}