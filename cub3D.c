/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/08 20:01:53 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>

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
    t_cub	cub;
	t_mlx	mlx;
    (void)cub;
    if (ac == 2)
    {
        allocation_map(&cub, av[1]);
        check_file_ext(av[1]);
        load_map(av[1], &cub);
        check_information(&cub);
        check_map(&cub);
		mlx.init_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
		mlx.img_ptr = mlx_new_image(mlx.init_ptr, 320, 200);
		if (!(mlx.init_ptr || mlx.img_ptr))
			return (EXIT_FAILURE);
		mlx_put_pixel(mlx.img_ptr, 10, 10, 0xFFF);
		mlx_loop(mlx.init_ptr);
		mlx_terminate(mlx.init_ptr);
	}
	return (0);
}
