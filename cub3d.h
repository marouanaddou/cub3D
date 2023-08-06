/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:24:04 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 14:00:36 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

typedef struct s_parser 
{
    char buffer[1000000];
    char **map;
    char **element;
    char **file;
    int count;
    int fd;
} t_parser;

typedef struct s_cub
{
    int i;
    int j;
    t_parser par;
} t_cub;

//-----------------------start parsing-------------------------//.

void    check_file_ext(char *name);
void	check_file(int fd);
void    check_map(char *map, t_cub *cub);

//-----------------------end parsing-------------------------//
#endif