/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:24:04 by maddou            #+#    #+#             */
/*   Updated: 2023/08/08 20:02:43 by mel-gand         ###   ########.fr       */
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

#define WIDTH 1200
#define HEIGHT 900

typedef struct s_mlx
{
	int		width;
	int		height;
    void    *init_ptr;
    void    *img_ptr;
}			t_mlx;

typedef struct s_elem
{
    char *path;
    char *direction;
} t_elem;

typedef struct s_parser 
{
    char **map;
    char **element;
    char **file;
    int cnt_map;
    t_elem *elm;
    int cnt_elmt;
} t_parser;


typedef struct s_cub
{
    int i;
    int j;
    t_parser par;
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

//-----------------------end parsing-------------------------//
#endif