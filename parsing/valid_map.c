/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:44:13 by maddou            #+#    #+#             */
/*   Updated: 2023/09/02 12:56:03 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_valid_map(t_cub *cub, char **map, char *str)
{
	free_double_pointer(map);
	free_double_pointer(cub->par.map);
	free_double_pointer(cub->par.element);
	free_element(cub->par.elm);
	print_error(str);
}

void	check_element(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != 'N' && map[i][j] != 'W' && map[i][j] != 'S' 
				&& map[i][j] != 'E'
				&& map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0')
				free_valid_map(cub, map, "ERROR: map not valid\n");
			j++;
		}
		i++;
	}
}

char	**copy_map(t_cub *cub, char **map)
{
	map = malloc(sizeof(char *) * (cub->par.cnt_map + 1));
	if (!map)
	{
		free_double_pointer(cub->par.map);
		free_double_pointer(cub->par.element);
		free_element(cub->par.elm);
		exit(1);
	}
	cub->i = 0;
	while (cub->par.map[cub->i] != NULL)
	{
		map[cub->i] = ft_strdup(cub->par.map[cub->i]);
		cub->i++;
	}
	map[cub->i] = NULL;
	check_element(map, cub);
	return (map);
}

void	valid_map(t_cub *cub, char **map, int y, int x)
{
	if (map[y][x] != '1' && (x == 0 || y == 0 || y == cub->mlx.height - 1))
		free_valid_map(cub, map, "ERROR: map\n");
	if (x == (int)ft_strlen(map[y]) - 1 && map[y][x] != '1')
		free_valid_map(cub, map, "ERROR: map\n");
	if (map[y][x] <= 32)
		free_valid_map(cub, map, "ERROR: map\n");
	if (map[y][x] == '1' || map[y][x] == 'Z')
		return ;
	map[y][x] = 'Z';
	valid_map(cub, map, y, x + 1);
	valid_map(cub, map, y, x - 1);
	valid_map(cub, map, y - 1, x);
	valid_map(cub, map, y + 1, x);
}

void	check_valid_map(t_cub *cub)
{
	int		x;
	int		y;
	char	**map;

	map = NULL;
	map = copy_map(cub, map);
	x = (cub->par.x) / 30;
	y = (cub->par.y) / 30;
	cub->i = 0;
	valid_map(cub, map, y, x);
	free_double_pointer(map);
}
