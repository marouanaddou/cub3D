/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:24 by maddou            #+#    #+#             */
/*   Updated: 2023/08/12 10:59:12 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>

void    print_error(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        write(2, &str[i], 1);
        i++;
    }
    exit(1);
}

void    check_start_end_line(t_cub *cub)
{
    while(cub->par.map[0][cub->i] != '\0' && cub->par.map[0][cub->i] != '\n')
    {
        if(cub->par.map[0][cub->i] != '1' && cub->par.map[0][cub->i] != ' ') //free ??????.....
            print_error("ERROR: wall\n");
        cub->i++;
    }
    while(cub->par.map[cub->par.cnt_map - 1][cub->j] != '\0' 
        && cub->par.map[cub->par.cnt_map - 1][cub->j] != '\n')
    {
        if(cub->par.map[cub->par.cnt_map - 1][cub->j] != '1' 
            && cub->par.map[cub->par.cnt_map - 1][cub->j] != ' ') //free ??????.....
            print_error("ERROR: wall\n");
        cub->j++;
    }
    cub->i = 1;
    cub->j = 0;
}

int check_element(char c)
{
    int i;
    char str[] = "10NSWE";

    i = 0;
    while(str[i] != '\0')
    {
        if (c == str[i])
            return (1);
        i++;
    }
    return (0);
}

void    check_direction_element(t_cub *cub)
{
    if (check_element(cub->par.map[cub->i][cub->j - 1]) == 0
        || check_element(cub->par.map[cub->i][cub->j + 1]) == 0
        || check_element(cub->par.map[cub->i - 1][cub->j]) == 0
        || check_element(cub->par.map[cub->i + 1][cub->j]) == 0)
        print_error("ERROR: wall 1\n");
}

void    check_body_map(t_cub *cub)
{
    while(cub->i < cub->par.cnt_map - 1)
    {
        cub->j = 0;
        while(cub->par.map[cub->i][cub->j] != '\0' && cub->par.map[cub->i][cub->j] == ' ')
            cub->j++;
        if (cub->par.map[cub->i][cub->j] != '1' || 
            cub->par.map[cub->i][ft_strlen(cub->par.map[cub->i]) - 2] != '1')
            print_error("ERROR: wall 1\n");
        while(++cub->j < (int)ft_strlen(cub->par.map[cub->i]) - 2)
        {
            if (cub->par.map[cub->i][cub->j] != ' ' && cub->par.map[cub->i][cub->j] != '1')
                check_direction_element(cub);
        }
        cub->i++;
    }
}

void    check_double_element(t_cub *cub)
{
    int nb;
    
    cub->i = 0;
    nb = 0;
    while(cub->par.map[cub->i] != NULL)
    {
        cub->j = 0;
        while(cub->par.map[cub->i][cub->j] != '\0')
        {
            if (cub->par.map[cub->i][cub->j] == 'N' 
                || cub->par.map[cub->i][cub->j] == 'S'
                || cub->par.map[cub->i][cub->j] == 'W'
                || cub->par.map[cub->i][cub->j] == 'E')
                nb++;
            cub->j++;
        }
        cub->i++;
    }    
    if (nb != 1)
        print_error("ERROR: player\n");       
}
char    **copy_map(t_cub *cub, char **map)
{
    map = malloc(sizeof(char *) *(cub->par.cnt_map + 1));
    //protiction malloc !!!!!!!
    cub->i = 0;
    while(cub->par.map[cub->i] != NULL)
    {
        map[cub->i] = ft_strdup(cub->par.map[cub->i]);
        cub->i++;
    }
    map[cub->i] = NULL;
    return(map);
}

void    valid_path(t_cub *cub, char **map, int y, int x)
{
    if (map[y][x] != '1' && x == 0) {
        print_error("FOUND ERROR\n");
        return ;
    }
    if ((unsigned int)y == ft_strlen(map[y]) - 1 && map[y][ft_strlen(map[x]) - 1] != '1') {
        print_error("FOUND ERRR OUT BOUND\n");
    }
    if (map[y][x] <= 32) {
         print_error("FOUND ERRR OUT BOUND\n");  
    }
    if (map[y][x] == '1')
        return ;
    map[y][x] = '1';
	valid_path(cub, map, y, x + 1);
	valid_path(cub, map, y, x - 1);
	valid_path(cub, map, y - 1, x);
	valid_path(cub, map, y + 1, x);
        cub->i = 0;
    // printf ("---------\n");
    // while(map[cub->i] != NULL)
    // {
    //     printf ("%s", map[cub->i]);
    //     cub->i++;
    // }
    // printf ("---------\n");
}

void    check_valid_path(t_cub *cub)
{
    int i;
    int j;
    char **map;
    
    map = NULL;
    map = copy_map(cub, map);
    i = (cub->par.x - 5) / 30;
    j = (cub->par.y - 5) / 30;
    cub->i = 0;
    player(cub);
    valid_path(cub, map, j, i);
}

void    check_map(t_cub *cub)
{
    char *tream;
    
    // check_start_end_line(cub);
    check_valid_path(cub);
    check_double_element(cub);
    // check_body_map(cub);
    cub->i = 0;
    cub->mlx.width = 0;
    while(cub->par.map[cub->i] != NULL)
    {
        tream = ft_strtrim(cub->par.map[cub->i], "\n");
        free(cub->par.map[cub->i]);
        cub->par.map[cub->i] = ft_strdup(tream);
        free(tream);
        cub->j = 0;
        while(cub->par.map[ cub->i][cub->j] != '\0')    
            cub->j++;
        if (cub->j > cub->mlx.width)
            cub->mlx.width = cub->j;
        cub->i++;
    }
    cub->mlx.height = cub->par.cnt_map;
}