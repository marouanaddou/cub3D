/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_newline_information.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:51:00 by maddou            #+#    #+#             */
/*   Updated: 2023/08/31 15:09:59 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**number_element_without_newlen(t_cub *cub, char **result)
{
	cub->i = 0;
	cub->par.cnt_elmt = 0;
	while (cub->par.element[cub->i] != NULL)
	{
		if (cub->par.element[cub->i][0] != '\n')
			cub->par.cnt_elmt++;
		cub->i++;
	}
	if (cub->par.cnt_elmt != 6)
	{
		free_double_pointer(cub->par.element);
		free_double_pointer(cub->par.map);
		print_error("ERROR: information\n");
	}
	result = malloc(sizeof(char *) * (cub->par.cnt_elmt + 1));
	cub->i = 0;
	cub->j = 0;
	return (result);
}

void	split_newline_information(t_cub *cub)
{
	char	**result;
	result = NULL;
	result = number_element_without_newlen(cub, result);
	while (cub->par.element[cub->i] != NULL)
	{
		if (cub->par.element[cub->i][0] != '\n')
		{
			result[cub->j] = ft_strdup(cub->par.element[cub->i]);
			cub->j++;
		}
		cub->i++;
	}
	result[cub->j] = NULL;
	cub->j = 0;
	free_double_pointer(cub->par.element);
	cub->par.element = result;
	cub->par.elm = malloc(sizeof(t_elem) * cub->par.cnt_elmt);
	cub->i = 0;
}
