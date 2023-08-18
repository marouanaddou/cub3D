/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/18 20:52:15 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"
#include "mlx42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/syslimits.h>

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

void    player(t_cub *cub)
{
    cub->par.pyp = 0;
    while(cub->par.map[cub->par.pyp] != NULL)
    {
        cub->par.pxp = 0;
        while(cub->par.map[cub->par.pyp][cub->par.pxp] != '\0')
        {
            if (cub->par.map[cub->par.pyp][cub->par.pxp] == 'N')
                break;
            cub->par.pxp++;
        }
        if (cub->par.map[cub->par.pyp][cub->par.pxp] == 'N')
            break;
        cub->par.pyp++;
    }
}
int check_holes(t_cub *cub, float prev_x, float prev_y)
{
    
    if (cub->par.map[((int)(cub->ray.y_ver / 30))][(int)prev_x / 30] == '1'
        && cub->par.map[(int)prev_y / 30][(int)(cub->ray.x_hor / 30)] == '1')
            return (1);
    return (0);
}
void    calculate_slope( int i, t_cub *cub)
{
    double dx;
    double dy;
    float steps;

    dx = cub->point[i].x_end;
    dy = cub->point[i].y_end;
    steps = fabs(dx) + fabs(dy);
    cub->ray.x_inc = dx / steps;
    cub->ray.y_inc = dy / steps;
}

void    cast_rays(t_cub *cub)
{
    int   i;

    i = 0;
    while(i < cub->degree / cub->angle_increment)
    {
        calculate_slope(i, cub);
        cub->ray.x_hor = cub->par.x;
        cub->ray.y_ver = cub->par.y;
        while (1)
        {
            if (cub->par.map[(int)floor(cub->ray.y_ver)/ 30][(int)floor(cub->ray.x_hor) / 30] == '1')
                break;
            if (check_holes(cub, cub->ray.x_hor - cub->ray.x_inc, cub->ray.y_ver - cub->ray.y_inc) == 1)
                break;
            mlx_put_pixel(cub->mlx.img_ptr, cub->ray.x_hor, cub->ray.y_ver, 0xAA4A44);
            cub->ray.x_hor += cub->ray.x_inc;
            cub->point[i].x_end = cub->ray.x_hor;
            cub->ray.y_ver += cub->ray.y_inc;
            cub->point[i].y_end = cub->ray.y_ver;
        }
        i++;
    } 
}
void    find_point(t_cub *cub)
{
    int i;

    i = 0;
    cub->degree = 60 * (M_PI / 180);
    cub->angle_increment = (cub->degree / (cub->mlx.width * 30));
    cub->point = malloc(sizeof(t_point) * ((cub->degree / cub->angle_increment) + 1));
    cub->angle = 0;
    while(cub->angle < cub->degree)
    {
        cub->point[i].x_end = cos(cub->angle + (cub->ray.first_angle - (cub->degree / 2)));
        cub->point[i].y_end = sin(cub->angle + (cub->ray.first_angle - (cub->degree / 2)));
        cub->angle += cub->angle_increment;
        i++;
    }
}

void    draw_player_in_image(t_cub *cub, int i, int j)
{
    int x;
    int y;
    int radian;
    
    radian = 5;
    x = -1 * radian;
    while(x < radian)
    {
        y = -1 * radian;
        while(y < radian)
        {
            if (x*x + y*y < radian*radian)
                mlx_put_pixel(cub->mlx.img_ptr,  (cub->par.x + i) + x, (cub->par.y + j) + y  , 0xC41E3A);
            y++;
        }
        x++;
    }
    cub->par.x += i;
    cub->par.y += j;
    find_point(cub);
    cast_rays(cub);
}

int check_wall(t_cub *cub, int i)
{
    int x;

    x = 0;
    if (i == MLX_KEY_A)
    {
        x = (cub->par.x - 5 - 1) / 30;
        if (cub->par.map[(int)cub->par.y / 30][x] == '1')
            return (0);
    }
    else if (i == MLX_KEY_W)
    {
        x = (cub->par.y - 5 - 1) / 30;
        if (cub->par.map[x][(int)cub->par.x / 30] == '1')
            return (0);
    }
    else if (i == MLX_KEY_D)
    {
        x = (cub->par.x + 5) / 30;
        if (cub->par.map[(int)cub->par.y / 30][x] == '1')
            return (0);
    }
    else if (i == MLX_KEY_S)
    {
        x = (cub->par.y + 5) / 30;
        if (cub->par.map[x][(int)cub->par.x / 30] == '1')
            return (0);
    }
    return (1);
}
void    loop_hook( void *cub)
{
    t_cub *cu = (t_cub *)cub;
    if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_A))
    {
        cu->par.x += cos(cu->ray.first_angle -(M_PI / 2));
        cu->par.y += sin(cu->ray.first_angle -(M_PI / 2));
        draw_white_in_image(cu);
        draw_wall_in_image(cu); 
        draw_player_in_image(cub, 0, 0);
    }
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_W))
    {
        cu->par.x += cos(cu->ray.first_angle);
        cu->par.y += sin(cu->ray.first_angle);
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    }
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_D))
    {
        cu->par.x -= cos(cu->ray.first_angle -(M_PI / 2));
        cu->par.y -= sin(cu->ray.first_angle -(M_PI / 2));
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    }
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_S))
    {
        cu->par.x -= cos(cu->ray.first_angle);
        cu->par.y -= sin(cu->ray.first_angle);
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    }
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_LEFT))
    {
        cu->ray.first_angle += 0.10;
        if (cu->ray.first_angle > 2 * M_PI)
            cu->ray.first_angle -= 2 * M_PI;
        if (cu->ray.first_angle < 0)
            cu->ray.first_angle += 2 * M_PI;
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    }
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_RIGHT))
    {
        cu->ray.first_angle -= 0.10;
        if (cu->ray.first_angle > 2 * M_PI)
            cu->ray.first_angle -= 2 * M_PI;
        if (cu->ray.first_angle < 0)
            cu->ray.first_angle += 2 * M_PI;
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    }
    if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_ESCAPE))
        mlx_close_window(cu->mlx.init_ptr);
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
        // mlx_key_hook(cub.mlx.init_ptr, key_hook, &cub);
        mlx_loop_hook(cub.mlx.init_ptr, loop_hook, &cub);
		mlx_loop(cub.mlx.init_ptr);
		mlx_terminate(cub.mlx.init_ptr);
	}
	return (0);
}
