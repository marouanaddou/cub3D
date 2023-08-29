/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:51:55 by maddou            #+#    #+#             */
/*   Updated: 2023/08/30 00:17:44 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"

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

void  draw_ver_line(t_cub *cub, int i)
{
  	cub->y_inc = (2 * cub->wallHeight - (cub->y_end - cub->x_start)) * cub->txt->height / (cub->wallHeight * 2);
	if (cub->y_inc < (int)cub->txt->height)
	{
		if (cub->point[i].direction == LEFT)
			cub->color = cub->left_texture[(int)cub->y_inc][cub->x_pos];
		else if (cub->point[i].direction == RIGHT)
			cub->color = cub->right_texture[(int)cub->y_inc][cub->x_pos];
		else if (cub->point[i].direction == TOP)
			cub->color = cub->top_texture[(int)cub->y_inc][cub->x_pos];
		else if (cub->point[i].direction == BOTTOM)
			cub->color = cub->bottom_texture[(int)cub->y_inc][cub->x_pos];
		mlx_put_pixel(cub->mlx.img_ptr, i, cub->x_start, cub->color);
	}
}
void    draw_view( t_cub *cub)
{
	  int i;
	
	  i = 0;
	  cub->rayangle = cub->ray.first_angle - (DEGREE / 2); 
    while (i < WIDTH)
    {
    	cub->distance = sqrt((pow((cub->point[i].x_end / 30) - (cub->par.x / 30), 2)) + (pow((cub->point[i].y_end/30) - (cub->par.y / 30), 2)));
      cub->correctdistance = cub->distance * cos(cub->rayangle - cub->ray.first_angle);
      cub->wallHeight = floor((HEIGHT / 2) / (cub->correctdistance));
		if (cub->point[i].view == LEFT_RIGHT)
			cub->x_pos=(cub->point[i].y_end - (int)(cub->point[i].y_end/30) *30) / 30 * cub->txt->width;
		else if (cub->point[i].view == TOP_BOTTOM)
			cub->x_pos=(cub->point[i].x_end - (int)(cub->point[i].x_end/30) *30) / 30 * cub->txt->width;
    	cub->x_start = (HEIGHT / 2) - cub->wallHeight;
    	cub->y_end = (HEIGHT / 2) + cub->wallHeight;
      	while (cub->x_start <= cub->y_end)
      	{
			    if (cub->x_start > 0 && cub->x_start < HEIGHT)
        		draw_ver_line(cub, i);
            cub->x_start++;
		    }
    	cub->rayangle += ANGLE_INCREMENT;
    	i++;
    }
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
	  mlx_set_cursor_mode(cub.mlx.init_ptr, MLX_MOUSE_DISABLED);
	  mlx_get_mouse_pos(cub.mlx.init_ptr, &cub.mouse_x, &cub.mouse_y);
    mlx_loop_hook(cub.mlx.init_ptr, loop_hook, &cub);
    draw_minimap(&cub);
    draw_fc(&cub);
    draw_view(&cub);
    mlx_loop_hook(cub.mlx.init_ptr, draw_minimap, &cub);
    mlx_loop(cub.mlx.init_ptr);
    mlx_terminate(cub.mlx.init_ptr);
  }
  return (0);
}
