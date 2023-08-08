/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:24 by maddou            #+#    #+#             */
/*   Updated: 2023/08/08 16:13:22 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
        print_error("ERROR: double player\n");        
}

void    check_map(t_cub *cub)
{
    (void)cub;
    check_start_end_line(cub);
    check_body_map(cub);
    check_double_element(cub);
    cub->i = 0;
    cub->j = 0;
}