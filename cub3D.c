/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/26 22:55:05 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include "libft/libft.h"
#include "mlx42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslimits.h>

void allocation_map(t_cub *cub, char *map) {
	map_len(map, cub);
	cub->par.element = malloc(sizeof(char *) * (cub->par.cnt_elmt + 1));
	if (!cub->par.element) {
		free(cub->par.element);
		exit(1);
	}
	cub->par.map = malloc(sizeof(char *) * (cub->par.cnt_map + 1));
	if (!cub->par.map) {
		free(cub->par.map);
		exit(1);
	}
	cub->par.file =
			malloc(sizeof(char *) * (cub->par.cnt_map + 1 + cub->par.cnt_elmt));
	if (!cub->par.file) {
		free(cub->par.file);
		exit(1);
	}
}

void draw_wall_in_image(t_cub *cub) {
	int put1;
	int put2;

	while (cub->par.map[cub->i] != NULL) {
		cub->j = 0;
		while (cub->par.map[cub->i][cub->j] != '\0') {
			if (cub->par.map[cub->i][cub->j] == '1') {
				put1 = 0;
				while (put1 < 30) {
					put2 = 0;
					while (put2 < 30) {
						mlx_put_pixel(cub->mlx.img_ptr,
													MINIMAP_SCALE_FACTOR * ((cub->j * 30) + put1),
													MINIMAP_SCALE_FACTOR * ((cub->i * 30) + put2), 0x6a);
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

void draw_white_in_image(t_cub *cub) {
	cub->i = 0;
	cub->j = 0;
	while (cub->i < (cub->mlx.width * 30 * MINIMAP_SCALE_FACTOR)) {
		cub->j = 0;
		while (cub->j < (cub->mlx.height * 30 * MINIMAP_SCALE_FACTOR)) {
			mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j, 0xffffffff);
			cub->j++;
		}
		cub->i++;
	}
	cub->i = 0;
	cub->j = 0;
}

void player(t_cub *cub) {
	cub->par.pyp = 0;
	while (cub->par.map[cub->par.pyp] != NULL) {
		cub->par.pxp = 0;
		while (cub->par.map[cub->par.pyp][cub->par.pxp] != '\0') {
			if (cub->par.map[cub->par.pyp][cub->par.pxp] == 'N')
				break;
			cub->par.pxp++;
		}
		if (cub->par.map[cub->par.pyp][cub->par.pxp] == 'N')
			break;
		cub->par.pyp++;
	}
}
int check_holes(t_cub *cub, float prev_x, float prev_y) {

	if ((cub->par.map[((int)(cub->ray.y_ver / 30))][(int)prev_x / 30] == '1' &&
			 cub->par.map[(int)prev_y / 30][(int)(cub->ray.x_hor / 30)] == '1') ||
			cub->par.map[(int)floor(cub->ray.y_ver) / 30]
									[(int)floor(cub->ray.x_hor) / 30] == '1')
		return (1);
	return (0);
}
void calculate_slope(int i, t_cub *cub) {
	double dx;
	double dy;
	float steps;

	dx = cub->point[i].x_end;
	dy = cub->point[i].y_end;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	// steps = (fabs(dx) + fabs(dy)) * 0.08;
	cub->ray.x_inc = dx / steps;
	cub->ray.y_inc = dy / steps;
}

void cast_rays(t_cub *cub) {
	int i;
	bool check;

	i = 0;
	while (i < WIDTH) {
		calculate_slope(i, cub);
		cub->ray.x_hor = cub->par.x;
		cub->ray.y_ver = cub->par.y;
		while (1) {
			
			check = false;
			if (check_holes(cub, cub->ray.x_hor - cub->ray.x_inc,
											cub->ray.y_ver - cub->ray.y_inc) == 1)
				break;
			mlx_put_pixel(cub->mlx.img_ptr, MINIMAP_SCALE_FACTOR * cub->ray.x_hor,
										MINIMAP_SCALE_FACTOR * cub->ray.y_ver, 0xAA4A44);
			cub->ray.x_hor += cub->ray.x_inc;
			cub->point[i].x_end = cub->ray.x_hor;
			if (cub->par.map[(int)floor(cub->point[i].y_end) / 30][(int)floor(cub->point[i].x_end) / 30] == '1')
			{
				check = true;
				cub->point[i].view = LEFT_RIGHT;
				if (cos(cub->point[i].angle ) >= 0)
					cub->point[i].direction = RIGHT;
				else
					cub->point[i].direction = LEFT;
			}
			cub->ray.y_ver += cub->ray.y_inc;
			cub->point[i].y_end = cub->ray.y_ver;
			if (cub->par.map[(int)floor(cub->point[i].y_end )/ 30][(int)floor(cub->point[i].x_end) / 30] == '1' && check == false)
			{
				cub->point[i].view = TOP_BOTTOM;
				if (sin(cub->point[i].angle) >= 0)
					cub->point[i].direction = TOP;
				else
					cub->point[i].direction = BOTTOM;
			}
		}
		i++;
	}
}
void find_point(t_cub *cub) {
	int i;

	i = 0;
	cub->point = malloc(sizeof(t_point) * WIDTH);
	double angle = 0;
	while (i < WIDTH)
	{
		cub->point[i].x_end = cos(angle + (cub->ray.first_angle - (DEGREE / 2)));
		cub->point[i].y_end = sin(angle + (cub->ray.first_angle - (DEGREE / 2)));
		cub->point[i].angle = angle + cub->ray.first_angle - (DEGREE / 2);
		angle += ANGLE_INCREMENT;
		i++;
	}
}

int check_wall(t_cub *cub, double x, double y) {
	if (cub->par.map[(int)y / 30][(int)x / 30] == '1')
		return (0);
	return (1);
}
void key_ad(t_cub *cub, int sign) {
	if (sign == 0) {
		cub->par.x += cos(cub->ray.first_angle - (M_PI / 2));
		cub->par.y += sin(cub->ray.first_angle - (M_PI / 2));
	} else {
		cub->par.x -= cos(cub->ray.first_angle - (M_PI / 2));
		cub->par.y -= sin(cub->ray.first_angle - (M_PI / 2));
	}
}
void key_ws(t_cub *cub, int sign) {
	if (sign == 0) {
		cub->par.x += cos(cub->ray.first_angle);
		cub->par.y += sin(cub->ray.first_angle);
	} else {
		cub->par.x -= cos(cub->ray.first_angle);
		cub->par.y -= sin(cub->ray.first_angle);
	}
}
void key_lr(t_cub *cub, int sign) {
	if (sign == 0)
		cub->ray.first_angle -= 0.05;
	else
		cub->ray.first_angle += 0.05;
	if (cub->ray.first_angle > 2 * M_PI)
		cub->ray.first_angle -= 2 * M_PI;
	if (cub->ray.first_angle < 0)
		cub->ray.first_angle += 2 * M_PI;
}
void draw_fc(t_cub *cub) {
	cub->i = 0;
	cub->j = 0;
	while (cub->i < WIDTH) {
		cub->j = 0;
		while (cub->j < HEIGHT) {
			if (cub->j < HEIGHT / 2)
				mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j, cub->par.ceiling);
			else
				mlx_put_pixel(cub->mlx.img_ptr, cub->i, cub->j, cub->par.floor);
			cub->j++;
		}
		cub->i++;
	}
	cub->i = 0;
	cub->j = 0;
}
void pixel_draw(int x0, int y0, t_cub *game, int color) {
	if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
		mlx_put_pixel(game->mlx.img_ptr, x0, y0, color);
}

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
	return (r << 24 | g << 16 | b << 8 | a);
}
uint32_t pixelcolor(t_cub *cub, double x, double y)
{
		static unsigned int i;
		static unsigned int factor;
		uint32_t color;
		
		color = 0;
		if (i < cub->txt->width * cub->txt->height * 4)
		{
				color = ft_pixel(cub->txt->pixels[i], cub->txt->pixels[i + 1], cub->txt->pixels[i + 2], cub->txt->pixels[i + 3]);
				i += cub->txt->width * 4;
				if (x == y)
				{
						factor += 4;
						i = factor;
				}
		}
		else
		{
				factor = 0;
				i = 0;
		}
	return (color);
}

void	drawline(int x0, int y0, int x1, int y1, t_cub *game)
{
	int		dx;
	int		dy;
	int		i;
	int		steps;
		int     x_inc, y_inc;

	i = 0;
	dx = x1 - x0;
	dy = y1 - y0;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	while (i <= steps)
	{
		pixel_draw(x0, y0, game, ft_pixel(25, 50, 20, 1));
		x0 += x_inc;
		y0 += y_inc;
		i++;
	}
}
void    draw_view( t_cub *cub)
{
    double wallHeight;
    double x;
    double y;
    double distance;
    double correctdistance;
    int32_t color;

	int i;
    double rayangle = cub->ray.first_angle - (DEGREE / 2);

	i = 0;
    while (i < WIDTH)
    {
        distance = sqrt((pow((cub->point[i].x_end / 30) - (cub->par.x / 30), 2)) + (pow((cub->point[i].y_end/30) - (cub->par.y / 30), 2)));
        correctdistance = distance * cos(rayangle - cub->ray.first_angle);
        wallHeight = floor((HEIGHT / 2) / (correctdistance));
		/////
		// int ss=cub->point[i].x_end/30;
		int pppp=(cub->point[i].x_end - (int)(cub->point[i].x_end/30) *30) / 30 * cub->txt->width;
		//////
        x = (HEIGHT / 2) - wallHeight;
        y = (HEIGHT / 2) + wallHeight;
        // drawline(i, x, i, HEIGHT / 2, cub);
        // drawline(i, (HEIGHT / 2), i, y, cub);
        while (x <= y)
        {
			if (x > 0 && x < WIDTH)
			{
            	color = cub->color_texture[(int)x][pppp];
            	mlx_put_pixel(cub->mlx.img_ptr, i, x, color);
			}
            x++;
        }
        rayangle += ANGLE_INCREMENT;
        i++;
    }
}


// void    draw_view( t_cub *cub)
// {
// 		double wallHeight;
// 		// double x;
// 		double distance;
// 		double correctdistance;
// 		uint32_t color;
// 		double y_inc;
// 		int x_pos;
// 		int i = 0;
		
// 		double rayangle = cub->ray.first_angle - (DEGREE / 2);
// 		while (i < WIDTH)
// 		{
// 				distance = sqrt((pow((cub->point[i].x_end / 30) - (cub->par.x / 30), 2)) + (pow((cub->point[i].y_end/30) - (cub->par.y / 30), 2)));
// 				correctdistance = distance * cos(rayangle - cub->ray.first_angle);
// 				wallHeight = floor((HEIGHT / 2) / (correctdistance));
// 				// x = (HEIGHT / 2) - wallHeight;
// 				// y = (HEIGHT / 2) + wallHeight;
// 				y_inc = cub->txt->height / wallHeight;
// 				if (cub->point[i].view == LEFT_RIGHT)
// 					x_pos = ((int)cub->point[i].x_end / 30 * ((int)cub->txt->width / 30)) % cub->txt->width;
// 				else if (cub->point[i].view == TOP_BOTTOM)
// 					x_pos = ((int)(cub->point[i].y_end/30) * ((int)cub->txt->width) / 30)  % cub->txt->width;
// 				double y = 0;
// 				while (y < cub->txt->height)
// 				{
// 					color = 0;
// 					mlx_put_pixel(cub->mlx.img_ptr, i, x_pos, color);
// 					y += y_inc;
// 					x_pos++;
// 				}
// 				i++;
// 		}
		
// }
void    draw_map(void *cu)
{
		t_cub *cub = (t_cub *)cu;
		draw_fc(cub);
		draw_view(cub);
}
void    loop_hook( void *cub)
{
		t_cub *cu = (t_cub *)cub;
		if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_A)  
				&& check_wall(cub, cu->par.x + cos(cu->ray.first_angle -(M_PI / 2)), 
						cu->par.y + sin(cu->ray.first_angle -(M_PI / 2))) != 0)
				{
				key_ad(cu, 0);
						draw_map(cu);
				}
		else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_W) 
				&& check_wall(cub, cu->par.x + cos(cu->ray.first_angle),
						 cu->par.y + sin(cu->ray.first_angle)) != 0)
						{
				key_ws(cu, 0);
				draw_map(cu);}
		else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_D) 
				&& check_wall(cub, cu->par.x - cos(cu->ray.first_angle 
						-(M_PI / 2)), cu->par.y - sin(cu->ray.first_angle -(M_PI / 2))) != 0)
						{
				key_ad(cu, 1);
				draw_map(cu);}
		else if(mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_S) 
				&& check_wall(cub, cu->par.x - 
						cos(cu->ray.first_angle), cu->par.y - sin(cu->ray.first_angle)) != 0)
						{
				key_ws(cu, 1);
				draw_map(cu);}
		else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_LEFT))
		{
				key_lr(cu, 0);
				draw_map(cu);}
		else if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_RIGHT))
		{
				key_lr(cu, 1);
				draw_map(cu);}
		if (mlx_is_key_down(cu->mlx.init_ptr, MLX_KEY_ESCAPE))
				mlx_close_window(cu->mlx.init_ptr);
}


