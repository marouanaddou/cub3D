/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 19:45:26 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void allocation_map(t_cub *cub, char *map)
{
	map_len(map, cub);
	cub->par.element = malloc(sizeof(char *) * (cub->par.cnt_elmt + 1));
	if (!cub->par.element)
	{
		free(cub->par.element);
		exit (1);
	}
	cub->par.map = malloc(sizeof(char *) * (cub->par.cnt_map + 1));
	if (!cub->par.map)
	{
		free(cub->par.map);
		exit (1);
	}
	cub->par.file = malloc(sizeof(char *) * (cub->par.cnt_map + 1 + cub->par.cnt_elmt));
	if (!cub->par.file)
	{
		free(cub->par.file);
		exit (1);
	}
}

int main(int ac, char **av)
{
    t_cub cub;
    (void)cub;
    if (ac == 2)
    {
		allocation_map(&cub, av[1]);
        check_file_ext(av[1]);
		load_map(av[1], &cub);
		// check_map(&cub);
		check_map_element(&cub);
    }
}