/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_information.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:51:35 by maddou            #+#    #+#             */
/*   Updated: 2023/09/01 13:13:55 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_copier(char add, char *new_data)
{
	int		nb;
	int		i;
	char	*new;

	nb = 0;
	i = 0;
	if (new_data != NULL)
		nb = ft_strlen(new_data);
	new = malloc(sizeof(char) * (nb + 2));
	if (!new)
		return (0);
	if (new_data != NULL)
	{
		while (new_data[i] != '\0')
		{
			new[i] = new_data[i];
			i++;
		}
	}
	new[i++] = add;
	new[i] = '\0';
	free(new_data);
	return (new);
}

void	fill_information(t_cub *cub)
{
	int	c;

	while (cub->par.element[cub->i] != NULL)
	{
		cub->j = 0;
		c = 0;
		cub->par.elm[cub->i].path = NULL;
		cub->par.elm[cub->i].direction = NULL;
		while (cub->par.element[cub->i][cub->j] != '\0')
		{
			if (c == 0 && cub->par.element[cub->i][cub->j] != ' ')
				cub->par.elm[cub->i].direction = ft_copier(cub->par.element
					[cub->i][cub->j], cub->par.elm[cub->i].direction);
			else if (c == 0 && cub->par.element[cub->i][cub->j] == ' ')
				c = 1;
			else if (c == 1)
				cub->par.elm[cub->i].path = ft_copier(cub->par.element
					[cub->i][cub->j], cub->par.elm[cub->i].path);
			cub->j++;
		}
		cub->i++;
	}
}

void	fill_texture_path(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(cub->par.elm[i].direction, "NO") == 0)
			cub->par.texture_path[0] = ft_strdup(cub->par.elm[i].path);
		else if (ft_strcmp(cub->par.elm[i].direction, "SO") == 0)
			cub->par.texture_path[1] = ft_strdup(cub->par.elm[i].path);
		else if (ft_strcmp(cub->par.elm[i].direction, "WE") == 0)
			cub->par.texture_path[2] = ft_strdup(cub->par.elm[i].path);
		else if (ft_strcmp(cub->par.elm[i].direction, "EA") == 0)
			cub->par.texture_path[3] = ft_strdup(cub->par.elm[i].path);
		i++;
	}
	cub->par.texture_path[4] = NULL;
}

void	check_information(t_cub *cub)
{
	split_newline_information(cub);
	fill_information(cub);
	check_error_information(cub);
	fill_texture_path(cub);
	cub->i = 0;
	cub->j = 0;
}