void load_textures(t_cub *cub) 
{
	uint32_t i;
	uint32_t x;
	uint32_t y;
	
	i  = 0;
	x = 0;
	y = 0;
	cub->txt = mlx_load_png("textures/wall.png");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->color_texture = malloc(sizeof(uint32_t *) * cub->txt->height);
	if (!cub->color_texture)
		return ;
	while(i < cub->txt->height)
	{
			cub->color_texture[i] = malloc(sizeof(uint32_t) * cub->txt->width);
			if (!cub->color_texture[i]) //free || !!!!!!?
				return;
			i++;
	}
	i = 0;
	// uint32_t x = 0;
	// uint32_t y= 0;
	while(i < cub->txt->height * cub->txt->width * cub->txt->bytes_per_pixel) // or * 4
	{
		cub->color_texture[x][y] = ft_pixel(cub->txt->pixels[i], cub->txt->pixels[i + 1]
				, cub->txt->pixels[i + 2], cub->txt->pixels[i + 3]);
			y++;
			if (y == cub->txt->width)
			{
				x++;
				y = 0;
			}
		i += 4;
		
	}
	// printf ("%d %d",cub->txt->height * cub->txt->width * 4, i);
	// exit(0);
}
// void draw_map(void *cu) {
//   t_cub *cub = (t_cub *)cu;
//   draw_fc(cub);
//   draw_view(cub);
// }

