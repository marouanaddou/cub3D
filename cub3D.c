/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/15 19:18:54 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"
#include "mlx42/include/MLX42/MLX42.h"
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
int check_holes(t_cub *cub, float *x_hor, float *y_ver)
{
    if (cub->par.map[((int)(*y_ver / 30) - 1)][(int)*x_hor / 30] == '1'
        && cub->par.map[(int)*y_ver / 30][(int)(*x_hor / 30) - 1] == '1')
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


    l = 0;
    while(l < cub->degree / cub->angle_increment)
    {
       
        dx = cub->point[l].x_end - (cub->par.x);
        dy = cub->point[l].y_end - (cub->par.y);
        if (fabs(dx) > fabs(dy))
            steps = fabs(dx);
        else
            steps = fabs(dy);
        x_increment = dx / steps;
        y_increment = dy / steps;
        x_hor = cub->par.x;
        y_ver = cub->par.y;
        while (1)
        {
            if (check_holes(cub, &x_hor, &y_ver) == 1)
            {
                break;
            }
            mlx_put_pixel(cub->mlx.img_ptr, x_hor, y_ver, 0xAA4A44);
            if ( cub->par.map[((int)floor(y_ver)/ 30)][((int)floor(x_hor) / 30)] == '1')
            {
                if (cub->par.map[(int)floor(y_ver)/ 30][(int)floor(x_hor) / 30] == '1')
                {
                    // printf("%lf---%lf\n", x_hor/30, y_ver/30);
                    break;
                }
            }
            x_hor += x_increment;
            y_ver += y_increment;
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
    cub->point = malloc(sizeof(t_point) * (cub->degree / cub->angle_increment) + 1);
    cub->angle = 0;
    while(cub->angle < cub->degree)
    {
        cub->point[i].x_end = (cub->par.x) + (cos(cub->angle + (cub->rot.first_angle - (cub->degree / 2))));
        cub->point[i].y_end = (cub->par.y) + (sin(cub->angle +(cub->rot.first_angle - (cub->degree / 2))));
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
                mlx_put_pixel(cub->mlx.img_ptr,  (cub->par.x + i) + x, (cub->par.y + j) + y , 0xC41E3A);
            y++;
        }
        x++;
    }
    find_point(cub);
    cast_rays(cub);
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
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        draw_player_in_image(cub, 0, 0);
    }
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_RIGHT))
    {
        cu->rot.first_angle -= 0.25;
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
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
        // mlx_key_hook(cub.mlx.init_ptr, key_hook, &cub);
        mlx_loop_hook(cub.mlx.init_ptr, loop_hook, &cub);
		mlx_loop(cub.mlx.init_ptr);
		mlx_terminate(cub.mlx.init_ptr);
	}
	return (0);
}
