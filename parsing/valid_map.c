/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:44:13 by maddou            #+#    #+#             */
/*   Updated: 2023/08/27 13:15:29 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// free /......!

void	check_element(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 'N' && str[i] != 'W' && str[i] != 'S' && str[i] != 'E'
			&& str[i] != ' ' && str[i] != '1' && str[i] != '0')
		{
			print_error("ERROR: map not valid");
			exit(1);
		}
		i++;
	}
}

char	**copy_map(t_cub *cub, char **map)
{
	map = malloc(sizeof(char *) * (cub->par.cnt_map + 1));
	if (!map)
		return (0);
	cub->i = 0;
	while (cub->par.map[cub->i] != NULL)
	{
		map[cub->i] = ft_strdup(cub->par.map[cub->i]);
		check_element(map[cub->i]);
		cub->i++;
	}
	map[cub->i] = NULL;
	return (map);
}

void	valid_map(t_cub *cub, char **map, int y, int x)
{
	if (map[y][x] != '1' && (x == 0 || y == 0 || y == cub->mlx.height - 1))
		print_error("FOUND ERROR\n");
	if ((unsigned int)y == ft_strlen(map[y]) - 1 && map[y][ft_strlen(map[x])
		- 1] != '1')
		print_error("FOUND ERRR OUT BOUND\n");
	if (map[y][x] <= 32)
		print_error("FOUND ERRR OUT BOUND\n");
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