void draw_minimap(void *cub) {
	t_cub *cu;

	cu = (t_cub *)cub;
	draw_white_in_image(cu);
	draw_wall_in_image(cu);
	mlx_put_pixel(cu->mlx.img_ptr, MINIMAP_SCALE_FACTOR * (cu->par.x),
								MINIMAP_SCALE_FACTOR * (cu->par.y), 0xC41E3A);
	find_point(cu);
	cast_rays(cu);
//   
//     draw_view(cub);
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
		mlx_image_to_window(cub.mlx.init_ptr,cub.mlx.img_ptr,0,0);
				if (!(cub.mlx.init_ptr || cub.mlx.img_ptr))
			return (EXIT_FAILURE);
				load_textures(&cub);
				mlx_loop_hook(cub.mlx.init_ptr, loop_hook, &cub);
				// mlx_loop_hook(cub.mlx.init_ptr, draw_minimap, &cub);
				// mlx_loop_hook(cub.mlx.init_ptr, draw_map, &cub);
				draw_minimap(&cub);
				draw_map(&cub);
				mlx_loop_hook(cub.mlx.init_ptr, draw_minimap, &cub);
		mlx_loop(cub.mlx.init_ptr);
		mlx_terminate(cub.mlx.init_ptr);
	}
	return (0);
}
