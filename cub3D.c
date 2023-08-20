/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/20 14:01:36 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"
#include "libft/libft.h"
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
                        mlx_put_pixel(cub->mlx.img_ptr, MINIMAP_SCALE_FACTOR * ((cub->j * 30) + put1), MINIMAP_SCALE_FACTOR *((cub->i * 30) +put2) ,0x00000000);
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
    while(cub->i < (cub->mlx.width * 30 * MINIMAP_SCALE_FACTOR))
    {
        cub->j = 0;
        while(cub->j < (cub->mlx.height * 30 * MINIMAP_SCALE_FACTOR))
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

    if ((cub->par.map[((int)(cub->ray.y_ver / 30))][(int)prev_x / 30] == '1'
        && cub->par.map[(int)prev_y / 30][(int)(cub->ray.x_hor / 30)] == '1') 
        || cub->par.map[(int)floor(cub->ray.y_ver)/ 30][(int)floor(cub->ray.x_hor) / 30] 
        == '1')
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
    while(i < DEGREE / ANGLE_INCREMENT)
    {
        calculate_slope(i, cub);
        cub->ray.x_hor = cub->par.x;
        cub->ray.y_ver = cub->par.y;
        while (1)
        {
            if (check_holes(cub, cub->ray.x_hor - cub->ray.x_inc, cub->ray.y_ver - cub->ray.y_inc) == 1)
                break;
            mlx_put_pixel(cub->mlx.img_ptr, MINIMAP_SCALE_FACTOR * cub->ray.x_hor, MINIMAP_SCALE_FACTOR * cub->ray.y_ver, 0xAA4A44);
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
    double angle;

    i = 0;
    cub->point = malloc(sizeof(t_point) * ((DEGREE / ANGLE_INCREMENT) + 1));
    angle = 0;
    while(i < WIDTH)
    {
        cub->point[i].x_end = cos(angle + (cub->ray.first_angle - (DEGREE / 2)));
        cub->point[i].y_end = sin(angle + (cub->ray.first_angle - (DEGREE / 2)));
        angle += ANGLE_INCREMENT;
        i++;
    }
}

int check_wall(t_cub *cub, double x, double y)
{
    if (cub->par.map[(int)y/30][(int)x/30] == '1')
        return (0);
    return (1);

}
void    key_ad(t_cub *cub ,int sign)
{
    if (sign == 0)
    {
        cub->par.x += cos(cub->ray.first_angle -(M_PI / 2));
        cub->par.y += sin(cub->ray.first_angle -(M_PI / 2));
    }
    else 
    {
        cub->par.x -= cos(cub->ray.first_angle -(M_PI / 2));
        cub->par.y -= sin(cub->ray.first_angle -(M_PI / 2));
    }
}
void    key_ws(t_cub *cub ,int sign)
{
    if (sign == 0)
    {
        cub->par.x += cos(cub->ray.first_angle );
        cub->par.y += sin(cub->ray.first_angle );
    }
    else 
    {
        cub->par.x -= cos(cub->ray.first_angle );
        cub->par.y -= sin(cub->ray.first_angle );
    }
}
void    key_lr(t_cub *cub ,int sign)
{
    if (sign == 0)
        cub->ray.first_angle += 0.10;
    else  
        cub->ray.first_angle -= 0.10;
    if (cub->ray.first_angle > 2 * M_PI)
        cub->ray.first_angle -= 2 * M_PI;
    if (cub->ray.first_angle < 0)
        cub->ray.first_angle += 2 * M_PI;
}
void    loop_hook( void *cub)
{
    t_cub *cu = (t_cub *)cub;
    if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_A)  
        && check_wall(cub, cu->par.x + cos(cu->ray.first_angle -(M_PI / 2)), 
            cu->par.y + sin(cu->ray.first_angle -(M_PI / 2))) != 0)
        key_ad(cu, 0);
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_W) 
        && check_wall(cub, cu->par.x + cos(cu->ray.first_angle),
             cu->par.y + sin(cu->ray.first_angle)) != 0)
        key_ws(cu, 0);
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_D) 
        && check_wall(cub, cu->par.x - cos(cu->ray.first_angle 
            -(M_PI / 2)), cu->par.y - sin(cu->ray.first_angle -(M_PI / 2))) != 0)
        key_ad(cu, 1);
    else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_S) 
        && check_wall(cub, cu->par.x - 
            cos(cu->ray.first_angle), cu->par.y - sin(cu->ray.first_angle)) != 0)
        key_ws(cu, 1);
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_LEFT))
        key_lr(cu, 0);
    else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_RIGHT))
        key_lr(cu, 1);
    if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_ESCAPE))
        mlx_close_window(cu->mlx.init_ptr);
}
int     rgb_convert(char *path, char c)
{
    char **color;
    c = 0;
    color = ft_split(path, ',');
        if (c == 'f')
            return (255 << 24 | atoi(color[0]) << 16 | atoi(color[1]) << 8 | atoi(color[2]));
        else if (c == 'c')
            return (255 << 24 | atoi(color[0]) << 16 | atoi(color[1]) << 8 | atoi(color[2]));
    return (0);
}
void    draw_map(void *cub)
{
    t_cub *cu = (t_cub *)cub;
    cu->i = 0;
    cu->j = 0;
    char **color = ft_split(cu->par.elm[4].path, ',');
    int    x = 255 << 24 | atoi(color[0]) << 16 | atoi(color[1]) << 8 | atoi(color[2]);
    printf ("%d ", x);
    color = ft_split(cu->par.elm[5].path, ',');
     int b= (255 << 24 | atoi(color[0]) << 16 | atoi(color[1]) << 8 | atoi(color[2]));
    while(cu->i < WIDTH)
    {
        cu->j = 0;
        while(cu->j < HEIGHT)
        {
            if (cu->j < HEIGHT / 2)
                mlx_put_pixel(cu->mlx.img_ptr, cu->i, cu->j, x);
            else
                mlx_put_pixel(cu->mlx.img_ptr, cu->i, cu->j, b);

            cu->j++;
        }
        cu->i++;
    }
    cu->i = 0;
    cu->j = 0;
}

void    draw_minimap (void *cub)
{
    t_cub *cu;

    cu = (t_cub *)cub;
    draw_white_in_image(cu);
    draw_wall_in_image(cu);
    mlx_put_pixel(cu->mlx.img_ptr,  MINIMAP_SCALE_FACTOR * (cu->par.x), MINIMAP_SCALE_FACTOR *(cu->par.y)  , 0xC41E3A);
    find_point(cu);
    cast_rays(cu);
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
		cub.mlx.init_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
		cub.mlx.img_ptr = mlx_new_image(cub.mlx.init_ptr, WIDTH, HEIGHT);
        // cub.mlx.fullimg_ptr = mlx_new_image(cub.mlx.init_ptr, WIDTH, HEIGHT);
		mlx_image_to_window(cub.mlx.init_ptr,cub.mlx.img_ptr,0,0);
        // mlx_image_to_window(cub.mlx.init_ptr,cub.mlx.fullimg_ptr,0,0);
        if (!(cub.mlx.init_ptr || cub.mlx.img_ptr))
			return (EXIT_FAILURE);
        mlx_loop_hook(cub.mlx.init_ptr, draw_map, &cub);
        mlx_loop_hook(cub.mlx.init_ptr, loop_hook, &cub);
        mlx_loop_hook(cub.mlx.init_ptr, draw_minimap, &cub);
		mlx_loop(cub.mlx.init_ptr);
		mlx_terminate(cub.mlx.init_ptr);
	}
	return (0);
}
