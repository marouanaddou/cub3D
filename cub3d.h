/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:24:04 by maddou            #+#    #+#             */
/*   Updated: 2023/08/07 15:13:41 by maddou           ###   ########.fr       */
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
void    check_map_element(t_cub *cub);

//-----------------------end parsing-------------------------//
#endif