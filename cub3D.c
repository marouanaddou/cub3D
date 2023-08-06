/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 15:05:08 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_cub cub;
    (void)cub;
    if (ac == 2)
    {
		cub.par.file = malloc(sizeof(char *) * map_len(av[1]) + 1);
		if(!cub.par.file)
		{
			free(cub.par.file);
			return (1);
		}
        check_file_ext(av[1]);
		// check_map(av[1], &cub);
		load_map(av[1], &cub);
    }
}