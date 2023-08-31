/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_information_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:52:57 by maddou            #+#    #+#             */
/*   Updated: 2023/08/31 01:12:12 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
//free hna !.......!

void	check_argument(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		printf("ERROR: color1\n");
		exit(1);
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 1)
		{
			printf("ERROR: color2\n");
			exit(1);
		}
		i++;
	}
}

void	check_rgb(char **color, t_cub *cub, int atoi)
{
	cub->j = 0;
	atoi = 0;
	while (color[cub->j] != NULL)
	{
		check_argument(color[cub->j]);
		atoi = ft_atoi(color[cub->j]);
		if (atoi < 0 || atoi > 255)
		{
			printf("ERROR: color3\n");
			exit(1);
		}
		cub->j++;
	}
}

// hna khasna free .....!
void	check_double(t_cub *cub, int i)
{
	cub->j = 0;
	while (cub->j < cub->par.cnt_elmt)
	{
		if (cub->j != i)
		{
			if (ft_strcmp(cub->par.elm[i].direction,
					cub->par.elm[cub->j].direction) == 0)
			{
				printf("ERROR: double information\n");
				exit(1);
			}
		}
		cub->j++;
	}
	cub->j = 0;
}

//free ......!@
void	check_double_coma(t_cub *cub, char *color)
{
	cub->i = 0;
	if (color[0] == ',' || color[ft_strlen(color) - 1] == ',')
		print_error("ERROR: color4\n"); 
	while (color[cub->i] != '\0')
	{
		if (color[cub->i] == ',' && color[cub->i + 1] == ',')
			print_error("ERROR: color5\n");
		cub->i++;
	}
}
