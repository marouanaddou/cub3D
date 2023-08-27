/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:52:24 by maddou            #+#    #+#             */
/*   Updated: 2023/08/27 13:35:04 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

void	check_double_element(t_cub *cub)
{
	int	nb;

	cub->i = 0;
	nb = 0;
	while (cub->par.map[cub->i] != NULL)
	{
		cub->j = 0;
		while (cub->par.map[cub->i][cub->j] != '\0')
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

//free........!

void	check_map(t_cub *cub)
{
	char	*tream;

	cub->mlx.height = cub->par.cnt_map;
	check_valid_map(cub);
	check_double_element(cub);
	cub->i = 0;
	while (cub->par.map[cub->i] != NULL)
	{
		tream = ft_strtrim(cub->par.map[cub->i], "\n");
		free(cub->par.map[cub->i]);
		cub->par.map[cub->i] = ft_strdup(tream);
		free(tream);
		cub->i++;
	}
}
