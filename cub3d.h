/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:24:04 by maddou            #+#    #+#             */
/*   Updated: 2023/08/30 20:56:09 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000.0
# define HEIGHT 500.0
# define MINIMAP_SCALE_FACTOR 0.2
# define LEFT_RIGHT 0
# define TOP_BOTTOM 1
# define LEFT 2
# define RIGHT 3
# define TOP 4
# define BOTTOM 5
# define CENTER 15

typedef struct s_mlx
{
	int				width;
	int				height;
	void			*init_ptr;
	void			*img_ptr;
	void			*fullimg_ptr;
	mlx_t			*mlx;
}					t_mlx;

typedef struct s_point
{
	double			x_end;
	double			y_end;
	int				direction;
	int				view;
	double			angle;
}					t_point;

typedef struct s_elem
{
	char			*path;
	char			*direction;
}					t_elem;

typedef struct s_ray
{
	float			x_inc;
	float			y_inc;
	float			x_hor;
	float			y_ver;
	double			first_angle;
}					t_ray;

typedef struct s_parser
{
	int				floor;
	int				ceiling;
	char			**map;
	double			x;
	double			y;
	int				pxp;
	int				pyp;
	char			**element;
	char			**file;
	int				cnt_map;
	t_elem			*elm;
	char			*hexfloor;
	char			*hexceiling;
	int				cnt_elmt;
}					t_parser;

typedef struct s_cub
{
	int				i;
	int				j;
	t_point			*point;
	t_ray			ray;
	double			angle_increment;
	double			angle;
	double			degree;
	double			wallheight;
	double			x_start;
	double			y_end;
	double			distance;
	double			correctdistance;
	int32_t			color;
	int				x_pos;
	int				y_inc;
	double			rayangle;
	t_parser		par;
	t_mlx			mlx;
	mlx_texture_t	*txt;
	uint32_t		**left_texture;
	uint32_t		**right_texture;
	uint32_t		**top_texture;
	uint32_t		**bottom_texture;
	mlx_image_t		*img;
	int				mouse_x;
	int				mouse_y;
}					t_cub;

void				free_double_pointer(char **result);
void				check_file_ext(char *name);
void				check_file(int fd);
void				check_map(t_cub *cub);
void				map_len(char *map, t_cub *cub);
void				allocation_map(t_cub *cub, char *map);
void				load_map(char *map, t_cub *cub);
void				check_information(t_cub *cub);
void				print_error(char *str);
void				player(t_cub *cub);
char				*ft_copier(char add, char *new_data);
void				check_line(char *line, t_cub *cub);
void				fill_line(t_cub *cub);
void				check_error_information(t_cub *cub);
void				split_newline_information(t_cub *cub);
void				check_double_coma(t_cub *cub, char *color);
void				check_rgb(char **color, t_cub *cub, int atoi);
void				check_double(t_cub *cub, int i);
void				check_valid_map(t_cub *cub);
void				draw_minimap(void *cub);
void				draw_fc(t_cub *cub);
void				loop_hook(void *cub);
void				find_point(t_cub *cub);
void				cast_rays(t_cub *cub);
void				cast_rays_utils(t_cub *cub, int i, bool check);
int					check_holes(t_cub *cub, float prev_x, float prev_y);
void				draw_view(t_cub *cub);
int					check_wall(t_cub *cub, double y, double x);
void				load_textures(t_cub *cub);
int					open_file(char *map, int fd);

#endif