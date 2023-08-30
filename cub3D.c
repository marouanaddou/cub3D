/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/30 13:25:47 by maddou           ###   ########.fr       */
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

void allocation_map(t_cub *cub, char *map) 
{
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

int check_holes(t_cub *cub, float prev_x, float prev_y) {

	if ((cub->par.map[((int)(cub->ray.y_ver / 30))][(int)prev_x / 30] == '1' &&
			 cub->par.map[(int)prev_y / 30][(int)(cub->ray.x_hor / 30)] == '1') ||
			cub->par.map[(int)floor(cub->ray.y_ver) / 30]
									[(int)floor(cub->ray.x_hor) / 30] == '1')
		return (1);
	return (0);
}
void calculate_slope(int i, t_cub *cub) {
	
	// double dx;
	// double dy;
	// double steps;

	// dx = cub->point[i].x_end;
	// dy = cub->point[i].y_end;
	// if (fabs(dx) > fabs(dy))
	// 	steps = fabs(dx);
	// else
	// 	steps = fabs(dy);
	// // steps = fabs(dx) + fabs(dy);
	// cub->ray.x_inc = dx / steps;
	// cub->ray.y_inc = dy / steps;
	
	///////////////
	float dx;
    float dy;
    int step;

    dx = cub->point[i].x_end;
    dy = cub->point[i].y_end;
    step = (int)(fabs(dx) + fabs(dy));
	cub->ray.x_inc = dx / step;
	cub->ray.y_inc = dy / step;
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
			mlx_put_pixel(cub->mlx.img_ptr, /*MINIMAP_SCALE_FACTOR **/cub->ray.x_hor,
										/*MINIMAP_SCALE_FACTOR **/cub->ray.y_ver, 0xAA4A44);
			cub->ray.x_hor += cub->ray.x_inc;
			cub->point[i].x_end = cub->ray.x_hor;
			if (cub->par.map[(int)floor(cub->point[i].y_end) / 30][(int)floor(cub->point[i].x_end) / 30] == '1')
			{
				check = true;
				cub->point[i].view = LEFT_RIGHT;
				if (cos(cub->point[i].angle) >= 0)
					cub->point[i].direction = RIGHT;
				else
					cub->point[i].direction = LEFT;
			}
			cub->ray.y_ver += cub->ray.y_inc;
			cub->point[i].y_end = cub->ray.y_ver;
			if (cub->par.map[(int)floor(cub->point[i].y_end)/ 30][(int)floor(cub->point[i].x_end) / 30] == '1' && check == false)
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



void pixel_draw(int x0, int y0, t_cub *game, int color) {
	if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
		mlx_put_pixel(game->mlx.img_ptr, x0, y0, color);
}

uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
	return (r << 24 | g << 16 | b << 8 | a);
}
// uint32_t pixelcolor(t_cub *cub, double x, double y)
// {
// 		static unsigned int i;
// 		static unsigned int factor;
// 		uint32_t color;
		
// 		color = 0;
// 		if (i < cub->txt->width * cub->txt->height * 4)
// 		{
// 				color = ft_pixel(cub->txt->pixels[i], cub->txt->pixels[i + 1], cub->txt->pixels[i + 2], cub->txt->pixels[i + 3]);
// 				i += cub->txt->width * 4;
// 				if (x == y)
// 				{
// 					factor += 4;
// 					i = factor;
// 				}
// 		}
// 		else
// 		{
// 				factor = 0;
// 				i = 0;
// 		}
// 	return (color);
// }

void    draw_view( t_cub *cub)
{
    double wallHeight;
    double x;
    double y;
    double distance;
    double correctdistance;
    int32_t color;
	int x_pos;
	int i;
    double rayangle;
	
	i = 0;
	rayangle = cub->ray.first_angle - (DEGREE / 2); 
    while (i < WIDTH)
    {
        distance = sqrt((pow((cub->point[i].x_end / 30) - (cub->par.x / 30), 2)) + (pow((cub->point[i].y_end/30) - (cub->par.y / 30), 2)));
        correctdistance = distance * cos(rayangle - cub->ray.first_angle);
        wallHeight = floor((HEIGHT / 2) / (correctdistance));
		if (cub->point[i].view == LEFT_RIGHT)
			x_pos=(cub->point[i].y_end - (int)(cub->point[i].y_end/30) *30) / 30 * cub->txt->width;
		else if (cub->point[i].view == TOP_BOTTOM)
			x_pos=(cub->point[i].x_end - (int)(cub->point[i].x_end/30) *30) / 30 * cub->txt->width;
        x = (HEIGHT / 2) - wallHeight;
        y = (HEIGHT / 2) + wallHeight;
        while (x <= y)
        {
			if (x > 0 && x < HEIGHT)
			{
				int y_inc = (2 * wallHeight - (y - x)) * cub->txt->height / (wallHeight * 2);
				if (y_inc < (int)cub->txt->height)
				{	
					if (cub->point[i].direction == LEFT)
            			color = cub->left_texture[(int)y_inc][x_pos];
					else if (cub->point[i].direction == RIGHT)
						color = cub->right_texture[(int)y_inc][x_pos];
					else if (cub->point[i].direction == TOP)
						color = cub->top_texture[(int)y_inc][x_pos];
					else if (cub->point[i].direction == BOTTOM)
						color = cub->bottom_texture[(int)y_inc][x_pos];
            		mlx_put_pixel(cub->mlx.img_ptr, i, x, color);
				}
			}
            x++;
        }
        rayangle += ANGLE_INCREMENT;
        i++;
    }
}




uint32_t	**fill_in_texture(t_cub *cub, uint32_t **texture)
{
	uint32_t i;
	uint32_t x;
	uint32_t y;
	
	i = 0;
	x = 0;
	y = 0;
	texture = malloc(sizeof(uint32_t *) * cub->txt->height);
	if (!texture)
		return(0) ;
	while(i < cub->txt->height)
	{
			texture[i] = malloc(sizeof(uint32_t) * cub->txt->width);
			if (!texture[i]) //free || !!!!!!?
				return(0);
			i++;
	}
	i = 0;
	while(i < cub->txt->height * cub->txt->width * cub->txt->bytes_per_pixel) // or * 4
	{
		texture[x][y] = ft_pixel(cub->txt->pixels[i], cub->txt->pixels[i + 1]
				, cub->txt->pixels[i + 2], cub->txt->pixels[i + 3]);		
			y++;
			if (y == cub->txt->width)
			{
				x++;
				y = 0;
			}
		i += 4;
	}
	return(texture);
}
void load_textures(t_cub *cub) 
{
	uint32_t i;
	uint32_t x;
	uint32_t y;
	
	i = 0;
	x = 0;
	y = 0;
	cub->txt = mlx_load_png("textures/BRICK_1A.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->right_texture = fill_in_texture(cub, cub->right_texture);
	cub->txt = mlx_load_png("textures/BRICK_2B.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->left_texture = fill_in_texture(cub, cub->left_texture);
	cub->txt = mlx_load_png("textures/BRICK_3B.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->top_texture = fill_in_texture(cub, cub->top_texture);
	cub->txt = mlx_load_png("textures/BRICK_3D.PNG");
	if (!cub->txt)
		return;
	cub->img = mlx_texture_to_image(cub->mlx.init_ptr, cub->txt);
	if (!cub->img)
		return;
	cub->bottom_texture = fill_in_texture(cub, cub->bottom_texture);
}

int main(int ac, char **av)
{
  t_cub cub;
  
  if (ac == 2) 
  {
    allocation_map(&cub, av[1]);
    check_file_ext(av[1]);
    load_map(av[1], &cub);
    check_information(&cub);
    check_map(&cub);
    cub.mlx.init_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
    cub.mlx.img_ptr = mlx_new_image(cub.mlx.init_ptr, WIDTH, HEIGHT);
    mlx_image_to_window(cub.mlx.init_ptr, cub.mlx.img_ptr, 0, 0);
    if (!(cub.mlx.init_ptr || cub.mlx.img_ptr))
      return (EXIT_FAILURE);
    load_textures(&cub);
	// mlx_set_cursor_mode(cub.mlx.init_ptr, MLX_MOUSE_DISABLED);
	// mlx_get_mouse_pos(cub.mlx.init_ptr, &cub.mouse_x, &cub.mouse_y);
    mlx_loop_hook(cub.mlx.init_ptr, loop_hook, &cub);
    mlx_loop_hook(cub.mlx.init_ptr, draw_minimap, &cub);
    // mlx_loop_hook(cub.mlx.init_ptr, draw_map, &cub);
    draw_minimap(&cub);
    // draw_fc(&cub);
    // draw_view(&cub);
    mlx_loop_hook(cub.mlx.init_ptr, draw_minimap, &cub);
    mlx_loop(cub.mlx.init_ptr);
    mlx_terminate(cub.mlx.init_ptr);
  }
  return (0);
}
