
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

void draw_line(t_cub *cub, int i, int j)
{
    double dx, dy;
    float x_increment;
    float y_increment;
    float x;
    float y;
    float steps;
    int   l;
    float endx = cub->par.x + 70 * cos(cub->anglel);
    float endy = cub->par.y + 70 * sin(cub->anglel);
    l = 0;
    while(l < cub->degree / cub->angle_increment)
    {
        dx = endx	 - (cub->par.x + i);
        dy = 	endy - (cub->par.y + j);
        if (fabs(dx) > fabs(dy))
            steps = fabs(dx);
        else
            steps = fabs(dy);
        x_increment = dx / steps;
        y_increment = dy / steps;
        x = cub->par.x + i;
        y = cub->par.y + j;
        while (1)
        {
            if(endx == x || endy == y)
                break;
            mlx_put_pixel(cub->mlx.img_ptr, x, y, 0xAA4A44);
            // if (cub->par.map[(int)y / 30][(int)x / 30] == '1')
            //     break;
            x += x_increment;
            y += y_increment;
        }
        l++;
    } 
}
// void draw_line(t_cub *cub, int end_point_x, int end_point_y)
// {
//     int start_point_x = 0;  // You need to determine the starting point
//     int start_point_y = 0;  // You need to determine the starting point

//     int dx = end_point_x - start_point_x;
//     int dy = end_point_y - start_point_y;
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

//     float x_increment = (float)dx / steps;
//     float y_increment = (float)dy / steps;

//     float x = start_point_x;
//     float y = start_point_y;

//     for (int i = 0; i <= steps; i++) 
// 	{

// 		if(x == end_point_x && y == end_point_y)
// 			break;
//         // Plot the pixel at (x, y) with the specified color using your graphics library
//         // Example: plot_pixel(cub, (int)x, (int)y, color);

//         x += x_increment;
//         y += y_increment;
//     }
// }

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
    draw_line(cub, i , j);
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
    cu->d = 0;
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
    {
        draw_white_in_image(cu);
        draw_wall_in_image(cu);
        if (check_wall(cub, MLX_KEY_S) == 1)
            draw_player_in_image(cub, 0, 5);
        else  
            draw_player_in_image(cub, 0, 0);
    }
    else if(data.key == MLX_KEY_S && data.action == MLX_KEY_LEFT)
    {
        cu->d = 1;
    }
    else if(data.key == MLX_KEY_S && data.action == MLX_KEY_RIGHT)
    {
        cu->d = -1;
    }
    
    cu->anglel += cu->d;
}

void    find_point(t_cub *cub)
{
    int i;
    float    ray_angle;

    i = 0;
    
    cub->degree = 60 * (M_PI / 180);
    ray_angle = M_PI - (cub->degree / 2);
    cub->angle_increment = (cub->degree / (cub->mlx.width * 30));
    cub->point = malloc(sizeof(t_point) * (cub->degree / cub->angle_increment) + 1);
    while(i < cub->degree)
    {
        cub->point[i].x_end = 50;
        cub->point[i].y_end = 50;
        cub->angle += cub->angle_increment;
        i++;
    }
}
// void    cast_all_rays(t_struct *cub) 
// {     
//     float    ray_angle;
//     float    fov_angle;
//     float    radian_beetwen_rays;
//     int        strip_id;
    
//     strip_id = 0; 
//     fov_angle = (60 * (M_PI / 180));
//     ray_angle = cub->player.rotation_angle - (fov_angle / 2);
//     radian_beetwen_rays = fov_angle / NUM_RAYS;
//     while (strip_id < NUM_RAYS)     
//     {         
//         cast_ray(cub, ray_angle, strip_id);
//         ray_angle += radian_beetwen_rays;         strip_id++;     
                
//     }
// }

int main(int ac, char **av)
{
    t_cub	cub;
    if (ac == 2)
    {
        cub.anglel = M_PI;
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
        find_point(&cub);
        draw_player_in_image(&cub, 0, 0);
        mlx_key_hook(cub.mlx.init_ptr, key_hook, &cub);
        // mlx_loop_hook(cub.mlx.init_ptr, key_release, &cub);
		mlx_loop(cub.mlx.init_ptr);
		mlx_terminate(cub.mlx.init_ptr);
	}
	return (0);
}