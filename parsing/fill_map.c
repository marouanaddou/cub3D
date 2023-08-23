/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:20 by maddou            #+#    #+#             */
/*   Updated: 2023/08/21 10:55:34 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    initialisation_fa(char *line, t_cub *cub, int i)
{
    i = 0;
    while(line[i] != '\0')
    {
        if (line[i] == 'N')
            cub->ray.first_angle  = -(M_PI / 2);
        else if (line[i] == 'W')
            cub->ray.first_angle  = M_PI;
        else if (line[i] == 'S')
            cub->ray.first_angle  = (M_PI / 2);
        else if (line[i] == 'E')
            cub->ray.first_angle = 0;
        if (line[i] == 'N' || line[i] == 'W' || line[i] == 'S' || line[i] == 'E')
        {
            cub->par.x = (i * 30);
            cub->par.y = (cub->j * 30);
        }
        i++;
    }
}

void    check_line(char *line, t_cub *cub)
{
    int i;

    i = 0;
    if (line[i] == '\n')
        print_error("ERROR");
    while(line[i] != '\0' && line[i] == ' ')
    {
        if(line[i + 1] == '\n' || line[i + 1] == '\0')
            print_error("ERROR"); //freee ......!!!!
        i++;
    }
    initialisation_fa(line, cub, i);
}

void    fill_line(t_cub *cub)
{
    int j;

    j = 0;
    cub->par.map[cub->j] = NULL;
    while(cub->par.file[cub->i][j] != '\0')
    {
        if (j != (int)ft_strlen(cub->par.file[cub->i]) - 1)
            cub->par.map[cub->j] = ft_copier(cub->par.file[cub->i][j], cub->par.map[cub->j]);
        j++;
    }
    while (j < cub->mlx.width)
    {
        cub->par.map[cub->j] = ft_copier(' ', cub->par.map[cub->j]);
        j++;
    }
    cub->j++;
}