/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/10 19:48:19 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>

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

void    draw_wall_in_image(t_cub *cub)
{
    int put1;
    int put2;
    
    while(cub->par.map[cub->i] != NULL)
    {
        cub->j = 0;
        while(cub->par.map[cub->i][cub->j] != '\0')
        {
            if (cub->par.map[cub->i][cub->j] == '1')
            {
                put1 = 0;
                while(put1 < 30)
                {
                    put2 = 0;
                    while(put2 < 30)
                    {
                        mlx_put_pixel(cub->mlx.img_ptr, (cub->j *30) + put1, (cub->i*30) +put2 ,0x00000000);
                        put2++;
                    }
                    put1++;
                }
            }
           cub->j++;
        }
        cub->i++;
    }
}

void    draw_white_in_image(t_cub *cub)
{
    cub->i = 0;
    cub->j = 0;
    while(cub->i < (cub->mlx.width * 30))
    {
        cub->j = 0;
        while(cub->j < (cub->mlx.height * 30))
        {
            mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j, 0xffffffff);
            cub->j++;
        }
        cub->i++;
    }
    cub->i = 0;
    cub->j = 0;
}

// void    draw_player(t_cub *cub)
// {
//     int        x;
//     int        y;
//     int        dx;
//     int        dy;
//     int        radius;
//     int        distance_squared;

//     radius = 5;
//     x = 0;
//     while (x < ((cub->j *30) + radius))
//     {
//         y = 0;
//         while (y < ((cub->i *30) + radius))
//         {
//             dx = x - (cub->j *30);
//             dy = y - (cub->i *30);
//             distance_squared = dx * dx + dy * dy;
//             if (distance_squared < (radius * radius))
//                 mlx_put_pixel(cub->mlx.img_ptr, x + 15, y + 15, 0xC41E3A);
//             y++;
//         }
//         x++;
//     }
// }

void    player(t_cub *cub)
{
    cub->par.y = 0;
    while(cub->par.map[cub->par.y] != NULL)
    {
        cub->par.x = 0;
        while(cub->par.map[cub->par.y][cub->par.x] != '\0')
        {
            if (cub->par.map[cub->par.y][cub->par.x] == 'N')
                break;
            cub->par.x++;
        }
        if (cub->par.map[cub->par.y][cub->par.x] == 'N')
            break;
        cub->par.y++;
    }
}

void    draw_player_in_image(t_cub *cub, int i, int j)
{
    int x;
    int y;
    
    // cub->i = 0;
    x = -5;
    // while(cub->par.map[cub->i] != NULL)
    // {
    //     cub->j = 0;
    //     while(cub->par.map[cub->i][cub->j] != '\0')
    //     {
    //         if (cub->par.map[cub->i][cub->j] == 'N')
    //             break;
    //         cub->j++;
    //     }
    //     if (cub->par.map[cub->i][cub->j] == 'N')
    //         break;
    //     cub->i++;
    // }
    // player(cub, i ,j);
    while(x < 5)
    {
        y = -5;
        while(y < 5)
        {
            if (x*x + y*y < 5*5)
                mlx_put_pixel(cub->mlx.img_ptr,  (cub->par.x + i) + x, (cub->par.y + j) + y , 0xC41E3A);
            y++;
        }
        x++;
    }
    cub->par.x += i;
    cub->par.y += j;
}

int check_wall(t_cub *cub, int i)
{
    int x;

    x = 0;
    if (i == MLX_KEY_A)
    {
        x = (cub->par.x - 5 - 1) / 30;
        if (cub->par.map[cub->par.y / 30][x] == '1')
            return (0);
    }
    else if (i == MLX_KEY_W)
    {
        x = (cub->par.y - 5 - 1) / 30;
        if (cub->par.map[x][cub->par.x / 30] == '1')
            return (0);
    }
    else if (i == MLX_KEY_D)
    {
        x = (cub->par.x + 5) / 30;
        if (cub->par.map[cub->par.y / 30][x] == '1')
            return (0);
    }
    else if (i == MLX_KEY_S)
    {
        x = (cub->par.y + 5) / 30;
        if (cub->par.map[x][cub->par.x / 30] == '1')
            return (0);
    }
    return (1);
}
void    key_hook(mlx_key_data_t data, void *cub)
{
    t_cub *cu = (t_cub *)cub;
    if(data.key == MLX_KEY_A && data.action == MLX_PRESS)
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_A) == 1)
            draw_player_in_image(cub, -5, 0);
        else  
            draw_player_in_image(cub, 0, 0);
    }
    else if(data.key == MLX_KEY_W && data.action == MLX_PRESS)
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_W) == 1)
            draw_player_in_image(cub, 0, -5);
        else  
            draw_player_in_image(cub, 0, 0);
    }
    else if(data.key == MLX_KEY_D && data.action == MLX_PRESS)
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_D) == 1)
            draw_player_in_image(cub, 5, 0);
        else  
            draw_player_in_image(cub, 0, 0);
    }
    else if(data.key == MLX_KEY_S && data.action == MLX_PRESS)
   {;
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_S) == 1)
            draw_player_in_image(cub, 0, 5);
        else  
            draw_player_in_image(cub, 0, 0);
    }
}

int main(int ac, char **av)
{
    t_cub	cub;
    if (ac == 2)
    {
        allocation_map(&cub, av[1]);
        check_file_ext(av[1]);
        load_map(av[1], &cub);
        check_information(&cub);
        check_map(&cub);
		cub.mlx.init_ptr = mlx_init(cub.mlx.width * 30, cub.mlx.height * 30, "cub3D", 1);
		cub.mlx.img_ptr = mlx_new_image(cub.mlx.init_ptr, cub.mlx.width * 30, cub.mlx.height * 30);
		mlx_image_to_window(cub.mlx.init_ptr,cub.mlx.img_ptr,0,0);
        if (!(cub.mlx.init_ptr || cub.mlx.img_ptr))
			return (EXIT_FAILURE);
        draw_white_in_image(&cub);
        draw_wall_in_image(&cub);
        draw_player_in_image(&cub, 0, 0);
        mlx_key_hook(cub.mlx.init_ptr, key_hook, &cub);
		mlx_loop(cub.mlx.init_ptr);
		mlx_terminate(cub.mlx.init_ptr);
	}
	return (0);
}






// #include "mlx42/include/MLX42/MLX42.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <memory.h>
// #define WIDTH 256
// #define HEIGHT 256

// static mlx_image_t	*g_img;

// void	hook(void* param)
// {
// 	mlx_t* mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_P))
// 		mlx_delete_image(mlx, g_img);
// 	for (int x = 0; x < (int)g_img->width; x++)
// 		for(int y= 0; y < (int)g_img->height; y++)
// 			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
// }

// int32_t	main(void)
// {
// 	mlx_t*    mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		exit(EXIT_FAILURE);
// 	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	mlx_image_to_window(mlx, g_img, 0, 0);
//     for(int i = 0;i<100;i++)
//     {
//         for(int j = 0;j< 100;j++)
// 			mlx_put_pixel(g_img, i, j, 0xEF0000FF);

//     }
// 	// mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }