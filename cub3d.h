/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:24:04 by maddou            #+#    #+#             */
/*   Updated: 2023/08/20 12:59:43 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
#include "mlx42/include/MLX42/MLX42.h"

#define WIDTH 1920
#define HEIGHT 1300
#define DEGREE 60 * (M_PI / 180)
#define ANGLE_INCREMENT (DEGREE / WIDTH)
#define MINIMAP_SCALE_FACTOR 0.4

typedef struct s_mlx
{
	int		width;
	int		height;
    void    *init_ptr;
    void    *img_ptr;
    void    *fullimg_ptr;
    mlx_t   *mlx;
}			t_mlx;

typedef struct s_point{
    double x_end;
    double y_end;
} t_point;

typedef struct s_elem
{
    char *path;
    char *direction;
} t_elem;

typedef struct  s_ray
{
    float x_inc;
    float y_inc;
    float x_hor;
    float y_ver;
    double   first_angle;
} t_ray;

typedef struct s_parser 
{
    char **map;
    double  x;
    double y;
    int pxp;
    int pyp;
    char **element;
    char **file;
    int cnt_map;
    t_elem *elm;
    char *hexfloor;
    char *hexceiling;
    int cnt_elmt;
} t_parser;

typedef struct s_cub
{
    int i;
    int j;
    t_point *point;
    t_ray   ray;
    double angle_increment;
    double angle;
    double degree;
    t_parser par;
    t_mlx mlx;
} t_cub;

void free_double_pointer(char **result);


//-----------------------start parsing-------------------------//.

void    check_file_ext(char *name);
void	check_file(int fd);
void    check_map(t_cub *cub);
void    map_len(char *map, t_cub *cub);
void	load_map(char *map ,t_cub *cub);
void    check_information(t_cub *cub);
void    print_error(char *str);
void    player(t_cub *cub);
char	*ft_copier(char add, char *new_data);
//-----------------------end parsing-------------------------//
#endif