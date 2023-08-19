/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/18 15:50:35 by maddou           ###   ########.fr       */
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
int check_holes(t_cub *cub, float *x_hor, float *y_ver, float prev_x, float prev_y)
{
    
    if (cub->par.map[((int)(*y_ver / 30))][(int)prev_x / 30] == '1'
        && cub->par.map[(int)prev_y / 30][(int)(*x_hor / 30)] == '1')
            return (1);
    // if (cub->par.map[((int)(*y_ver / 30) - 1)][(int)*x_hor / 30] == '1'
    //     && cub->par.map[(int)*y_ver / 30][(int)(*x_hor / 30) + 1] == '1')
    //     return (1);
    // if (cub->par.map[((int)(*y_ver / 30) + 1)][(int)*x_hor / 30] == '1'
    //     && cub->par.map[(int)*y_ver / 30][(int)(*x_hor / 30) - 1] == '1')
    //     return (1);
    // if (cub->par.map[((int)(*y_ver / 30) + 1)][(int)*x_hor / 30] == '1'
    //     && cub->par.map[(int)*y_ver / 30][(int)(*x_hor / 30) + 1] == '1')
    //     return (1);
    return (0);
}

void cast_rays(t_cub *cub)
{
    double dx, dy;
    float x_increment;
    float y_increment;
    float x_hor;
    float y_ver;
    float steps;
    int   l;

    while(l < cub->degree / cub->angle_increment)
    {
        dx = cub->point[l].x_end;
        dy = cub->point[l].y_end;
        steps = fabs(dy) + fabs(dx);
        x_increment = dx / steps;
        y_increment = dy / steps;
        x_hor = cub->par.x;
        y_ver = cub->par.y;
        while (1)
        {
            if (cub->par.map[(int)floor(y_ver)/ 30][(int)floor(x_hor) / 30] == '1')
                break;
            if (check_holes(cub, &x_hor, &y_ver, x_hor -x_increment, y_ver- y_increment) == 1)
                break;
            mlx_put_pixel(cub->mlx.img_ptr, x_hor, y_ver, 0xAA4A44);
            x_hor += x_increment;
            cub->point[l].x_end = x_hor;
            y_ver += y_increment;
            cub->point[l].y_end = y_ver;
        }
        l++;
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
        cub->point[i].x_end = (cos(cub->angle + (cub->rot.first_angle - (cub->degree / 2))));
        cub->point[i].y_end = (sin(cub->angle + (cub->rot.first_angle - (cub->degree / 2))));
        cub->angle += cub->angle_increment;
        i++;
    }
}
//**********************
// void    draw_line(t_cub *cub, int i)
// {
//     t_line    line;

//     line.dx = cub->rx[i] - cub->par.x;
//     line.dy = cub->ry[i] - cub->par.y;
//     line.ste = fmax(fabs(line.dx), fabs(line.dy));
//     line.xi = line.dx / line.ste;
//     line.yi = line.dy / line.ste;
//     line.x = cub->par.x;
//     line.y = cub->par.y;
//     while (line.ste >= 0)
//     {
//         line.gx = (int)floor(line.x);
//         line.gy = (int)floor(line.y);
//         // if (cub->par.map[line.gy / 30][line.gx / 30] == '1')
//         //     break ;
//         // if (check_holes(cub, &line.x, &line.y, line.x -line.xi, line.y -line.yi) == 1)
//         //         break;
//         mlx_put_pixel(cub->mlx.img_ptr, (int)line.x, (int)line.y, 0x800080FF);
//         line.x += line.xi;
//         line.y += line.yi;
//         line.ste--;
//     }
// }
// void    cast_loop(t_cub *cub)
// {
//     int    i;

//     i = -1;
//     cub->degree = M_PI / 3.0;
//     cub->angle_increment = (cub->degree / (cub->mlx.width * 30));
//     while (++i < cub->mlx.width * 30)
//     {
//         cub->ang[i] = (cub->rot.first_angle - (cub->degree / 2.0)) + i * cub->angle_increment;
//         cub->dx[i] = cos(cub->ang[i]);
//         cub->dy[i] = sin(cub->ang[i]);
//         cub->rx[i] = cub->par.x;
//         cub->ry[i] = cub->par.y;
//         while (1)
//         {
//             cub->rx[i] += cub->dx[i];
//             // if (cub->par.map[(int)cub->ry[i]][(int)cub->rx[i]] != '1')
//             //     cub->side[i] = LEFTRIGHT;
//             cub->ry[i] += cub->dy[i];
//             // if (cub->map->map[(int)cub->ry[i]][(int)cub->rx[i]] != '1')
//             //     cub->side[i] = TOPBOTTOM;
//             // if (cub->par.map[(int)cub->ry[i] / 30][(int)cub->rx[i] /30] == '1')
//             //     break;
//             if (cub->rx[i] < 0 || cub->rx[i] >= cub->mlx.width * 30
//                 || cub->ry[i] < 0 || cub->ry[i] >= cub->mlx.height * 30)
//                 break ;
//         }
//         // side_select(cub, cas, i);
//         // draw_column(cub, cas, i);
//     }
//     i = -1;
//     while(++i < cub->mlx.width * 30)
//         draw_line(cub, i);
// }
//***********************
// void    draw_wall(t_cub *cub)
// {
//     float x = cub->point->x_end - cub->par.x;
//     float y = cub->point->y_end - cub->par.y;
//     printf ("%lf %lf\n", x, y);
// }

void    draw_player_in_image(t_cub *cub, int i, int j)
{
    cub->par.x += i;
    cub->par.y += j;
    // int x;
    // int y;
    // int radian;
    
    // radian = 5;
    // x = -1 * radian;
    // while(x < radian)
    // {
    //     y = -1 * radian;
    //     while(y < radian)
    //     {
    //         if (x*x + y*y < radian*radian)
                mlx_put_pixel(cub->mlx.img_ptr,  (cub->par.x + i), (cub->par.y + j)  , 0xC41E3A);
    //         y++;
    //     }
    //     x++;
    // }
    find_point(cub);
    cast_rays(cub);
    // cast_loop(cub);
    // draw_wall(cub);
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
void    loop_hook( void *cub)
{
    t_cub *cu = (t_cub *)cub;
    if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_A))
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_A) == 1)
            draw_player_in_image(cub, -1, 0);
        else  
            draw_player_in_image(cub, 0, 0);  
    }
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_W))
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_W) == 1)
            draw_player_in_image(cub, 0, -1);
        else
            draw_player_in_image(cub, 0, 0);
    }
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_D))
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_D) == 1)
            draw_player_in_image(cub, 1, 0);
        else  
            draw_player_in_image(cub, 0, 0);
    }
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_S))
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_S) == 1)
            draw_player_in_image(cub, 0, 1);
        else  
            draw_player_in_image(cub, 0, 0);
    }
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_LEFT))
    {
        cu->rot.first_angle += 0.25;
        if (cu->rot.first_angle > 2 * M_PI)
            cu->rot.first_angle -= 2 * M_PI;
        if (cu->rot.first_angle < 0)
            cu->rot.first_angle += 2 * M_PI;
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    // printf ("xxxx\n");
    }
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_RIGHT))
    {
        cu->rot.first_angle -= 0.25;
        if (cu->rot.first_angle > 2 * M_PI)
            cu->rot.first_angle -= 2 * M_PI;
        if (cu->rot.first_angle < 0)
            cu->rot.first_angle += 2 * M_PI;
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
